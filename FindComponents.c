//Jesus Hernandez
//jherna83
//PA5
//FindComponents.c

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Graph.h"
#include "List.h"

int main(int argc, char* argv[])
{
	if(argc > 3 || argc < 3)
	{
		printf("Usage: %s [inputFile] [OutputFile]", argv[0]);
	}

	FILE* inFile;
	FILE* outFile;

	inFile = fopen(argv[1], "r");
	outFile = fopen(argv[2], "w");


    if(inFile == NULL)
    {
        printf("Unable to open file %s for reading\n", argv[1]);
        exit(1);
    }
    else if(outFile == NULL)
    {
        printf("Unable to open file %s for writing\n", argv[2]);
        exit(1);
    }

    int vertex;
    //grabs the value that represents the number of vertecies
    fscanf(inFile, "%d", &vertex);
    Graph G = newGraph(vertex);

    int u, v; //using the same veriables from Graph ADT to represent verticies

    //grab the values of the verticies and start adding the edges/verticies.
    while(fscanf(inFile, "%d %d", &u, &v) == 2)
    {
        if(u == 0 && v == 0)
        {
            break;
        }
        else
        {
            addArc(G, u, v);
        }
    }
    fprintf(outFile, "Adjacency list representation of G:\n");
    printGraph(outFile, G);
    fprintf(outFile,"\n" );

    List L = newList();

    for(int i = 1; i <= vertex; i++)
    {
    	append(L, i);
    }

    //run DFS for the first time then run again on the transpose
    DFS(G, L);
    Graph tG = transpose(G);
    DFS(tG, L);

    //this part finds the number of connected components
    int SCnum = 0; //number of strongly connected comp.
    moveFront(L);

    while(index(L) >= 0)
    {
    	if(getParent(tG, get(L)) == NIL)
    	{
    		SCnum++;
    	}
    	moveNext(L);
    }

    //create an array of lists that will hold all the components
    List componentL[SCnum];

    for(int i = 0; i < SCnum; i++)
    {
    	componentL[i] = newList();
    }

    //starting from the back of the stack, the elements will be taken 
    //and placed in the array of lists containing. Break out once vert
    //is equal to number of strong components
    int vert = 0;
    moveBack(L);
    while(index(L) >= 0)
    {
    	prepend(componentL[vert], get(L));
    	if(getParent(tG, get(L)) == NIL)
    	{
    		vert++;
    	}
    	if(vert == SCnum)
    	{
    		break;
    	}
    	movePrev(L);
    }

    //this part prints out the SCC
    fprintf(outFile, "G contains %d strongly connected components:\n", SCnum);
    for(int i = 0; i < SCnum; i++)
    {
    	fprintf(outFile, "Component %d:", (i+1));
    	printList(outFile, componentL[i]);
    	fprintf(outFile, "\n");
    	freeList(&(componentL[i]));
    }

    freeList(&L);
    freeGraph(&G);
    freeGraph(&tG);
    fclose(inFile);
    fclose(outFile);
}