//
// Created by olive on 12/05/2020.
//

#include <fstream>
#include <sstream>
#include <cmath>
#include <iostream>
#include <algorithm>
#include "GraphFuncs.h"

using namespace std;

bool loadGraph(Graph<Node> &graph){

    ifstream coordFile, edgeFile, tagFile;

    coordFile.open("../mapas/Porto/nodes_x_y_porto.txt");

    if(!coordFile) {
        cout << "Couldn't open coordinates file!" << endl;
        return false;
    }

    edgeFile.open("../mapas/Porto/edges_porto.txt");

    if(!edgeFile) {
        cout << "Couldn't open edge file!" << endl;
        return false;
    }

    tagFile.open("../mapas/Porto/t02_tags_porto.txt");

    if(!tagFile) {
        cout << "Couldn't open tags file!" << endl;
        return false;
    }

    //-------------------------------READ VERTEX----------------------

    int numNodes;
    coordFile >> numNodes;

    string line;

    // to clear the newline
    getline(coordFile, line);


    while(getline(coordFile, line)) {

        // gets rid of the parentheses
        size_t pos = line.find(')');
        if (pos != string::npos)
            line = line.substr(1, pos);

        // gets rid of the commas
        line.erase(remove(line.begin(), line.end(), ','), line.end());


        int id;
        double x, y;
        stringstream linestream(line);
        linestream >> id >> x >> y;


        // add node to vertex
        graph.addVertex(Node(id, x, y));
    }


    if(graph.getVertexSet().size() != numNodes) {
        cout << "Number of nodes in the graph is wrong! ";
        cout << graph.getVertexSet().size() << " instead of " << numNodes << "." << endl;
        return false;
    }



    //------------------------READ EDGES-----------------------------

    int numEdges;
    edgeFile >> numEdges;

    // to clear the newline
    getline(edgeFile, line);


    while(getline(edgeFile, line)) {

        // gets rid of the parentheses
        size_t pos = line.find(')');
        if (pos != string::npos)
            line = line.substr(1, pos);


        // gets rid of the commas
        line.erase(remove(line.begin(), line.end(), ','), line.end());

        int id1, id2;
        stringstream lineS(line);
        lineS >> id1 >> id2;

        // gets the two nodes from the graph
        Vertex<Node>* v1 = graph.findVertex(Node(id1));
        Vertex<Node>* v2 = graph.findVertex(Node(id2));

        // calculates the distance between the two nodes
        double distance = getEdgeWeight(v1->getInfo().getXCoord(), v1->getInfo().getYCoord(), v2->getInfo().getXCoord(), v2->getInfo().getYCoord());


        // adds the edges to the graph
        graph.addEdge(Node(id1), Node(id2), distance, true);
        graph.addEdge(Node(id2), Node(id1), distance, false);
    }

    int total = 0;

    for(auto v : graph.getVertexSet()) {
        total += v->getAdj().size();
    }

    if(total != (numEdges * 2)) {
        cout << "Number of edges in the graph is wrong! ";
        cout << total << " instead of " << numEdges * 2 << "." << endl;
        return false;
    }

    //---------------------READ TAGS-------------------------


    int numDifTags;
    tagFile >> numDifTags;


    for(int i = 0; i < numDifTags; i++) {

        // extracts tag name
        tagFile >> line;

        int numTags;
        tagFile >> numTags;

        int id;

        for(int j = 0; j < numTags; j++) {

            tagFile >> id;

            Vertex<Node>* v = graph.findVertex(Node(id));

            if(line == "amenity=waste_basket")
                v->getInfo().setType(PARAGEM);

            else if(line == "amenity=recycling")
                v->getInfo().setType(PARAGEM);

            else if(line == "amenity=waste_disposal")
                v->getInfo().setType(PARAGEM);

            else if(line == "bin=*")
                v->getInfo().setType(INTERSECAO);

            else if(line == "landuse=landfill")
                v->getInfo().setType(INTERSECAO);

            else if(line == "recycling_type=container")
                v->getInfo().setType(POINT);

            else if(line == "recycling_type=centre")
                v->getInfo().setType(POINT);

            else if(line == "amenity=waste_transfer_station")
                v->getInfo().setType(PRECOLHA);

            else if(line == "waste=*")
                v->getInfo().setType(PRECOLHA);

        }

    }

    return true;
}

double getEdgeWeight(double x1, double y1, double x2, double y2) {

    return sqrt(pow(x2 - x1,2)  + pow(y2 - y1,2) );
}