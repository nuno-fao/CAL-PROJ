//
// Created by olive on 12/05/2020.
//

#ifndef CAL_PROJ_GRAPHFUNCS_H
#define CAL_PROJ_GRAPHFUNCS_H


#include "Graph.h"
#include "Node.h"
#include "Service.h"


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
 * Função que marca a garagem no grafo e utilizando cleanEdgesNVertex retorna o grafo acessivel a partir da mesma
 *
 * @param graph grafo a processar
 * @param city string que indica qual cidade a ler
 *
 * @return Vetor com os vertices accessiveis a partir da garagem.
 */
vector<Vertex<Node>*> readFromCityFile(Graph<Node> &graph, string city);

/**

 * Função que marca a garagem no grafo
 *
 * @param graph grafo contendo apenas nodes acessiveis
 * @param city string que indica em qual cidade estamos a trabalhar
 *
 * @return Uma cópia do grafo passado como argumento mas com os pontos de recolha devidamente marcados
 */
Service readService(vector<Vertex<Node>*> graph, string city);

/**
 * Função que guarda a informação num unordered map
 *
 * @param accessNodes nodes a processar
 * @param graph grafo a processar
 *
 * @return Vetor com os vertices accessiveis a partir da garagem.
 */

unordered_map<VertexPair, double> makeTable(vector<Vertex<Node> *> accessNodes, Graph<Node> graph);


/**
 * Função que ordena as edges a percorrer pelo veiculo
 *
 * @param service serviço a realizar
 * @param graph grafo a processar
 *
 * @return Vetor com as edges a percorrer, ordenadas.
 */
vector<Edge<Node> *> orderEdges(Service service, Graph<Node> graph);

/**
 * Função que atribui um caminho (edges) a um veiculo especifico, e esse veiculo a um serviço;
 *
 * @param service serviço a realizar
 * @param vehicle veiculo a atribuir ao serviço
 * @param graph grafo a processar
 *
 * @return nothing.
 */

void proccessService(Service service, Vehicle &vehicle, Graph<Node> graph);

#endif //CAL_PROJ_GRAPHFUNCS_H

