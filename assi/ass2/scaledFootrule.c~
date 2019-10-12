//2521 Aissgement 2 scaledFootrule.c
//Haowei Lou
//z5258575
//31 July 2019
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<assert.h>
#include<math.h>

#include "scaledFootrule.h"

#define TRUE 1
#define FALSE 0
//global variable
int N;
char **urlnames;

//This is task is follwing a alogrithm called the Hungarian_algorithm
//It will created a N X N matrix with the W(c,p) value only each row 
//and column. each urls' W(c,p) value with position form 1..N. Then
//it will substruct each row with its min number. If it is assignable
//(each column and row have its own zero), it will assign each url to a
//position and return. Otherwise, this function will keep subtract min 
//number in remain until it reaches the assign condition and return.
int main(int args, char *argv[])
{
    char **files = calloc(sizeof(files),args-1);

    int num_of_files = args - 1;
    for(int i = 0; i < num_of_files; i++)
    {
        files[i] = malloc(strlen(argv[i+1]));
        assert(files[i] != NULL);
        strcpy(files[i],argv[i+1]);
    }

    List *list = calloc(sizeof(struct scaledList),num_of_files);
    List urls = malloc(sizeof(List));
    
    for (int i = 0; i < num_of_files; i++)
    {
        list[i] = newList();
        FILE *file = fopen(files[i],"r");
        char temp[1000]; 
        while (fscanf(file,"%s",temp) != EOF)
        {
            if(isInList(temp,urls) == FALSE)
            {
                insertList(temp,urls);
            }
            insertList(temp,list[i]);
        }

        fclose(file);
    }

    //N is size of urls
    N = NumOfLinks(urls);
    
    double **graph = calloc(sizeof(double *),N);
    urlnames = calloc(sizeof(char *),N);

    for(int i = 0; i < N; i++) graph[i] = malloc(sizeof(double) * N);
    //create a matrix of Wcp value for each urls and position
    Node temp = urls->first;
    for(int i = 0; i < N; i++)
    {
        for(int j = 0; j < N; j++)
        {
            graph[i][j] = sum(list, j + 1, temp->name);
        }
        temp = temp->next;
    }
    
    
    for(int i = 0; i < N; i++)
    {
        for(int j = 0; j < N; j++)
        {
            printf("%lf ",graph[i][j]);
        }
        printf("\n");
    }printf("\n");
    temp = urls->first;
    
    //P is set of position
    int *P = calloc(sizeof(int),N);
    for(int i = 0; i < N; i++) P[i] = -1;

    int l = 0;
    for(Node curr = urls->first; curr != NULL; curr = curr->next)
    {
        urlnames[l] = malloc(strlen(curr->name));
        strcpy(urlnames[l],curr->name);
        l++;
    }
  
    Hungarian(graph, P, urlnames);

    double out = 0;
    for(int i = 0; i < N; i++)
    {
        if(P[i] == -1) continue;
        out = out + sum(list,i + 1,IdToName(P[i],urls));
    }

    printf("%lf\n",out);
    for(int i = 0; i < N; i++)
    {
        printf("%s\n",IdToName(P[i],urls));
    }   

    freeList(urls);
    for (int i = 0; i < num_of_files; i++)
    {
        freeList(list[i]);
    }
    free(P);
    return 0;
}
//create a new list
List newList(void)
{
    List list = malloc(sizeof(list));
    list->first = NULL;
    list->last = NULL;
    return list;
}
//insert node who has 'name' into list
void insertList(char *name, List list)
{
    if(isInList(name, list) == TRUE) return;

    Node new = malloc(sizeof(*new));
    new->name = malloc(strlen(name));
    new->value = 0;
    strcpy(new->name,name);
    new->next = NULL;

    if(list->first == NULL)
    {
        list->first = new;
        list->last = list->first;
        return;
    }
    list->last->next = new;
    list->last = new;
    list->last->next = NULL;
    return;
}
//check wheter the node who have given name is in list
int isInList(char *name, List list)
{
    for(Node curr = list->first; curr != NULL; curr = curr->next)
    {
        if(strcmp(name,curr->name) == 0) return TRUE;
    }
    return FALSE;
}
//sort the linklist by bubble sort
void sortList(List newlist)
{
    for (Node curr = newlist->first; curr != NULL; curr = curr->next)
    {
        for(Node now = newlist->first; now->next != NULL; now = now->next)
        {
            if(now->value < now->next->value)
            {
                double value = now->next->value;
                char temp[1000];
                strcpy(temp,now->next->name);

                now->next->value = now->value;
                strcpy(now->next->name, now->name);
                
                now->value = value;
                strcpy(now->name, temp);
            }
        }
    }
    return;
}
//find position of node who has given name in list
int FindPositionInList(char *name, List list)
{
    int i = 1;
    for(Node curr = list->first; curr != NULL; curr = curr->next)
    {
        if(strcmp(curr->name,name) == 0) return i;
        i++;
    }
    return -1;
}
//found number of links in list
int NumOfLinks(List list)
{
    int i = 0;
    for(Node curr = list->first; curr != NULL; curr = curr->next) i++;
    return i;
}
//find the sum value of given urls's W(cp) value from T1..Tn in given position
double sum(List *list,int position, char *name)
{
    double output = 0;
    for(int i = 0; list[i] != NULL; i++)
    {
        if(isInList(name, list[i]) == FALSE) continue;
        output += absnum(name, list[i], position);
    }
    return output;
}
//calculate the W(c,p) value of given node in given list with given postion
double absnum(char *name, List T, int position)
{
    double output;
    double T_p = (double)FindPositionInList(name,T);
    double num_of_links_in_T = abs(NumOfLinks(T));
    output = T_p/num_of_links_in_T-(double)position/N;
    if(output < 0) output = output *-1;
    return output;
}
//min value in row
double minInRow(double **graph, int row)
{
    double min = graph[row][0];
    for(int i = 0; i < N; i++)
    {
        if(min > graph[row][i]) min = graph[row][i];
    }
    return min;
}
//check wheter the graph can be assigend successfully
int CanBeAssigned(double **graph)
{
    int *row = calloc(sizeof(int),N);
    int *col = calloc(sizeof(int),N);
    int number_of_zero = 0;

    for(int i = 0; i < N; i++)
    {
        for(int j = 0; j < N; j++)
        {
            if(graph[i][j] == 0 && col[j] == 0 && row[i] == 0)
            {
                number_of_zero++;
                col[j] = 1;
                row[i] = 1;
            }
        }
    }
    //if number of distinct zero is equal to N, return success
    if(number_of_zero == N) return TRUE;
    return FALSE;
}
//return urls name in given id
char *IdToName(int Id, List urls)
{
    int i = 0;
    for(Node curr = urls->first; curr != NULL; curr = curr->next)
    {
        if(i == Id)
        {
            //printf("%s->>curr\n",curr->name);
            return curr->name;
        }
        i++;
    }
    return NULL;
}
//find a path so that graph is assignable
void FindPath(double **graph)
{
    int *SelectRow = calloc(sizeof(int),N);
    int *SelectCol = calloc(sizeof(int),N);
    for(int i = 0; i < N; i++)
    {
        for(int j = 0; j < N; j++)
        {
            if(graph[i][j] == 0 && SelectRow[i] == FALSE && SelectCol[j] == FALSE)
            {
                //printf("row is %d, col is %d\n",i,j);
                SelectCol[j] = TRUE;
                SelectRow[i] = TRUE;
            }
        }
    }

    int *tickRow = calloc(sizeof(int),N);
    int *tickCol = calloc(sizeof(int),N);

    for(int i = 0; i < N; i++)
    {
        //tick unselected row
        if(SelectRow[i] == FALSE)
        {
            tickRow[i] = TRUE;

            for(int j = 0; j < N; j++)
            {
                //tick current row's zero's colum
                if(graph[i][j] == 0)
                    tickCol[j] = TRUE;    
            }
        }
    }

    double min = 1000;
    for(int i = 0; i < N; i++)
    {
        for(int j = 0; j < N; j++)
        {
            if(tickRow[i] == TRUE && tickCol[j] == FALSE)
            {
                if(min > graph[i][j])
                    min = graph[i][j];
            }
        }
    }

    for(int i = 0; i < N; i++)
    {
        for(int j = 0; j < N; j++)
        {
            if(tickRow[i] == TRUE)
            {
                graph[i][j] = graph[i][j] - min;
            }
            if(tickCol[j] == TRUE) 
            {
                graph[i][j] = graph[i][j] + min;
            }
        }
    }

    return;
}
//use Hungarian_algorithm to solve problem
void Hungarian(double **graph, int *P, char **urls)
{
    for(int i = 0; i < N; i++)
    {
        double min = minInRow(graph, i);
        for(int j = 0; j < N; j++)
        {
            graph[i][j] = graph[i][j] - min;
        }
    }

    if(CanBeAssigned(graph) == TRUE)
    {
        int *SelectRow = calloc(sizeof(int),N);
        int *SelectCol = calloc(sizeof(int),N);
        for(int i = 0; i < N; i++)
        {
            for(int j = 0; j < N; j++)
            {
                if(graph[i][j] == 0 && SelectRow[j] == 0 && SelectCol[i] == 0)
                {
                    P[j] = i;
                    SelectCol[j] = TRUE;
                    SelectRow[i] = TRUE;
                }
            }
        }
        return;
    }
    
    while(CanBeAssigned(graph) == FALSE)
    {
        FindPath(graph);
    }

    int *SelectRow = calloc(sizeof(int),N);
    int *SelectCol = calloc(sizeof(int),N);
    for(int i = 0; i < N; i++)
    {
        for(int j = 0; j < N; j++)
        {
            if(SelectRow[i] == TRUE || SelectCol[j] == TRUE) continue;

            if(graph[i][j] == 0)
            {
                P[j] = i;
                SelectCol[j] = TRUE;
                SelectRow[i] = TRUE;
            }
        }
    }
    return;
}
//freelist
void freeList(List list)
{
	Node curr = list->first;
	Node prev = NULL;
	while (curr != NULL)
	{
		prev = curr;
		curr = curr->next;
		free(prev);
	}
	free(list);
	return;
}
