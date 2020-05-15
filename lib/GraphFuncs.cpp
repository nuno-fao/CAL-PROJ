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

    ifstream coordFile, edgeFile;
    int aux;

    //open files for reading

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

    //-------------------------------READ VERTEX----------------------


    coordFile >> aux;

    string line;

    getline(coordFile, line);   //clear /n


    while(getline(coordFile, line)) {

        // removes parentheses
        size_t pos = line.find(')');
        if (pos != string::npos)
            line = line.substr(1, pos);


        line.erase(remove(line.begin(), line.end(), ','), line.end());  //removes ','


        int id;
        double x, y;
        stringstream linestream(line);
        linestream >> id >> x >> y;

        graph.addVertex(Node(id, x, y));
    }


    if(graph.getVertexSet().size() != aux) {    //vertex num check
        cout << "Read wrong number of vertex! ";
        return false;
    }



    //------------------------READ EDGES-----------------------------
    int total=0;
    double distance;

    edgeFile >> aux;

    getline(edgeFile, line);    //clear /n


    while(getline(edgeFile, line)) {

        // removes parentheses
        size_t pos = line.find(')');
        if (pos != string::npos)
            line = line.substr(1, pos);


        line.erase(remove(line.begin(), line.end(), ','), line.end());  //removes ','

        int id1, id2;
        stringstream lineS(line);
        lineS >> id1 >> id2;

        Vertex<Node>* v1 = graph.findVertex(Node(id1)); //search source vertex
        Vertex<Node>* v2 = graph.findVertex(Node(id2)); //search dest vertex

        distance = getEdgeWeight(v1->getInfo().getXCoord(), v1->getInfo().getYCoord(), v2->getInfo().getXCoord(), v2->getInfo().getYCoord());



        if(!graph.addEdge(Node(id1), Node(id2), distance, true)){
            cout<<"Failed to add an edge from node "<<id1<<" to "<<id2<<" !!!";
            return false;
        }
        total++;
        if(!graph.addEdge(Node(id2), Node(id1), distance, false)){
            cout<<"Failed to add an edge from node "<<id2<<" to "<<id1<<" !!!";
            return false;
        }
        total++;
    }

    if(total != (aux * 2)) {    //edge num check
        cout << "Read wrong number of edges! ";
        return false;
    }

    return true;
}

double getEdgeWeight(double x1, double y1, double x2, double y2) {

    return sqrt(pow(x2 - x1,2)  + pow(y2 - y1,2) );
}

vector<Vertex<Node>*> readFromCityFile(Graph<Node> &graph){
    ifstream cityFile;
    string aux;
    vector<Vertex<Node>*> outIfFail;
    cityFile.open("../files/porto_info.txt");
    if(!cityFile){
        cout<<"Couldn't open city file! ";
        return outIfFail;
    }
    getline(cityFile,aux);
    Vertex<Node>* garage=graph.findVertex(Node(stoi(aux)));
    garage->getInfo().setType(Type::GARAGEM);
    return cleanEdgesNVertex(graph,garage);
}

vector<Vertex<Node>*> cleanEdgesNVertex(Graph<Node> graph, Vertex<Node>* garage){
    vector<Vertex<Node>*> visitedVertex;
    //---------------------CLEAN USELESS EDGES---------------------
    for(auto v : graph.getVertexSet()) {
        for (int i = 0; i < v->getAdj().size(); i++) {
            if (v->getAdj().at(i).getWeight() <= 0) {
                v->removeEdge(i);
                i--;
            }
        }
    }
    //----------------------REMOVE VERTEX NOT ACCESSIBLE FROM GARAGE---------------
    for (auto v : graph.getVertexSet())
        v->setVisited(false);

    graph.DepthFirstSearch(garage, visitedVertex);
    return visitedVertex;
}