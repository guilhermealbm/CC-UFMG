struct _userNode{
	int id;
	struct _userNode *next;
};
typedef struct _userNode userNode;

typedef struct {
    userNode *start;
    userNode *end;
} userList;

void userListCreate(userList *list);
int userListSize(userList *list);
void userListAdd(userList *list, int id);
userNode *userListFind(userList *list, int id);
void userListRemove(userList *list, userNode *previousRef);
void userListDelete(userList *list);
