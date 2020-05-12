//
// Created by olive on 12/05/2020.
//

#include <fstream>
#include <sstream>
#include <math.h>
#include <iostream>
#include "GraphFuncs.h"

using namespace std;

Graph<Node> loadGraph(){
    Graph<Node> graph;

    ifstream coordFile, edgeFile, tagFile   ;

    //------
    //OPEN FILES FOR READING
    //-------
    coordFile.open("mapas/Porto/nodes_x_y_porto.txt");

    if(!coordFile) {
        cout << "Couldn't open coordinates file!" << endl;
        return graph;
    }

    edgeFile.open("mapas/Porto/edges_porto.txt");

    if(!edgeFile) {
        cout << "Couldn't open edge file!" << endl;
        return graph;
    }

    tagFile.open("mapas/Porto/t02_tags_porto.txt");

    if(!tagFile) {
        cout << "Couldn't open tags file!" << endl;
        return graph;
    }


    // -----------
    // READS NODES
    // -----------

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
        return graph;
    }



    // -----------
    // READS EDGES
    // -----------

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
        stringstream linestream(line);
        linestream >> id1 >> id2;

        // gets the two nodes from the graph
        Vertex<Node>* v1 = graph.findVertex(Node(id1));
        Vertex<Node>* v2 = graph.findVertex(Node(id2));

        // calculates the distance between the two nodes
        double distance = getEdgeWeight(v1->getInfo().getXCoord(), v1->getInfo().getYCoord(), v2->getInfo().getXCoord(), v2->getInfo().getYCoord());


        // adds the edges to the graph
        graph.addEdge(Node(id1), Node(id2), distance);
        graph.addEdge(Node(id2), Node(id1), distance);
    }

    int total = 0;

    for(auto v : graph.getVertexSet()) {
        total += v->getAdj().size();
    }

    if(total != (numEdges * 2)) {
        cout << "Number of edges in the graph is wrong! ";
        cout << total << " instead of " << numEdges * 2 << "." << endl;
        return graph;
    }

    // -----------
    // READS TAGS
    // -----------


    int numDifTags;
    tagsStream >> numDifTags;


    for(int i = 0; i < numDifTags; i++) {

        // extracts tag name
        tagsStream >> line;

        int numTags;
        tagsStream >> numTags;

        int id;

        for(int j = 0; j < numTags; j++) {

            tagsStream >> id;

            Vertex<Node>* v = graph.findVertex(Node(id));

            if(line == "amenity=bank")
                v->getInfo().setType(BANK);

            else if(line == "barrier=hedge_bank")
                v->getInfo().setType(BANK);

            else if(line == "amenity=financial_advice")
                v->getInfo().setType(FIN_ADVICE);

            else if(line == "amenity=atm")
                v->getInfo().setType(ATM);

            else if(line == "office=tax_advisor")
                v->getInfo().setType(TAX_ADVISOR);

            else if(line == "government=audit")
                v->getInfo().setType(AUDIT);

            else if(line == "shop=money_lender")
                v->getInfo().setType(MONEY_MOV);

            else if(line == "amenity=money_transfer")
                v->getInfo().setType(MONEY_MOV);

            else if(line == "shop=moneylender")
                v->getInfo().setType(MONEY_MOV);

        }

    }

    return graph;
}

double getEdgeWeight(double x1, double y1, double x2, double y2) {

    return sqrt(pow(x2 - x1,2)  + pow(y2 - y1,2) );
}