/*****************************************************************//**
 * \file   grafo.c
 * \brief ficheiro com algoritmos de dft sum bfs and bestpath
 *
 * \author Teles
 * \date   May 2024
 *********************************************************************/

#include <string.h>
#include <stdlib.h>
#include "grafo.h"

#pragma region DFT and Sum
/**
 * @brief	Dijkstraos Algorithm.
 * @param adjMatrix
 * @param n			total of Vertices
 * @param v			initial vertice
 * @return
 * @author lufer
 *
 */
Best BestPath(Vertice* g, int n, int v) {

    int cost[MAX][MAX], distance[MAX], pred[MAX];
    int visited[MAX], count, mindistance, nextnode, i, j;

    //pred[] guarda o vertice anterior ao atual
    //count numero de nodos visitados ate ao momento
    //cria matriz de custos a partir da matriz de adjacencias

    //inicializa��es matriz de custos
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            cost[i][j] = MAXDISTANCE;

    //Colocar custos efectivos
    Vertice* aux = g;
    while (aux) {
        if (aux->adjacentes) {
            Adj* auxAdj = aux->adjacentes;
            while (auxAdj) {
                cost[aux->cod][auxAdj->cod] = auxAdj->dist;
                auxAdj = auxAdj->next;
            }
        }
        aux = aux->next;
    }

    //pred[],distance[] and visited[]
    aux = g;
    while (aux) {
        distance[aux->cod] = cost[v][aux->cod];
        pred[aux->cod] = v;
        visited[aux->cod] = 0;
        aux = aux->next;
    }


    distance[v] = 0;
    visited[v] = 1;
    count = 1;
    nextnode = 0;
    while (count < n - 1)
    {
        mindistance = MAXDISTANCE;
        //nextnode e o vertice e menor distancia do atual
        for (i = 0; i < n; i++)
        {
            if (distance[i] < mindistance && !visited[i])
            {
                mindistance = distance[i];
                nextnode = i;
            }
        }

        //Verifica se existe um melhor caminho
        visited[nextnode] = 1;
        for (i = 0; i < n; i++) {
            if (!visited[i])
                if (mindistance + cost[nextnode][i] < distance[i])
                {
                    distance[i] = mindistance + cost[nextnode][i];
                    pred[i] = nextnode;
                }
        }
        count++;
    }
    //Devolve resultados
    Best b;
    for (int i = 0; i < n; i++) {
        b.anteriores[i] = pred[i];
        b.distance[i] = distance[i];
    }
    return b;
}
/*
Auxiliar
*/
void ShowAllPath(Best b, int n, int v) {
    int j;
    for (int i = 0; i < n; i++)
        if (i != v)
        {
            printf("\nDistancia ate ao vertice %d = %d", i, b.distance[i]);
            printf("\nPath = %d", i);

            j = i;
            do
            {
                j = b.anteriores[j];
                printf(" <- %d", j);
            } while (j != v);
        }
}

bool DepthFirstSearchRec(Vertice* g, int origem, int dest)
{
    int j;
    if (origem < 1) return false;
    if (origem == dest) return true;

    Vertice* aux = ProcuraVerticeCod(g, origem);
    aux->visitado = true;
    //printf(" Vertice: %s : %d\n", aux->cidade, aux->cod);

    Adj* adj = aux->adjacentes;
    while (adj) {
        Vertice* aux = ProcuraVerticeCod(g, adj->cod);
        if (aux->visitado == false)
        {
            bool existe = DepthFirstSearchRec(g, adj->cod, dest);
            return existe;
        }
        else
            aux = aux->next;
    }
    return true;
}
Vertice* ProcuraVerticeCod(Vertice* g, int cod) {
    if (g == NULL) return NULL;
    if (g->cod == cod) return g;
    return(ProcuraVerticeCod(g->next, cod));
}
Vertice* ResetVerticesVisitados(Vertice* g) {
    Vertice* aux = g;
    while (aux) {
        aux->visitado = false;
        aux = aux->next;
    }
    return g;
}

#pragma endregion

#pragma region Procura em Largura BFS

bool inserirFila(int fila[], int* primeiro, int vertice) {

    fila[*primeiro] = vertice;

    *primeiro = *primeiro + 1;

    return true;
}

bool removerFila(int fila[], int* ultimo, int* vertice) {

    *vertice = fila[*ultimo];

    *ultimo = *ultimo + 1;

    return true;
}

bool verificaFilaVazia(int* primeiro, int* ultimo) {

    if (*primeiro == *ultimo) return true;

    return false;

}


bool BreadthFirstSearch(Vertice* listaVertice, int verticeOrigem, int destino) {

    int fila[300];

    if (verticeOrigem == destino) return true;
    bool res = false;

    int primeiro = 0;
    int ultimo = primeiro;
    int origem;

    Vertice* auxOrigem = listaVertice;
    Vertice* auxVertice = auxOrigem;

    while (auxOrigem != NULL && auxOrigem->cod != verticeOrigem) {
        auxOrigem = auxOrigem->next;
    }
    if (auxOrigem == NULL) return false;

    res = inserirFila(fila, &primeiro, auxOrigem->cod);

    if (res == false) return false;

    auxOrigem->visitado = true;

    while (verificaFilaVazia(&primeiro, &ultimo) == false)
    {
        res = removerFila(fila, &ultimo, &origem);
        if (res == false) return false;

        if (origem == destino) return true;

        Vertice* auxOrigem = listaVertice;

        while (auxOrigem != NULL && auxOrigem->cod != origem) {
            auxOrigem = auxOrigem->next;
        }
        if (auxOrigem == NULL) return false;

        Adj* auxAresta = auxOrigem->adjacentes;

        while (auxAresta != NULL)
        {
            Vertice* auxOrigem = listaVertice;

            while (auxOrigem != NULL && auxOrigem->cod != auxAresta->cod) {
                auxOrigem = auxOrigem->next;
            }

            if (auxOrigem == NULL) return false;

            if (auxOrigem->visitado == false) {
                res = inserirFila(fila, &primeiro, auxAresta->cod);
                if (res == false) return false;
                auxOrigem->visitado = true;
            }

            auxAresta = auxAresta->next;

        }
    }
    return false;
}



#pragma endregion

