#include "common.h"
#include "tagList.h"

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <sys/socket.h>
#include <sys/types.h>

#define BUFSZ 1024

void usage(int argc, char **argv) {
    printf("usage: %s <server port>\n", argv[0]);
    printf("example: %s51511\n", argv[0]);
    exit(EXIT_FAILURE);
}

struct client_data {
    int csock;
    struct sockaddr_storage storage;
};

tagList tagsList;
userList usersList;

void cleanUserData(struct client_data *cdata) {
    close(cdata->csock);

    for (tagNode* tag = tagsList.start; tag != NULL; tag = tag->next) {
        userList tempUserList = tag->usersList;
        userNode *user = userListFind(&tempUserList, cdata->csock);
        if (user != NULL) {
            userListRemove(&tempUserList, user);
        }
    }

    userListRemove(&usersList, userListFind(&usersList, pthread_self()));
    free(cdata);
}

int extractTags(char *message, tagList *list) {
    size_t messageSize = strlen(message);
    int inTag = 0, startIndex = 0, count = 0, validTag = 0;
    for (size_t i = 0; i < messageSize; i++) {
        if ((inTag == 0 && message[i] == '#' && (i != messageSize - 1 && message[i + 1] != ' ')) && ((i > 0 && message[i - 1] == ' ') || i == 0)) {
            startIndex = i;
            inTag = 1;
        }
        if (inTag == 1 && ((i != messageSize - 1 && message[i+1] == ' ') ||  i == messageSize - 1))
            validTag = 1;

        if (inTag == 1 && validTag == 1) {
            inTag = 0;
            validTag = 0;
            count++;
            int tagSize = i - startIndex + 1;
            char tag[tagSize];
            memcpy(tag, message + startIndex + 1, tagSize);
            tag[tagSize - 1] = '\0';
            tagListAdd(list, tag);
        }
    }
    
    return count;
}

void * client_thread(void *data) {
    struct client_data *cdata = (struct client_data *)data;
    struct sockaddr *caddr = (struct sockaddr *)(&cdata->storage);

    char caddrstr[BUFSZ];
    addrtostr(caddr, caddrstr, BUFSZ);
    printf("[log] connection from %s\n", caddrstr);

    while(1) {
        int totalStringSize = 0;
        char buf[BUFSZ];
        memset(buf, 0, BUFSZ);

        while(1) {
            size_t count = recv(cdata->csock, buf + totalStringSize, BUFSZ - totalStringSize, 0);
            totalStringSize += count;
            if (buf[strlen(buf) - 1] == '\n' || totalStringSize == 0)
                break;

        }

        if (totalStringSize == 0) {
            printf("[log] connection with %s closed by client\n", caddrstr);
            break;
        }

        printf("%s", buf);

        char *m;
        m = strtok(buf, "\n");
        while (m != NULL) {
            char message[strlen(m) + 1];
            memcpy(message, m, strlen(m));
            message[strlen(m)] = '\0';
            if (strlen(message) == 0) {
                printf("[log] connection with %s closed by blank message\n", caddrstr);
                break;
            }

            if (strlen(message) > 500) {
                printf("[log] connection with %s closed by long message\n", caddrstr);
                break;
            }

            if (checkStringValid(message) == 0) {
                printf("[log] connection with %s closed by invalid char\n", caddrstr);
                break;
            }

            if (strcmp(message, "##kill") == 0) {
                close(cdata->csock);
                free(cdata);

                userListDelete(&usersList);
                tagListDelete(&tagsList);
                
                exit(EXIT_SUCCESS);
            }

            char returnMessage[BUFSZ];
            memset(returnMessage, 0, BUFSZ);

            int messageForSubscribe = checkStringSubscribe(message);
            if (messageForSubscribe == 1) {
                //subscribe
                char tag[strlen(message)];
                memcpy(tag, message + 1, strlen(message));
                tag[strlen(message) - 1] = '\0';

                tagNode *userTagNode = tagListFind(&tagsList, tag);

                if (userTagNode == NULL) {
                    tagListAdd(&tagsList, tag);
                    userTagNode = tagsList.end;
                }

                if (userListFind(&userTagNode->usersList, cdata->csock)) {
                    sprintf(returnMessage, "already subscribed +%.1000s\n", tag);
                    send(cdata->csock, returnMessage, strlen(returnMessage), 0);
                } else {
                    userListAdd(&userTagNode->usersList, cdata->csock);
                    sprintf(returnMessage, "subscribed +%.1000s\n", tag);
                    send(cdata->csock, returnMessage, strlen(returnMessage), 0);
                }
            } else if (messageForSubscribe == 2) {
                //unsubscribe
                char tag[strlen(message)];
                memcpy(tag, message + 1, strlen(message));
                tag[strlen(message) - 1] = '\0';

                tagNode *userTagNode = tagListFind(&tagsList, tag);

                if (userTagNode == NULL) {
                    printf("Oi\n");
                    sprintf(returnMessage, "not subscribed -%.1000s\n", tag);
                    send(cdata->csock, returnMessage, strlen(returnMessage), 0);
                } else {

                    if (userListFind(&userTagNode->usersList, cdata->csock) != NULL) {
                        userListRemove(&userTagNode->usersList, userListFind(&userTagNode->usersList, cdata->csock));
                        sprintf(returnMessage, "unsubscribed -%.1000s\n", tag);
                        send(cdata->csock, returnMessage, strlen(returnMessage), 0);
                    } else {
                        sprintf(returnMessage, "not subscribed -%.1000s\n", tag);
                        send(cdata->csock, returnMessage, strlen(returnMessage), 0);
                    }

                }

            } else {
                //common message
                tagList tempTagsList;
                tagListCreate(&tempTagsList);

                userList sentUsers;
                userListCreate(&sentUsers);

                int tags = extractTags(message, &tempTagsList);

                for (size_t i = 0; i < tags; i++) {

                    char *tag = tempTagsList.start->next->tag;
                    
                    tagNode *mentionedTag = tagListFind(&tagsList, tag);

                    if (mentionedTag != NULL) {

                        userList users = mentionedTag->usersList;
                        userNode *userData = users.start->next;

                        while (userData != NULL) {
                            if (userListFind(&sentUsers, userData->id) == NULL && userData->id != cdata->csock) {
                                sprintf(returnMessage, "%s\n", message);
                                int size = send(userData->id, returnMessage, strlen(returnMessage), 0);
                                if (size != strlen(returnMessage))
                                    logexit("send");

                                userListAdd(&sentUsers, userData->id);
                            }

                            userData = userData->next;
                        }
                        
                    }

                    tagListRemoveFirst(&tempTagsList);

                }

                userListDelete(&sentUsers);
                tagListDelete(&tempTagsList);
                
            }
            printf("[msg] %s\n", returnMessage);
            m = strtok(NULL, "\n");

        }
        

    }

    cleanUserData(cdata);
    pthread_exit(EXIT_SUCCESS);

}

int main(int argc, char **argv) {
    if (argc < 2) {
        usage(argc, argv);
    }

    struct sockaddr_storage storage;
    if (0 != server_sockaddr_init(argv[1], &storage)) {
        usage(argc, argv);
    }

    int s;
    s = socket(storage.ss_family, SOCK_STREAM, 0);
    if (s == -1) {
        logexit("socket");
    }

    int enable = 1;
    if (0 != setsockopt(s, SOL_SOCKET, SO_REUSEADDR, &enable, sizeof(int))) {
        logexit("setsockopt");
    }

    struct sockaddr *addr = (struct sockaddr *)(&storage);
    if (0 != bind(s, addr, sizeof(storage))) {
        logexit("bind");
    }

    if (0 != listen(s, 10)) {
        logexit("listen");
    }

    char addrstr[BUFSZ];
    addrtostr(addr, addrstr, BUFSZ);
    tagListCreate(&tagsList);
    userListCreate(&usersList);
    printf("bound to %s, waiting connections\n", addrstr);

    while (1) {
        struct sockaddr_storage cstorage;
        struct sockaddr *caddr = (struct sockaddr *)(&cstorage);
        socklen_t caddrlen = sizeof(cstorage);

        int csock = accept(s, caddr, &caddrlen);
        if (csock == -1) {
            logexit("accept");
        }

        struct client_data *cdata = malloc(sizeof(*cdata));
        if (!cdata) {
            logexit("malloc");
        }
        cdata->csock = csock;
        memcpy(&(cdata->storage), &cstorage, sizeof(cstorage));

        pthread_t tid;
        pthread_create(&tid, NULL, client_thread, cdata);
        userListAdd(&usersList, (int)tid);
    }

    exit(EXIT_SUCCESS);
}
