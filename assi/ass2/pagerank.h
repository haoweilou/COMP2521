// Graph.h ... interface to Graph ADT
// For 2521 assignment z5258575
// Written by Haowei Lou, 2019 July
#define GRAPH_H

#include <stdio.h>

// graph representation is hidden
typedef struct GraphRep *Graph;
typedef struct node *Node;
typedef struct list *List;
typedef struct prnode *Pnode;


typedef struct node {
	int vertex;		 // #vertices
 	struct node *next;
} node;

// graph representation ( List Representation)
typedef struct GraphRep {
	int nV;		 // #vertices
	int nE;		 // #edges
	int **edges; // Adjacency matrix
} GraphRep;

// node for prlist
typedef struct prnode {
	int index;		 
	double value;		 
	struct prnode *next; 
} prnode;

// list for the PR 
typedef struct list {
	struct prnode *head;		 // #vertices
	struct prnode *last; // List representations
} list;

// vertices denoted by integers 0..N-1
typedef int Vertex;

Graph newGraph (int nV);

List newList(int nV);
void insertPnode(Pnode node, List list);
