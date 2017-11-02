//Jesus Hernandez
//jherna83
//PA5
//Graph.h

#ifndef _GRAPH_H_INCLUDE_
#define _GRAPH_H_INCLUDE_

#include <stdio.h>
#include <stdlib.h>
#include "List.h"

#define NIL -420
#define UNDEF -69

typedef struct GraphObj* Graph;

/*~~~Constructors and Destructors~~~*/
Graph newGraph(int n);
void freeGraph(Graph* pG);

/*~~~Access Functions~~~*/
int getOrder(Graph G);
int getSize(Graph G);
int getParent(Graph G, int u);
int getDiscover(Graph G, int u);
int getFinish(Graph G, int u);

/*~~~Manipulation Functions~~~*/
void addEdge(Graph G, int u, int v);
void addArc(Graph G, int u, int v);
void DFS(Graph G, List S);

/*~~~Other functions~~~*/
Graph transpose(Graph G);
Graph copyGraph(Graph G);
void printGraph(FILE* out, Graph G);
void place(List L, int u);
#endif