//
// Created by Nunation on 13/05/2020.
//

#ifndef CAL_PROJ_GRAPHVIEWERFUNCS_H
#define CAL_PROJ_GRAPHVIEWERFUNCS_H

#include "graphviewer.h"
#include "Node.h"
#include "Graph.h"
#include <cfloat>

/**
 * Le a informação de um grafo para um GraphViewer e dá display do mesmo numa forma básica.
 *
 * @param gv Objeto para onde será processado o grafo
 * @param graph Grafo a ser processado
 *
 * @return Returns true if successfull, false otherwise.
 */
GraphViewer* displayGraph( Graph<Node>& graph);

/**
 * Dá display no graphviewer de um grafo que corresponde a um CFC.
 *
 * @param graph conjunto de vertices pertencentes ao CFC
 *
 * @return nada.
 */
void displayGraphConexo( vector<Vertex<Node>*>& graph);

/**
 * Percorre o grafo identificar as coordinadas minimas e maximas .
 *
 * @param xMin coordenadas x minima
 * @param yMin coordenadas y minima
 * @param xMax coordenadas x maxima
 * @param yMax coordenadas y maxima
 * @param graph Grafo a percorrer
 *
 * @return Returns 0 successfull, -1 otherwise.
 */
int getMinMax(double &xMin,double &yMin, double &xMax, double &yMax , Graph<Node>& graph);

/**
 * Percorre o grafo identificar as coordinadas minimas e maximas desta vez, com um vetor de vertex.
 *
 * @param xMin coordenadas x minima
 * @param yMin coordenadas y minima
 * @param xMax coordenadas x maxima
 * @param yMax coordenadas y maxima
 * @param vec vetor a percorrer
 *
 * @return Returns 0 successfull, -1 otherwise.
 */
int getMinMaxVector(double &xMin,double &yMin, double &xMax, double &yMax , vector<Vertex<Node>*>& vec);

#endif //CAL_PROJ_GRAPHVIEWERFUNCS_H
