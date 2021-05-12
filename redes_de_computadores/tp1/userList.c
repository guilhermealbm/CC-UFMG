#include "userList.h"
#include <stdlib.h>

void userListCreate(userList *list) {
    list->start = (userNode *) malloc(sizeof(userNode));
    list->end = list->start;
    list->start->next = NULL;
}

int userListSize(userList *list) {
    userNode *curr = list->start;
    int i = 0;
    while (curr->next != NULL) {
        i++;
        if (curr->next == list->end)
            return i;
        curr = curr->next;
    }
    return i;
}

void userListAdd(userList *list, int id) {
    list->end->next = (userNode *) malloc(sizeof(userNode));
    list->end = list->end->next;
    list->end->id = id;
    list->end->next = NULL;
}

userNode *userListFind(userList *list, int id) {
    userNode *curr = list->start;
    while (curr != NULL && curr->next != NULL) {
        if (curr->next->id == id)
            return curr;
        curr = curr->next;
    }
    return NULL;
}

void userListRemove(userList *list, userNode *previousRef) {
    if (previousRef != NULL && previousRef->next != NULL) {
        userNode *user = previousRef->next;
        if (user == list->end)
            list->end = previousRef;
            
        previousRef->next = user->next;
        free(user);
    }
}

void userListDelete(userList *list) {
    userNode *curr = list->start;

    while (curr != NULL) {
        list->start = curr->next;
        free(curr);
        curr = list->start;
    }
}