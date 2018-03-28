//Edward Lee
//Graph.c: Implements the Graph.h header file

//Include basic input and output, as well as the List code
#include <stdio.h>
#include <stdlib.h>
#include "Graph.h"
#include "List.h"

//Define the Graph Object
typedef struct GraphObj{
    List *adj;
    int *color;
    int *parent;
    int *discover;
    int *finish;
    int order;
    int size;
} GraphObj;

typedef GraphObj* Graph;

//newGraph(): Makes a new Graph. Color: 0 = white, 1 = grey, 2 = black
Graph newGraph(int n){
    Graph G = malloc(sizeof(GraphObj));
    G->adj = calloc(n+1, sizeof(List));
    G->color = calloc(n+1, sizeof(int));
    G->parent = calloc(n+1, sizeof(int));
    G->discover = calloc(n+1, sizeof(int));
    G->finish = calloc(n+1, sizeof(int));
    int i;
    for(i=1; i<=n; i++){
        G->adj[i] = newList();
        G->color[i] = 0;
        G->parent[i] = NIL;
        G->discover[i] = UNDEF;
        G->finish[i] = UNDEF;
    }
    G->order = n;
    G->size = 0;
    return (G);
}

//freeGraph: Frees the memory attached to a graph, including the arrays in the graph
void freeGraph(Graph* pG){
    int i=0;
    if(pG!=NULL && *pG!=NULL){
        makeNull(*pG);
        while(i<=getOrder(*pG)){
            freeList(&((*pG)->adj[i]));
            i++;
        }
        free((*pG)->adj);
        free((*pG)->color);
        free((*pG)->parent);
        free((*pG)->discover);
        free((*pG)->finish);
        free(*pG);
        pG = NULL;
    }
}

//getOrder: Returns the order of the current Graph
int getOrder(Graph G){
    if(G==NULL){
        printf("getOrder error: cannot getOrder on a null graph\n");
        exit(1);
    }else{
        return G->order;
    }
}

//getSize: Returns the size of the current Graph
int getSize(Graph G){
    if(G==NULL){
        printf("getSize error: cannot getSize on a null graph\n");
        exit(1);
    }else{
        return G->size;
    }
}

//getParent: Returns the parent Vertex of the specified vertex in the most recent DFS tree
int getParent(Graph G, int u){
    if((u>getOrder(G)) || (u<1)){
        printf("getParent error; u is either < 1 or > getOrder(G)\n");
        exit(1);
        return 0;
    }else{
        return G->parent[u];
    }
}

//getColor: Returns the color value of the specific vertex, in the most recent DFS
int getColor(Graph G, int u){
    if((u>getOrder(G)) || (u<1)){
        printf("getColor error: specified vertex is either <1 or > getOrder(G)\n");
        exit(1);
        return 0;
    }else{
        return G->color[u];
    }
}

//getDiscover: Returns the discover time of the specific vertex, in the most recent DFS
int getDiscover(Graph G, int u){
    if((u>getOrder(G)) || (u<1)){
        printf("getDiscover error: u is either < 1 or > getOrder(G)\n");
        exit(1);
        return 0;
    }else{
        return G->discover[u];
    }
}

//getFinish: Returns the finish time of the specific vertex, in the most recent DFS
int getFinish(Graph G, int u){
    if((u>getOrder(G)) || (u<1)){
        printf("getFinish error: u is either < 1 or > getOrder(G)\n");
        exit(1);
        return 0;
    }else{
        return G->finish[u];
    }
}



//makeNull: Empties the Graph
void makeNull(Graph G){
    if(G==NULL){
        printf("makeNull error: cannot makeNull on a null graph\n");
        exit(1);
    }else{
        int i = 1;
        while(i <= getOrder(G)){
            clear(G->adj[i]);
            G->color[i] = 0;
            G->parent[i] = NIL;
            G->discover[i] = UNDEF;
            G->finish[i] = UNDEF;
            i++;
        }
    }
}

//sortedadd: Helper function for inserting the edges in the Adjacency List in the proper order
void sortedadd(List L, int i){
    int j=1;
    if(length(L) == 0){
        append(L, i);
        return;
    }else{
        moveBack(L);
        while(j<=length(L)){
            if(get(L) <= i){
                insertAfter(L, i);
                return;
            }
            movePrev(L);
            j++;
        }
    prepend(L, i);  
    }
}

//addEdge: Adds an edge to the Graph between the specified vertices
void addEdge(Graph G, int u, int v){
    if((u>=1) && (u<=getOrder(G)) && (v>=1) && (v<=getOrder(G))){
        sortedadd(G->adj[u], v);
        sortedadd(G->adj[v], u);
        G->size++;
    }else{
        printf("addEdge error: cannot add edge that is beyond the limits of the graph G\n");
        exit(1);
    }
}

//addArc: Adds a directed edge from the specified vertex to the other
void addArc(Graph G, int u, int v){
    if((u>=1) && (u<=getOrder(G)) && (v>=1) && (v<=getOrder(G))){
        sortedadd(G->adj[u], v);
        G->size++;
    }else{
        printf("addArc error: cannot add edge that is beyond the limits of the graph G\n");
        exit(1);
    }
}

//DFS: Runs a depth-first search on the graph G, according to the input adjacency list S
void DFS(Graph G, List S){
    if(length(S) != getOrder(G)){
        printf("DFS error: the length of the input list S is not equal to the number of vertices N in G\n");
        exit(1);
    }
    int i;
    int STraverse=0;
    int* time;
    time = malloc(sizeof(int));
    *time = 0;
    for(i=1; i<=getOrder(G); i++){
        G->color[i] = 0;
        G->parent[i] = NIL;
        G->discover[i] = UNDEF;
        G->finish[i] = UNDEF;
    }
    moveFront(S);
    for(i=1; i<=getOrder(G); i++){
        STraverse=get(S);
        if(G->color[STraverse]==0){
            DFSVisit(G, S, STraverse, time);
        }
        moveNext(S);
    }
    for(i=1; i<=getOrder(G); i++){
        deleteBack(S);
    }
    free(time); //Free int pointer used to keep Time consistent throughout the recursive calls
}

//DFSVisit: Recursive portion of the DFS
void DFSVisit(Graph G, List S, int vertex, int* time){
    int liststep = 0;
    int vertexstep = 0;
    (*time)++;
    G->discover[vertex] = *time;
    G->color[vertex] = 1;
    if(length(G->adj[vertex])>0){
        moveFront(G->adj[vertex]);
        while(liststep<length(G->adj[vertex])){
            vertexstep = get(G->adj[vertex]);
            if(G->color[vertexstep] == 0){
                G->parent[vertexstep] = vertex;
                DFSVisit(G, S, vertexstep, time);
            }
            liststep++;
            moveNext(G->adj[vertex]);
        }
    }
    G->color[vertex] = 2;
    (*time)++;
    G->finish[vertex] = *time;
    prepend(S, vertex);
}

//transpose: Returns a new graph that is the transpose of the graph G
Graph transpose(Graph G){
    int root;
    int branch;
    int liststep;
    int i;
    Graph Transpose = newGraph(getOrder(G));
    for(i=1; i<=getOrder(G); i++){
        liststep = 0;
        if((length(G->adj[i]))>0){
            moveFront(G->adj[i]);
        }
        while(liststep<length(G->adj[i])){
            root = i;
            branch = get(G->adj[i]);
            addArc(Transpose, branch, root); //For each directed edge from u to v, make a new directed edge in the transpose graph from v to u
            liststep++;
            if(liststep<length(G->adj[i])){
                moveNext(G->adj[i]);
                continue;
            }
            break;
        }
    }
    return Transpose;
}

//copyGraph: Returns a new graph, identical to G
Graph copyGraph(Graph G){
    Graph copy = newGraph(getOrder(G));
    int root;
    int branch;
    int liststep;
    int i;
    for(i=1; i<=getOrder(G); i++){
        liststep = 0;
        if((length(G->adj[i]))>0){
            moveFront(G->adj[i]);
        }
        while(liststep<length(G->adj[i])){
            root = i;
            branch = get(G->adj[i]);
            addArc(copy, root, branch);
            liststep++;
            if(liststep<length(G->adj[i])){
                moveNext(G->adj[i]);
                continue;
            }
            break;
        }
    }
    return copy;
}

//calculateComponents: Calculates the strongly connected components of G and prints
void calculateComponents(FILE* out, Graph G){
    List GStack = newList();
    Graph GTranspose = transpose(G);
    int componentCount=0;
    int i;
    int j=1;
    List *components;
    for(i=1; i<=getOrder(G); i++){
        append(GStack, i);
    }
    //Run DFS on G and the transpose of G, using the Stack result from the first DFS to run the second
    DFS(G, GStack);
    DFS(GTranspose, GStack);
    for(i=1; i<=getOrder(GTranspose); i++){
        if(getParent(GTranspose, i) == NIL){
            componentCount++;
        }
    }
    components = calloc(componentCount+1, sizeof(List)); //Make a List array, containing the connected components of G
    moveFront(GStack);
    for(i=1; i<=componentCount; i++){ //Add the elements of GStack to components
        components[i] = newList();
        sortedadd(components[i], get(GStack));
        if(j<length(GStack)){
            moveNext(GStack);
            j++;
        }
        while((getParent(GTranspose, get(GStack)) != NIL)){
            sortedadd(components[i], get(GStack));
            if(j<length(GStack)){ 
                moveNext(GStack);
                j++;
                continue;
            }
            break;
        }
    }
    j=1;
    fprintf(out, "G contains %d strongly connected components:\n", componentCount); //Print the List array to the specified output
    for(i=componentCount; i>=1; i--){
        fprintf(out, "Component %d: ", j);
        j++;
        printList(out, components[i]);
        fprintf(out, "\n");
    }
    for(i=1; i<=componentCount; i++){
        freeList(&components[i]);
    }
    freeGraph(&GTranspose); //Free the allocated memory
    freeList(&GStack);
    free(components);
}

//printGraph: Prints the graph to the specified file
void printGraph(FILE* out, Graph G){
    int i = 1;
    while(i<=getOrder(G)){
        fprintf(out, "%d: ", i);
        printList(out, G->adj[i]);
        fprintf(out, "\n");
        i++;
    }
}
