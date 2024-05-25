/*****************************************************************//**
 * \file   loadfile.h
 * \brief ficheiro .h do loadfiles
 *
 * \author Teles
 * \date   May 2024
 *********************************************************************/


#pragma once


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <limits.h>



#pragma warning (disable: 4996)
 // Assuming a maximum length for nome
#define MAX_NAME_LENGTH 10
#define MAX_LINE_LENGTH 100

#pragma region 
typedef struct Adj {
    int cod;
    float dist;
    struct Adj* next;
}Adj;

typedef struct Vertice {
    int cod;
    char nome[MAX_NAME_LENGTH];
    bool visitado;
    struct Vertice* next;
    struct Adj* adjacentes;
}Vertice;


//Struct para usar no ficheiro binario
typedef struct AdjFile {
    int codOrigem;
    int codDestino;
    float weight;
} AdjFile;

typedef struct VerticeFile {
    int cod;
    char nome[MAX_NAME_LENGTH];
} VerticeFile;

#pragma region CreateGR

Vertice* createVertice(int cod, const char* nome);
Adj* createAdj(int cod, float dist);
Vertice* InsereVertice(Vertice* h, Vertice* novo, bool* res);
void addAdj(Vertice* vertice, Adj* adj);
Adj* InsereAdj(Adj* h, Adj* novo, bool* res);
void removeAdj(Vertice* vertice, int cod);
void removeVertice(Vertice* graph, int cod);
Vertice* InsereAdjacenteVerticeCod(Vertice* g, int codOrigem, int codDest, float peso, bool* res);
bool ExisteAdjacentes(Adj* h, int cod);
Vertice* DestroyGraph(Vertice* g);
Adj* DestroyAdj(Adj* h);
void MostraAdjacencias(Adj* h);
void MostraGrafo(Vertice* g);

#pragma endregion



#pragma region LOADGRAPH AND SAVEGRAPH
Vertice* LoadGraph(Vertice* h, const char* fileName, bool* res);
Vertice* LoadGraphBIN(Vertice* h, char* fileName, bool* res);
int SaveGraphBIN(Vertice* h, char* fileName);
int SaveAdjBIN(Adj* h, char* fileName, int codVerticeOrigem);
Vertice* LoadAdjBIN(Vertice* g, bool* res);
#pragma endregion


