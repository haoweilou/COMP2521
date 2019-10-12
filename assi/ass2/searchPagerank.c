//2521 Aissgement 2 searchPagerank.c
//Haowei Lou
//z5258575
//31 July 2019
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include "searchPagerank.h"

#define TRUE 1
#define FALSE 0


//function
static SList list;

SList newList(void);

int isInList(char *);

void insertList(char *);
void sortList(SList);
void freeList(SList list);

int main(int args, char *argv[])
{
    char **words = calloc(sizeof(char *),args-1);
    int num = args - 1;
    //save arguments into words[]
    for (int i = 0; i < args - 1; i++)
    {
        words[i] = malloc(strlen(argv[i+1]));
        strcpy(words[i],argv[i + 1]);
    }

    list = newList();

    char temp[1000] = {0};
    for (int i = 0; i < num; i++)
    {
        FILE *file = fopen("invertedIndex.txt","r");
        while (fgets(temp,1000,file))
        {
            char new[1000];
            //read a line into temp
            sscanf(temp,"%s",new);

            if(temp[strlen(temp) - 1] == '\n') temp[strlen(temp) - 1] = '\0';
            if(strcmp(new,words[i]) != 0) continue;

            char *links;
            links = strtok(temp," ");
            while(links != NULL)
            {
                links = strtok(NULL," ");
                if(links != NULL) insertList(links);
            }            
            break;
        }
        fclose(file);
    }

    FILE *PR = fopen("pagerankList.txt","r");
    while (fgets(temp, 1000, PR))
    {
        char *new;
        double number;
        
        new = strtok(temp,", ");
        char *linkname = malloc(strlen(new));

        strcpy(linkname,new);
        new = strtok(NULL,", ");
        new = strtok(NULL,", ");

        number = strtof(new,NULL);
        if(isInList(linkname) == FALSE) continue;

        for(SNode curr = list->first; curr != NULL; curr = curr->next)
        {
            if(strcmp(linkname,curr->name) == 0) curr->value = number;
            if(strcmp(linkname,curr->name) == 0) break;
        }
    }
      
    sortList(list);
    int i = 0;
    for(SNode curr = list->first; curr != NULL && i < 30; curr = curr->next, i++)
    {
        printf("%s\n",curr->name);
    }
    freeList(list);
        
    return 0;
}
//create new list
SList newList()
{
    SList list = malloc(sizeof(*list));
    list->size = 0;
    list->first = NULL;
    list->last = NULL;
    return list;
}
//insert given name into list
void insertList(char *name)
{
    if(isInList(name) == TRUE)
    {
        for(SNode curr = list->first; curr != NULL; curr = curr->next)
        {
            if(strcmp(name,curr->name) == 0) curr->appear += 1;
            if(strcmp(name,curr->name) == 0) return;
        }
    }


    SNode new = malloc(sizeof(*new));
    new->name = malloc(strlen(name));
    new->appear = 1;
    strcpy(new->name,name);
    new->next = NULL;
    list->size++;

    if(list->first == NULL)
    {
        list->first = new;
        list->last = new;
        return;
    }

    list->last->next = new;
    list->last = new;
    list->last->next = NULL;
    return;
}
//check given name is in list
int isInList(char *name)
{
    for(SNode curr = list->first; curr != NULL; curr = curr->next)
        if(strcmp(name,curr->name) == 0) return TRUE;
    return FALSE;
}
//sort list by bubble sort
void sortList(SList newlist)
{
    for (SNode curr = newlist->first; curr != NULL; curr = curr->next)
    {
        for(SNode now = newlist->first; now->next != NULL; now = now->next)
        {
            if(now->appear < now->next->appear || 
            (now->value < now->next->value && now->appear == now->next->appear))
            {
                double value = now->next->value;
                char temp[1000];
                int appear = now->next->appear;
                strcpy(temp,now->next->name);

                now->next->value = now->value;
                now->next->appear = now->appear;
                strcpy(now->next->name, now->name);
                
                now->value = value;
                now->appear = appear;
                strcpy(now->name, temp);
            }
        }
    }
    return;
}
//free all list
void freeList(SList list)
{
	SNode curr = list->first;
	SNode prev = NULL;
	while (curr != NULL)
	{
		prev = curr;
		curr = curr->next;
		free(prev);
	}
	free(list);
	return;
}
