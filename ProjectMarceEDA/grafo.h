/*****************************************************************//**
 * \file   grafo.h
 * \brief
 *
 * \author Teles
 * \date   May 2024
 *********************************************************************/

#pragma once
#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <limits.h>
#include "/Users/gg/Downloads/ProjectMarceEDA/LIBCreateGR/loadfile.h"
#pragma comment(lib,"libs\\LIBCreateGR.lib")
#pragma warning (disable: 4996)


#pragma region DFT and Sum
Vertice* ProcuraVerticeCod(Vertice* g, int cod);
bool DepthFirstSearchRec(Vertice* g, int origem, int dest);
Vertice* ResetVerticesVisitados(Vertice* g);

//Auxiliar ao Dijkstra
#define MAX 5
#define MAXDISTANCE 9999

typedef struct Best {
    int distance[MAX];		//weight
    int anteriores[MAX];	//vertices cod
}Best;

//n total vertices , v initial vertice
Best BestPath(Vertice* g, int n, int v);

void ShowAllPath(Best b, int n, int v);
#pragma endregion

 

#pragma region Procura em Largura BFS
bool BreadthFirstSearch(Vertice* listaVertice, int verticeOrigem, int destino);
bool verificaFilaVazia(int* primeiro, int* ultimo);
bool removerFila(int fila[], int* ultimo, int* vertice);
bool inserirFila(int fila[], int* primeiro, int vertice);
#pragma endregion