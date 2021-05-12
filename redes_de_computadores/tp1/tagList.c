#include "tagList.h"
#include <stdlib.h>
#include <string.h>

void tagListCreate(tagList *list) {
    list->start = (tagNode *) malloc(sizeof(tagNode));
    list->start->tag = NULL;
    list->end = list->start;
    list->start->next = NULL;
}

int tagListSize(tagList *list) {
    tagNode *curr = list->start;
    int i = 0;
    while (curr->next != NULL) {
        i++;
        if (curr->next == list->end)
            return i;
        curr = curr->next;
    }
    return i;
}

void tagListAdd(tagList *list, char *tag) {
    list->end->next = (tagNode *) malloc(sizeof(tagNode));
    list->end = list->end->next;
    
    list->end->tag = (char *) malloc((strlen(tag) + 1) * sizeof(char));
    memcpy(list->end->tag, tag, strlen(tag) + 1);

    list->end->tag[strlen(tag)] = '\0';
    userListCreate(&list->end->usersList);
    
    list->end->next = NULL;
}

tagNode *tagListFind(tagList *list, char *tag) {
    tagNode *curr = list->start;
    while (curr->next != NULL) {
        if (strcmp(curr->next->tag, tag) == 0)
            return curr->next;
        curr = curr->next;
    }
    return NULL;
}

int tagListRemoveFirst(tagList *list) {
    if (tagListSize(list) == 0)
        return 0;

    tagNode *curr = list->start;
    list->start = list->start->next;
    if (curr->tag != NULL) {
        free(curr->tag);
        userListDelete(&curr->usersList);
    }
    free(curr);
    return 1;
}

void tagListDelete(tagList *list) {
    tagNode *curr = list->start;

    while (curr != NULL) {
        list->start = curr->next;
        if (curr->tag != NULL) {
            userListDelete(&curr->usersList);
            free(curr->tag);
        }
        free(curr);
        curr = list->start;
    }    
}
