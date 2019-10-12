//2521 Aissgement 2 searchPagerank.h
//Haowei Lou
//z5258575
//31 July 2019 

typedef struct searchList *SList;
typedef struct searchNode *SNode;


struct searchNode
{
    char *name;
    int appear;
    double value;
    struct searchNode *next;  
};

struct searchList
{
    int size;
    struct searchNode *first;
    struct searchNode *last;
};
