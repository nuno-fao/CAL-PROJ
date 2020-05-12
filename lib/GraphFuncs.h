//
// Created by olive on 12/05/2020.
//

#ifndef CAL_PROJ_GRAPHFUNCS_H
#define CAL_PROJ_GRAPHFUNCS_H

#endif //CAL_PROJ_GRAPHFUNCS_H

#include "Graph.h"
#include "Node.h"

/**
 * Funcao que le, de certos ficheiros txt, informacao de modo a gerar um grafo.
 *
 * @return Grafo gerado com a informacao dada.
 */
Graph<Node> loadGraph();

double getEdgeWeight(double x1,double y1, double x2, double y2);

