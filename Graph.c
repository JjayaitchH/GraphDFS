//Jesus Hernandez
//jherna83
//PA5
//Graph.c
//this Graph.c was copied over from PA4 and fixed to fit the needs of PA5

#include <stdio.h>
#include <stdlib.h>
#include "Graph.h"

void visit(Graph G, List S, int u, int *time);

typedef struct GraphObj
{ 
    char* color;
    int*  parentV;
    int* distance;
    int* discover;
    int* finish;
    List* row;
    int size;
    int order;
}GraphObj;

//~~~Consructors and Destructors~~~

//returns Graph pointing to newly created GraphObj
//n = number ov verticies
//contains no edges
Graph newGraph(int n)
{
    if(n < 1)
    {
        printf("Error when calling newGraph. order of graph cannot be less than 1");
        exit(1);
    }
    Graph G = malloc(sizeof(GraphObj));

    G -> color = malloc((n + 1) * sizeof(char));
    G -> parentV = malloc((n + 1) * sizeof(int));
    G -> distance = malloc((n + 1) * sizeof(int));
    G -> discover = malloc((n + 1) * sizeof(int));
    G -> finish = malloc((n + 1) * sizeof(int));
    G -> row = malloc((n + 1) * sizeof(List));

    for(int i = 1; i <= n; i++)
    {
        G -> color[i] = 'w';
        G -> parentV[i] = NIL;
        G -> discover[i] = UNDEF;
        G -> finish[i] = UNDEF;
        G -> row[i] = newList();
    }

    G -> size = 0;
    G -> order = n;

    return G;
}

//free all dynamic memory in graph
void freeGraph(Graph* pG)
{
    if(pG != NULL && *pG != NULL)
    {


        for(int i = 1; i <= getOrder(*pG); i++)
        {
            freeList(&(*pG) -> row[i]);
        }
        free((*pG) -> color);
        free((*pG) -> parentV);
        free((*pG) -> discover);
        free((*pG) -> finish);
        free((*pG) -> row);

        free(*pG);
        *pG = NULL;
    }
}

//~~~Access Functions~~~
//returns the order of the graph
//Pre: Graph must not be NULL
int getOrder(Graph G)
{
    if(G == NULL)
    {
        printf("Error when calling getOrder. Graph is NULL\n");
        exit(1);
    }
    return G -> order;
}

//returns the size of the Graph
//Pre: Graph must not be NULL
int getSize(Graph G)
{
    if(G == NULL)
    {
        printf("Error when calling getSize. Graph is NULL\n");
        exit(1);
    }
    return G -> size;
}

//will return the parent of vertex u
//Pre: Graph must not be NULL and vertex u cannot be greater than order or less than 1
int getParent(Graph G, int u)
{
    if(G == NULL)
    {
        printf("Error when calling getParent. Graph is NULL\n");
        exit(1);
    }
    else if(u > getOrder(G) || u < 1)
    {
        printf("Error when calling getParent. Vertex is invalid\n");
        exit(1);
    }
    return G -> parentV[u];
}

//get the discover time of vertex u
//Pre: Graph must not be NULL and vertex u cannot be greater than order or less than 1
int getDiscover(Graph G, int u)
{
	if(G == NULL)
	{
		printf("Error when calling getDiscover. Graph is NULL\n");
		exit(1);
	}
	else if(u > getOrder(G) || u < 1)
	{
		printf("Error when calling getDiscover. Vertex is invalid\n");
		exit(1);
	}

	return G -> discover[u];

}

int getFinish(Graph G, int u)
{
	if(G == NULL)
	{
		printf("Error when calling getFinish. Graph is NULL\n");
		exit(1);
	}
	else if(u > getOrder(G) || u < 1)
	{
		printf("Error when calling getFinish. Vertex is invalid\n");
		exit(1);
	}

	return G -> finish[u];
}

//~~~End Access Functions 

//~~~Start Manipulation Functions~~~

//inserts new edge joining u and v
////pre: Graph must not be NULL and vertex u and v cannot be greater than order or less than 1
void addEdge(Graph G, int u, int v)
{
    if(G == NULL)
    {
        printf("Error when calling addEdge. Graph is NULL\n");
        exit(1);
    }
    else if(u > getOrder(G) || u < 1)
    {
        printf("Error when calling addEdge. Invalid Vertex\n");
        exit(1);
    }
    else if(v > getOrder(G) || v < 1)
    {
        printf("Error when calling addEdge. Invalid Vertex\n");
        exit(1);
    }

    List tempU = G -> row[u];
    place(tempU, v);

    List tempV = G -> row[v];
    place(tempV, u);

    G -> size++;
}

//add new directed edge from u to v
//pre: Graph must not be NULL and vertex u and v cannot be greater than order or less than 1
void addArc(Graph G, int u, int v)
{
    if(G == NULL)
    {
        printf("Error when calling addArc. Graph is NULL\n");
        exit(1);
    }
    else if(u > getOrder(G) || u < 1)
    {
        printf("Error when calling addArc. Invalid Vertex\n");
        exit(1);
    }
    else if(v > getOrder(G) || v < 1)
    {
        printf("Error when calling addArc Invalid Vertex\n");
        exit(1);
    }

    List temp = G -> row[u];
    place(temp, v);

    G -> size++;
}

//the DFS algorithm
//pre: Graph must not be NULL
void DFS(Graph G, List S)
{
	if(G == NULL)
    {
        printf("Error when calling DFS. Graph is NULL\n");
        exit(1);
    }
    for(int i = 1; i <= getOrder(G); i++)
    {
    	G -> color[i] = 'w';
    	G -> parentV[i] = NIL;
    }
    int time = 0;

    moveBack(S);
    for(int i = 1; i <= length(S); i++)
    {
    	int u = front(S);
    	if(G -> color[u] == 'w')
    	{
    		visit(G, S, u, &time);
    	}
    	deleteFront(S);
    }
}
/*~~~End Manipulation Procedures~~~*/
//Returns new graph which is the transpose of the original
//Pre: Graph must not be NULL
Graph transpose(Graph G)
{
	if(G == NULL)
    {
        printf("Error when calling transpose. Graph is NULL\n");
        exit(1);
    }

    Graph tG = newGraph(getOrder(G));
    if(getOrder(G) != 0)
    {
	    for(int i = 1; i <= getOrder(G); i++)
	    {
	    	if(length(G -> row[i]) != 0)
	    	{
		    	moveFront(G -> row[i]);
		    	while(index(G -> row[i]) >= 0)
		    	{
		    		addArc(tG, get(G -> row[i]), i);
		    		moveNext(G -> row[i]);
		    	}
	    	}
		}
	}
    return tG;	
}

//Returns a copy of the graph
//Pre: Graph must not be NULL
Graph copyGraph(Graph G)
{
	if(G == NULL)
    {
        printf("Error when calling copyGraph. Graph is NULL\n");
        exit(1);
    }
    Graph cG = newGraph(getOrder(G));

    if(getOrder(G) != 0)
    {
	    for(int i = 1; i <= getOrder(G); i++)
	    {
	    	if(length(G -> row[i]) != 0)
	    	{
		    	moveFront(G -> row[i]);
		    	while(index(G -> row[i]) >= 0)
		    	{
		    		addArc(cG, i, get(G -> row[i]));
		    		moveNext(G -> row[i]);
		    	}
	    	}
		}
	}
    return cG;
}   

//~~~Other functions~~~
//function printGraph prints out the graph
//pre: Graph must not be NULL
void printGraph(FILE* out, Graph G)
{
    if(G == NULL)
    {
        printf("Error when calling printGraph. Graph is NULL\n");
        exit(1);
    }
    for(int i = 1; i <= getOrder(G); i++)
    {
        List L = G -> row[i];
        fprintf(out, "%d: ", i);
        printList(out, L);
        fprintf(out, "\n");
    }
}

//this is a helper function I made that helps place a vertex
//in a list. I used this code for both addEdge and addArc but realized
//it would look much better if I made an actual funtion 
void place(List L, int u)
{
    if(length(L) == 0)
    {
        append(L, u);
        return;
    }

    moveFront(L);
    while(index(L) >= 0)
    {
        if(get(L) < u)
        {
            moveNext(L);
        }
        else
        {
            break;
        }
    }
    if(index(L) != -1)
    {
        insertBefore(L, u);
    }
    else
    {
        append(L, u);
    }
}

void visit(Graph G, List S, int u, int *time)
{
	G -> discover[u] = ++*time;
	G -> color[u] = 'g';
	if(length(G -> row[u]) != 0)
	{
		for(moveFront(G -> row[u]); index(G -> row[u]) >= 0; moveNext(G -> row[u]))
		{
			int v = get(G -> row[u]);
			if(G -> color[v] == 'w')
			{
				G -> parentV[v] = u;
				visit(G, S, v, time);
			}
		}
	}
	G -> color[u] = 'b';
	G -> finish[u] = ++*time;
	insertAfter(S, u);
}