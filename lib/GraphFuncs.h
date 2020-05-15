//
// Created by olive on 12/05/2020.
//

#ifndef CAL_PROJ_GRAPHFUNCS_H
#define CAL_PROJ_GRAPHFUNCS_H


#include "Graph.h"
#include "Node.h"


/**
 * Funcao que le de um ficheiro para um grafo
 *
 * @param city string que indica qual cidade a ler
 *
 * @return grafo carregado.
 */
Graph<Node> loadGraph( string city);

/**
 * Função que calcula a distancia entre os dois nodes que a edge vai ligar.
 *
 * @param x1 X do node 1
 * @param y1 Y do node 1
 * @param x2 X do node 2
 * @param y2 Y do node 2
 *
 * @return Distancia entre os dois pontos.
 */
double getEdgeWeight(double x1,double y1, double x2, double y2);

/**
 * Função que limpa todas as arestas inuteis e consequentemente os vertex inacessiveis
 *
 * @param graph grafo a processar
 *
 * @return Vetor com os vertices accessiveis a partir da garagem.
 */
vector<Vertex<Node>*> cleanEdgesNVertex(Graph<Node> graph,Vertex<Node>* garage);

/**
 * Função que marca a garagem no grafo
 *
 * @param graph grafo a processar
 * @param city string que indica qual cidade a ler
 *
 * @return Vetor com os vertices accessiveis a partir da garagem.
 */
vector<Vertex<Node>*> readFromCityFile(Graph<Node> &graph, string city);

unordered_map<VertexPair, double> makeTable(vector<Vertex<Node> *> accessNodes, Graph<Node> graph);


#endif //CAL_PROJ_GRAPHFUNCS_H

