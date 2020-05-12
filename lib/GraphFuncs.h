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
 * @param graph referencia do objeto para onde se vai ler
 *
 * @return true if successfull, false otherwise.
 */
bool loadGraph(Graph<Node> &graph);

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


#endif //CAL_PROJ_GRAPHFUNCS_H

