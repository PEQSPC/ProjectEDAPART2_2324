/*****************************************************************//**
 * \file   main.c
 * \brief Projeto Principal
 *
 * \author Teles -23039 contact telesgomes96@gmail.com
 * \date   May 2024
 *********************************************************************/
#include "grafo.h"
#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <limits.h>

int main() {
    Vertice* graph = NULL;
    bool result;

    graph = LoadGraph(graph, "grafo.txt", &result);
    if (result) {
        printf("Grafo carregado com successo.\n");
        MostraGrafo(graph);
    }
    else {
        printf("Falha a gravar o grafo.\n");
    }

    // Save Graph Bin.
    int res1 = SaveGraphBIN(graph, "Vertices.bin");
    if (res1 > 0) puts("\nGrafo gravado em ficheiro Binario");

   
    graph = DestroyGraph(graph);
    puts("\nGrafo em memoria:");
    MostraGrafo(graph);


    graph = LoadGraphBIN(graph, "Vertices.bin", &result);
    if (graph != NULL) puts("\nVertices do Grafo lido de ficheiro\n");
    MostraGrafo(graph);

    puts("\nLer Adjacencias do grafo de ficheiro\n");
    graph = LoadAdjBIN(graph, &result);
    if (result = true)
    {
        printf("Adj lidas com sucesso no ficheiro Binario");
    }
    MostraGrafo(graph);



    printf("\nExiste Path?\n");
    bool existe = DepthFirstSearchRec(graph, 1, 3);
    printf("(DFSR) Existe Path entre %d e %d: %s\n", 1, 3, (existe == true ? "Sim" : "Nao"));


    graph = ResetVerticesVisitados(graph);

    bool existe2 = BreadthFirstSearch(graph, 1, 4);
    printf("(BFS) Existe Path entre %d e %d: %s\n", 2, 4, (existe2 == true ? "Sim" : "Nao"));
    graph = ResetVerticesVisitados(graph);
    //n total of Vertices
    //v initial vertice
   /* Best b = BestPath(graph, 5, 1);
    ShowAllPath(b, 5, 1);*/

    
    

    return 0;
}
