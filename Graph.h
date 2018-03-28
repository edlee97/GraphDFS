/* Edward Lee
 * Graph.h: Header file for the Graph*/
#ifndef _GRAPH_H_INCLUDE_
#define _GRAPH_H_INCLUDE_
#include "List.h"
#define INF -1
#define NIL 0
#define UNDEF -3

typedef struct GraphObj* Graph;

int getOrder(Graph G);
int getSize(Graph G);
int getParent(Graph G, int u);
int getColor(Graph G, int u);
int getDiscover(Graph G, int u);
int getFinish(Graph G, int u);

void makeNull(Graph G);
void freeGraph(Graph* pG);
void addEdge(Graph G, int u, int v);
void addArc(Graph G, int u, int v);
void DFS(Graph G, List S);
void DFSVisit(Graph G, List S, int vertex, int* time);
void printGraph(FILE* out, Graph G);
void calculateComponents(FILE* out, Graph G);

Graph newGraph(int n);
Graph transpose(Graph G);
Graph copyGraph(Graph G);
#endif
