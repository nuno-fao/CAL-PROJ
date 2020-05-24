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
 * Função que ordena as edges a percorrer pelo veiculo
 *
 * @param service serviço a realizar
 * @param graph grafo a processar
 *
 * @return Vetor com as edges a percorrer, ordenadas.
 */
vector<Edge<Node>> orderEdges(Service service, Graph<Node> graph, vector<Vertex<Node>*> conexo);

/**
 * Função que atribui um caminho (edges) a um veiculo especifico, e esse veiculo a um serviço;
 *
 * @param service serviço a realizar
 * @param graph grafo a processar
 *
 * @return nothing.
 */

void proccessService(Service &service, Graph<Node> graph);

/**
 * Função para usar com o std::sort para ordenar o vetor de nodes;
 *
 * @param a vertex à esquerda
 * @param d vertex à direita
 *
 * @return true se a menor que d, false se o contrário.
 */
bool sortById(const Vertex<Node>* a,const Vertex<Node>* d);

/**
 * Função que faz pesquisa binária num vertexSet um vertex que contenha uma Node igual à target. ;
 *
 * @param vertexSet vetor a percorrer
 * @param target o que queremos encontrar
 * @param indInicio extremo esquerdo da procura no vetor
 * @param indFim extremo direito da procura no vetor
 *
 * @return apontador para o vertex deseja se encontrar, senão retorna nullptr.
 */
Vertex<Node>* vertexBinarySearch(vector<Vertex<Node>*> vertexSet, const Node &target, int indInicio, int indFim);


vector<Vertex<Node> *>sortPoints(Service service, Graph<Node> graph);

double pathCost(Graph<Node> graph, Vertex<Node> * origem, Vertex<Node> * destino);
#endif //CAL_PROJ_GRAPHFUNCS_H

