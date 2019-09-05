//Name: Joshua Rony
//UserID: jrony
//Assignment Name: pa5




#include "List.h"

#ifndef Graph_H

#define Graph_H

#define INF -2

#define UNDEF -3

#define NIL -1



typedef struct GraphObject *Graph; //exported to Graph.c

Graph newGraph(int n);

int getOrder(Graph G);

int getSource(Graph G);

int getSize(Graph G);

int getDist(Graph G, int u);

int getParent(Graph G, int u);

void getPath(List L, Graph G, int u);

void makeNull(Graph G);

void addEdge(Graph G, int u, int v);

void addArc(Graph G, int u, int v);

void BFS(Graph G, int s);

void printGraph(FILE *out, Graph G);

void Peekaboo(Graph G);

void freeGraph(Graph *pG);

Graph copyGraph(Graph G);

Graph transpose(Graph G);

void DFS(Graph G, List S);

void printDFSLists(Graph G);

int getDiscover(Graph G, int u);

int getFinish(Graph G, int u);

//void PrintAdjacencies(Graph G);





#endif
