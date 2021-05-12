#include "userList.h"

struct _tagNode {
	char *tag;
    userList usersList;
	struct _tagNode *next;
};
typedef struct _tagNode tagNode;

typedef struct{
    tagNode *start;
    tagNode *end;
} tagList;

void tagListCreate(tagList *list);
int tagListSize(tagList *list);
void tagListAdd(tagList *list, char *tag);
tagNode *tagListFind(tagList *list, char *tag);
int tagListRemoveFirst(tagList *list);
void tagListDelete(tagList *list);
