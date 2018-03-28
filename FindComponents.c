//Edward Lee
//FindComponents: Creates a graph from an input file and prints its strongly connected components to an output file
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"Graph.h"
int main(int argc, char* argv[]){
    FILE* in;
    FILE* out;
    int temp1;
    int temp2 = 1;
    if(argc != 3){
        printf("Usage error. %s <input file> <output file>\n", argv[0]);
        exit(1);
    }
    in = fopen(argv[1], "r");
    if(in==NULL){
        printf("unable to read from file %s\n", argv[1]);
        exit(1);
    }
    out = fopen(argv[2], "w");
    if(out==NULL){
        printf("unable to write to file %s\n", argv[2]);
        exit(1);
    }
    fscanf(in, "%d", &temp1);
    Graph G = newGraph(temp1);
    while(temp1 != 0){
        fscanf(in, "%d %d", &temp1, &temp2);
        if((temp1 != 0) && (temp2 != 0)){
            addArc(G, temp1, temp2);
        }
    }
    fprintf(out, "Adjacency List representation of G:\n");
    printGraph(out, G);
    fprintf(out, "\n");
    calculateComponents(out, G);
    freeGraph(&G); //Free memory used and close the files
    fclose(in);
    fclose(out);
    return 1;
}
