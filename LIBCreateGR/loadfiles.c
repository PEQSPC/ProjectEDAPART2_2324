/*****************************************************************//**
 * \file   loadfiles.c
 * \brief LIB para manipular ficheiros
 *
 * \author Teles
 * \date   May 2024
 *********************************************************************/

#include <string.h>
#include <stdlib.h>
#include "loadfile.h"
#include "..\\ProjectMarceEDA\grafo.h"


#pragma region Create Graph

 /**
  * @brief Cria Vertice na memoria e adiciona a struct.
  *
  * @param cod  codigo do vertice
  * @param nome do vertice
  * @author teles
  *
  */
Vertice* createVertice(int cod, char* nome) {
    Vertice* novo = (Vertice*)malloc(sizeof(Vertice));
    if (novo == NULL) return NULL;
    novo->cod = cod;
    strcpy(novo->nome, nome);
    novo->visitado = false;
    novo->next = NULL;
    novo->adjacentes = NULL;
    return novo;
}
/**
 * @brief Cria Adj na memoria e adiciona a struct.
 *
 * @param cod  codigo do vertice
 * @param weight peso da adj
 * @author teles
 *
 */
Adj* createAdj(int cod, float weight) {
    Adj* novo = (Adj*)malloc(sizeof(Adj));
    if (novo == NULL) return NULL;
    novo->cod = cod;
    novo->dist = weight;
    novo->next = NULL;
    return novo;
}
/**
 * @brief Insere o Vertice na Struct.
 *
 * @param h  lista de vertices
 * @param novo vertice novo
 * @param res resposta da funcao
 * @author teles
 *
 */
Vertice* InsereVertice(Vertice* h, Vertice* novo, bool* res) {
    if (h == NULL) {
        *res = true;
        return novo;
    }
    Vertice* current = h;
    while (current->next != NULL) {
        current = current->next;
    }
    current->next = novo;
    *res = true;
    return h;
}

/**
 * @brief Adiciona adj na struct.
 *
 * @param h  lista de vertices
 * @param novo vertice novo
 * @param res resposta da funcao
 * @author teles
 *
 */
void addAdj(Vertice* vertice, Adj* adj) {
    adj->next = vertice->adjacentes;
    vertice->adjacentes = adj;
}

Adj* InsereAdj(Adj* h, Adj* novo, bool* res) {

    *res = false;		//por defeito � falso

    if (novo == NULL)	//Se novo adjacente � nulo, ignora opera��o
        return h;

    if (ExisteAdjacentes(h, novo->cod) == true) return h; // Se novo adj existe, ignorar operacao

    // Inserir nova adjacencia!
    *res = true;
    if (h == NULL) {	//Se lista de adjacencias � vazia, esta � a primeira adjacencia
        h = novo;
        return h;
    }
    //sen�o insere no in�cio das adjac�ncias! Podia ser de outra forma!
    novo->next = h;
    h = novo;

    return h;
}


/**
 * @brief Remove adj de um vertice.(Auxiliar)
 *
 * @param vertice  lista de vertices
 * @param cod codigo do vertice
 * @author teles
 *
 */
void removeAdj(Vertice* vertice, int cod) {
    Adj* current = vertice->adjacentes;
    Adj* previous = NULL;

    while (current != NULL && current->cod != cod) {
        previous = current;
        current = current->next;
    }

    if (current != NULL) {
        if (previous == NULL) {
            vertice->adjacentes = current->next;
        }
        else {
            previous->next = current->next;
        }
        free(current);
    }
}

/**
 * @brief Remove vertice da struct.
 *
 * @param vertice  lista de vertices
 * @param cod codigo do vertice
 * @author teles
 *
 */
void removeVertice(Vertice* graph, int cod) {
    Vertice* current = graph;
    Vertice* previous = NULL;

    while (current != NULL && current->cod != cod) {
        previous = current;
        current = current->next;
    }

    if (current != NULL) {
        if (previous == NULL) {
            graph = current->next;
        }
        else {
            previous->next = current->next;
        }

        // Remove all adjacencies to this vertex
        for (Vertice* v = graph; v != NULL; v = v->next) {
            removeAdj(v, cod);
        }

        // Free adjacencies of this vertex
        Adj* adj = current->adjacentes;
        while (adj != NULL) {
            Adj* temp = adj;
            adj = adj->next;
            free(temp);
        }
        free(current);
        //graph->numVertices--;
    }
}
/**
 * @brief Insere Adjacente no vertice pelo COD.
 *
 * @param g  lista de vertices
 * @param codOrigem codigo do vertice de origem
 * @param codDest codigo do vertice destino
 * @param peso da adj
 * @author lufer
 *
 */
Vertice* InsereAdjacenteVerticeCod(Vertice* g, int codOrigem, int codDest, float peso, bool* res) {

#pragma region Validacoes
    * res = false;				//por defeito e falso

    if (g == NULL) return g;	//<! se grafo esta vazio, ignora operacao

    Vertice* o = ProcuraVerticeCod(g, codOrigem);	//<! procura vertice origem
    Vertice* d = ProcuraVerticeCod(g, codDest);	//<! procura vertice destino
    if (o == NULL || d == NULL) return g;		//<! Se nao encontrou vertice origem e destino, ignora operacao

    if (ExisteAdjacentes(o->adjacentes, codDest) == true)
        return g; //Se ja foi registado esta adjacencia, ignorar a opera��o
#pragma endregion

    //g=InsereAdjacenteVertice(g, o->cidade, d->cidade, peso, res);

#pragma region Acoes
    //Insere nova adjacencia no vertice "Origem"
    Adj* novoAdj = createAdj(codDest, peso);
    o->adjacentes = InsereAdj(o->adjacentes, novoAdj, res);
    return g;
    //Se for n�o orientado
    //return (InsereAdjacenteVertice(g, dest, origem, peso, res));
#pragma endregion

}

/**
 * @brief	Verifica se determinado adj ja existe.
 *			Forma Recursiva
 *
 * @param h		Lista de Adjacencias
 * @param cod	Codigo a procurar
 * @return		Verdadeiro ou Falso
 * @author lufer
 *
 */
bool ExisteAdjacentes(Adj* h, int cod) {
    if (h == NULL) return false;
    if (h->cod == cod) return true;
    return ExisteAdjacentes(h->next, cod);
}
/**
 * @brief Destroi o grafo.
 *
 * @param g
 * @return struct vazia
 * @author teles
 *
 */
Vertice* DestroyGraph(Vertice* g) {
    if (g == NULL) return NULL;
    Vertice* aux = NULL;
    while (g) {
        if (g->next)
            aux = g->next;
        g->adjacentes = DestroyAdj(g->adjacentes);
        free(g);
        g = aux;
        aux = NULL;
    }
    return g;
}


/**
 * @brief Destroi todas as arestas.(Auxiliar)
 * @param h Adj Struct
 * @return struct vazia
 * @author teles
 *
 */
 /**
  * @brief .
  *
  * @param h
  * @return
  * @author lufer
  *
  */
Adj* DestroyAdj(Adj* h) {
    if (h == NULL) return NULL;
    Adj* aux = NULL;
    while (h) {
        if (h->next != NULL)
            aux = h->next;
        free(h);
        h = aux;
        aux = NULL;
    }
    return h;
}


/**
 * @brief Mostra lista de adjacentes.
 *
 * @param h struct h
 * @author teles
 *
 */
void MostraAdjacencias(Adj* h) {
    if (h == NULL) return;
    printf("\tAdj: %d - (%.0f)\n", h->cod, h->dist);
    MostraAdjacencias(h->next);
}
/**
 * @brief Apresenta grafo.
 *
 * @param g
 * @author lufer
 *
 */
void MostraGrafo(Vertice* g) {
    if (g == NULL) return;
    printf("V: %d - %s\n", g->cod, g->nome);
    MostraAdjacencias(g->adjacentes);
    MostraGrafo(g->next);
}

#pragma endregion

#pragma region LoadGraph and SaveGraph
/**
 * @brief Load do grafo para o programa por um ficheiro .txt ->Estrutura txt COD,NOME,CODADJ:PESO:CODADJ:PESO,
 *
 * @param h lista de Vertice
 * @param h nome do ficheiro
 * @param res reposta da funcao
 * @author teles
 *
 */
Vertice* LoadGraph(Vertice* h, const char* fileName, bool* res) {
    // Inicializar o resultado como falso
    *res = false;

    // Abrir o arquivo para leitura
    FILE* fp = fopen(fileName, "r");
    // Se não abrir o arquivo, mostrar o erro e returnar NULL
    if (fp == NULL) {
        perror("Falha ao abrir o arquivo");
        *res = false;
        return NULL;
    }

    char line[256]; // Buffer para ler linhas do arquivo
    // Ler o arquivo linha por linha
    while (fgets(line, sizeof(line), fp)) {
        // Dividir a linha em tokens usando a vírgula como delimitador
        char* token = strtok(line, ",");
        if (token == NULL) continue; // Se o primeiro token for NULL, continuar para a próxima linha

        // Converter o primeiro token em um inteiro (código do vértice)
        int cod = atoi(token);

        //o próximo token (nome do vértice)
        token = strtok(NULL, ",");
        if (token == NULL) continue; // Se o segundo token for NULL, continuar com a próxima linha

        char nome[MAX_NAME_LENGTH]; // Buffer para o nome do vértice
        // Copiar o nome do vértice para o buffer, assegurando de não ultrapassar o tamanho máximo
        strncpy(nome, token, MAX_NAME_LENGTH - 1);
        nome[MAX_NAME_LENGTH - 1] = '\0';

        // Criar um novo vértice com o código e o nome lidos em memoria
        Vertice* novo = createVertice(cod, nome);
        // Inserir o novo vértice no estrutura do grafo
        h = InsereVertice(h, novo, res);

        // Obter o próximo token para processar as adjacências
        token = strtok(NULL, ",");
        //Processar cada adjacência do vértice
        while (token != NULL) {
            // Dividir o token de adjacência em código e distância usando ':' como delimitador
            char* adjToken = strtok(token, ":");
            if (adjToken == NULL) break;

            // Convertimos o primeiro token de adjacência em um inteiro (código do vértice adjacente)
            int adjCod = atoi(adjToken);

            // Obtemos o próximo token (distância até a adjacência)
            adjToken = strtok(NULL, ":");
            if (adjToken == NULL) break;

            // Convertimos o segundo token de adjacência em um float (distância)
            float dist = atof(adjToken);

            // Criamos uma nova adjacência com o código e a distância
            Adj* adj = createAdj(adjCod, dist);
            // Adicionamos a adjacência ao vértice
            addAdj(novo, adj);

            // Obtemos o próximo token de adjacência
            token = strtok(NULL, ",");
        }

    }
    // Fechamos o arquivo
    fclose(fp);
    // Indicamos que o processo foi bem-sucedido
    *res = true;
    return h; // Retornamos o grafo atualizado
}



/**
 * @brief Carrega o grafo no ficheiro binario.
 *
 * @param h
 * @param filename
 * @param res
 * @author lufer
 *
 */
Vertice* LoadGraphBIN(Vertice* h, char* fileName, bool* res) {
    *res = false;
    FILE* fp = fopen(fileName, "rb");
    if (fp == NULL) return NULL;

    VerticeFile aux;
    Vertice* novo;
    while (fread(&aux, 1, sizeof(VerticeFile), fp)) {
        novo = createVertice(aux.cod, aux.nome);
        h = InsereVertice(h, novo, res);
    }
    fclose(fp);
    return h;
}
/**
 * @brief Load de Adjacencias de um Grafo. JA REVI!!!
 *
 * @param g
 * @param res
 * @return retorna vertice
 * @author lufer
 *
 */
Vertice* LoadAdjBIN(Vertice* g, bool* res) {
    *res = false;
    FILE* fp;
    if (g == NULL) return -1;
    AdjFile aux;
    Vertice* auxGraph = g;
    while (auxGraph) {
        fp = fopen(auxGraph->nome, "rb");
        if (fp != NULL) {
            while (fread(&aux, 1, sizeof(AdjFile), fp)) {
                g = InsereAdjacenteVerticeCod(g, aux.codOrigem, aux.codDestino, aux.weight, res);
            }
            fclose(fp);
        }
        auxGraph = auxGraph->next;
    }
    return g;
}
/**
 * @brief Grava Grafo em ficheiro binario.
 *
 * @param h
 * @param fileName
 * @return
 * @author lufer
 *
 */
int SaveGraphBIN(Vertice* h, char* fileName) {

    if (h == NULL) return -1;
    FILE* fp;
    int r;
    fp = fopen(fileName, "wb");
    if (fp == NULL) return -2;

    Vertice* aux = h;
    VerticeFile auxFicheiro;	//estrutura de vertice para gravar em ficheiro
    while (aux != NULL) {
        auxFicheiro.cod = aux->cod;
        strcpy(auxFicheiro.nome, aux->nome);
        fwrite(&auxFicheiro, 1, sizeof(VerticeFile), fp);
        //Pode gravar de imediato as adjacencias!
        if (aux->adjacentes) {
            r = SaveAdjBIN(aux->adjacentes, aux->nome, aux->cod);
            if (r < 0) break;
        }
        aux = aux->next;
    }
    fclose(fp);
    return 1;
}

/**
 * @brief Gravar Adj em ficheiro binario.
 *
 * @param h
 * @param fileName
 * @return
 * @author teles
 *
 */
int SaveAdjBIN(Adj* h, char* fileName, int codVerticeOrigem) {
    FILE* fp;
    if (h == NULL) return -2;
    fp = fopen(fileName, "wb");
    if (fp == NULL) return -1;

    Adj* aux = h;
    AdjFile auxFile;
    while (aux) {
        auxFile.codDestino = aux->cod;
        auxFile.codOrigem = codVerticeOrigem;
        auxFile.weight = aux->dist;
        fwrite(&auxFile, 1, sizeof(AdjFile), fp);
        aux = aux->next;
    }
    fclose(fp);
    return 1;
}

#pragma endregion

