//2521 Aissgement 2 pagerank.c
//Haowei Lou
//z5258575
//31 July 2019

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<assert.h>
#include "pagerank.h"

#define MAX_SIZE 1000
#define TRUE 1
#define FALSE 0

//function
void freeList(List);

int num_of_webpage(void);
int check_urls_index(char *input, char **name);

double **W_out(Graph graph);
double Wout_number(Vertex from, Vertex dest, Graph graph);
int number_of_outlinks(Vertex base, Graph graph);

double **W_in(Graph graph);
double Win_number(Vertex from, Vertex dest, Graph graph);
int number_of_inlinks(Vertex base, Graph graph);

List initial_list(int N);

double sum(int pi ,Graph graph ,double **Win, double **Wout, List oldlist);
double sum_diff(List newList,List oldlist);
double find_value_of_pnode(int index, List list);

void sortList(List);

static char **urls;

int main(int argc, char *argv[]) {
    if (argc < 4 )  
    {
        printf("Error input\n");
        return 0;
    }
    double d = atof(argv[1]);
    double diffPR = atof(argv[2]);
    int maxIterations  = atoi(argv[3]);
    //calculate #urls and create a graph
    FILE *collection = fopen("collection.txt","r");
    int N = num_of_webpage();
    Graph graph = newGraph(N);
    //store urls ' name in an array
    urls = malloc(sizeof(*urls)*N);
    for (int i = 0; i < N; i++)
    {
        urls[i] = malloc(MAX_SIZE);
        fscanf(collection,"%s",urls[i]);
    }

    for (int i = 0; i < N; i++)
    {
        char *file =malloc(strlen(urls[i]) + 4);
        strcpy(file,urls[i]);
        strcat(file,".txt");

        FILE *curr = fopen(file,"r");
        for(char temp[1000] = {0}; strcmp(temp,"#end") != 0;){
            fscanf(curr,"%s",temp);
            if(temp[0] != '#' && strcmp(temp,"Section-1")!=0){
                int n = check_urls_index(temp,urls);
                if(n != i) graph->edges[i][n] = 1;
            }
        }
        free(file);
        fclose(curr);
    }

    //create a link list
    double **Wout = W_out(graph);
    double **Win = W_in(graph);
    List newlist = initial_list(N);
    List oldlist = initial_list(N);

    double diff = diffPR;
    for(int i = 0; i < maxIterations && diff >= diffPR; i++)
    {

        for(Pnode curr = newlist->head; curr != NULL; curr = curr->next){
            curr->value = (1-d)/N + d*sum(curr->index, graph, Win, Wout, oldlist);
        }

        diff = sum_diff(newlist,oldlist);

        Pnode new = newlist->head, old = oldlist->head;
        for(int j = 0; j < N; j++)
        {
            old->value = new->value;
            new = new->next;
            old = old->next;
        }
            
    }

    sortList(newlist);
    FILE *output = fopen("pagerankList.txt", "w");
    for(Pnode curr = newlist->head; curr != NULL; curr = curr->next){
        int i = curr->index;
        int num_out = number_of_outlinks(i, graph);
        fprintf(output,"%s, %d, %.7lf\n",urls[i], num_out, curr->value);
    }
    fclose(output);

    freeList(oldlist);
    freeList(newlist);
    free(graph);

    return 0;
}

//create new graph
Graph newGraph (int nV)
{
	assert (nV > 0);

	GraphRep *new = malloc (sizeof *new);
	assert (new != NULL);
	new->nV = nV;
	new->nE = 0;

	new->edges = calloc ((size_t) nV, sizeof (int *));
	assert (new->edges != NULL);
	for (int v = 0; v < nV; v++) {
		new->edges[v] = calloc ((size_t) nV, sizeof (int *));
	}

	return new;
}

void freeList(List list)
{
	Pnode curr = list->head;
	Pnode prev = NULL;
	while (curr != NULL)
	{
		prev = curr;
		curr = curr->next;
		free(prev);
	}
	free(list);
	return;
}

List newList(int v)
{
	List new = malloc(sizeof(*new));

	new->head = NULL;
	new->last = NULL;

	return new;
}

void insertPnode(Pnode node, List list)
{
	if(list->head == NULL){
		list->head = node;
		list->last = node;
		return;
	}

	list->last->next = node;
	list->last = node;
	return;
}


//count number of webpages in collecion.txt
int num_of_webpage(void)
{
    int N = 0;
    FILE *file = fopen("collection.txt","r");
    for(char filename[1000]; fscanf(file,"%s",filename) != EOF;)
        N++;
    return N;
}
//chek urls's index in the name array
int check_urls_index(char *input, char **name)
{
    for(int i = 0; name[i] != NULL; i++)
    {
        if(strcmp(input,name[i]) == 0)
        {
            return i;
        }
    }
    return -1;
}
//calculate Wout and return the whole graph's wout numebr as an 2D-array
double **W_out(Graph graph)
{
    int N = graph->nV;
    double **output = calloc(N,sizeof(output));
    for(int i = 0; i < N; i++){
        output[i] = calloc(N,sizeof(double *));
    }
    for(int i = 0; i < N; i++)
    {
        for(int j = 0; j < N; j++)
        {
           if(i != j && graph->edges[i][j] == 1) output[i][j] = Wout_number(i,j,graph);
           else output[i][j] = -1;
        }
    }
    
    return output;
}
//calcute the Wout for particular two vertex
double Wout_number(Vertex from, Vertex dest, Graph graph)
{
    double Ou = (double)number_of_outlinks(dest, graph);
    if(Ou == 0) Ou = 0.5;
    double Op = 0;

    for(int i = 0; i < graph->nV; i++)
    {
        if(i != from && graph->edges[from][i] == 1)
        {
            double n = (double)number_of_outlinks(i,graph);
            if(n == 0) n = 0.5;
            Op = Op + n;
        }
    }

    if(Op == 0) Op = 0.5;
    return Ou/Op;
}
//count number of outlinks for a vertex
int number_of_outlinks(Vertex base, Graph graph)
{
    int output = 0;
    for(int i = 0; i < graph->nV; i++){
        if(graph->edges[base][i] == 1 && i != base) output++;
    }
    return output;
}
//calculate Win and return the whole graph's win numebr as an 2D-array
double **W_in(Graph graph)
{
    int N = graph->nV;
    double **output = calloc(N,sizeof(output));

    for(int i = 0; i < N; i++){
        output[i] = calloc(N,sizeof(double *));
    }

    for(int i = 0; i < N; i++)
    {
        for(int j = 0; j < N; j++)
        {
           if(i != j && graph->edges[i][j] == 1) output[i][j] = Win_number(i,j,graph);
           else output[i][j] = -1;
        }
    }

    return output;
}
//calcute the Win for particular two vertex
double Win_number(Vertex from, Vertex dest, Graph graph)
{
    double Iu = (double)number_of_inlinks(dest, graph);
    if(Iu == 0) Iu = 0.5;
    double Ip = 0;

    for(int i = 0; i < graph->nV; i++) 
    {
        if(i != from && graph->edges[from][i] == 1)
        {
            double n = (double)number_of_inlinks(i,graph);
            if(n == 0) n = 0.5;
            Ip = Ip + n;
        }

    }

    if(Ip == 0) Ip = 0.5;
    return Iu/Ip;

}
//count number of inlinks for a vertex
int number_of_inlinks(Vertex base, Graph graph)
{
    int output = 0;
    for(int i = 0; i < graph->nV; i++){
        if(graph->edges[i][base] == 1 && i != base) output++;
    }
    return output;
}
//initial a list and assign the value t = 0 to this list
List initial_list(int N) 
{
    List list = newList(N);
    for (int i = 0; i < N; i++)
    {
        Pnode new = malloc(sizeof(new));
        new->next = NULL;
	    new->index = i;
        new->value = (double)1/N;

        insertPnode(new, list);
    }
    return list;
}
//calculate and return the sum of PR(pj,t)*Wout*Win
double sum(int pi ,Graph graph ,double **Win, double **Wout, List oldlist)
{
    double output = 0;
    for(int pj = 0; pj < graph->nV; pj++)
    {
        if(graph->edges[pj][pi] == 1 && pj != pi) 
            output = output + find_value_of_pnode(pj, oldlist)*Wout[pj][pi]*Win[pj][pi];
    }

    return output;
}
//calculate the PR value for node who have same index
double find_value_of_pnode(int index, List list)
{
    int i = 0;
    for(Pnode curr = list->head; curr != NULL ; curr = curr->next) 
    {
        if(i == index) return curr->value;
        i++;
    }
    return -1;
}
//calculate the sum difference
double sum_diff(List newList,List oldlist) 
{
    double output = 0;
    for(Pnode new = newList->head, old = oldlist->head; new != NULL; new = new->next, old = old->next){
        double temp = new->value - old->value;
        if(temp < 0) temp = -1*temp;
        output += temp;
    }

    return output;
}
//use bubble sort to sort the list as given format
void sortList(List newlist)
{
    for (Pnode curr = newlist->head; curr != NULL; curr = curr->next)
    {
        for(Pnode now = newlist->head; now->next != NULL; now = now->next)
        {
            if(now->value < now->next->value)
            {
                double value = now->next->value;
                int index = now->next->index;
                now->next->value = now->value;
                now->next->index = now->index;
                
                now->value = value;
                now->index = index;
            }
        }
    }
    return;
}
