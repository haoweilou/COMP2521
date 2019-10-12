//2521 Aissgement 2 scaledFootrule.h
//Haowei Lou
//z5258575
//31 July 2019
typedef struct scaledList *List;
typedef struct scaledNode *Node;

typedef struct scaledNode
{
    char *name;
    int value;
    struct scaledNode *next;  
} scaledNode;

typedef struct scaledList
{
    struct scaledNode *first;
    struct scaledNode *last;
} scaledList;

List newList(void);

int isInList(char *, List);
void insertList(char *, List);
void sortList(List);

int FindPositionInList(char *, List list);
int NumOfLinks(List);
void Hungarian(double **, int *, char **);

void freeList(List);
double sum(List *list,int position, char *name);
double absnum(char*,List, int);

char *IdToName(int, List);