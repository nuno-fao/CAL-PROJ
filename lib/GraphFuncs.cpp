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

Graph<Node> loadGraph( string city){
    Graph<Node> graph;
    ifstream coordFile, edgeFile;
    int aux;
    string auxString;

    //open files for reading
    auxString="../mapas/"+city+"/nodes_x_y_"+city+".txt";
    coordFile.open(auxString);

    if(!coordFile) {
        cout << "Couldn't open coordinates file!" << endl;
        return graph;
    }

    auxString="../mapas/"+city+"/edges_"+city+".txt";
    edgeFile.open(auxString);

    if(!edgeFile) {
        cout << "Couldn't open edge file!" << endl;
        return graph;
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
        return graph;
    }
    vector<Vertex<Node>*> copy = graph.getVertexSet();
    sort(copy.begin(),copy.end(),sortById);
    graph.setVertexSet(copy);



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

        Vertex<Node>* v1 = vertexBinarySearch(graph.getVertexSet(),Node(id1),0,graph.getVertexSet().size()); //search source vertex
        Vertex<Node>* v2 = vertexBinarySearch(graph.getVertexSet(),Node(id2),0,graph.getVertexSet().size()); //search dest vertex

        if(v1== nullptr|| v2== nullptr){
            cout<<"Failed to find vertex "<<id1<<" or vertex "<<id2<<" !!!";
            return graph;
        }

        distance = getEdgeWeight(v1->getInfo().getXCoord(), v1->getInfo().getYCoord(), v2->getInfo().getXCoord(), v2->getInfo().getYCoord());



        if(!graph.addEdge(Node(id1), Node(id2), distance, true)){
            cout<<"Failed to add an edge from node "<<id1<<" to "<<id2<<" !!!";
            return graph;
        }
        total++;
        if(!graph.addEdge(Node(id2), Node(id1), distance, false)){
            cout<<"Failed to add an edge from node "<<id2<<" to "<<id1<<" !!!";
            return graph;
        }
        total++;
    }

    if(total != (aux * 2)) {    //edge num check
        cout << "Read wrong number of edges! ";
        return graph;
    }

    return graph;
}

double getEdgeWeight(double x1, double y1, double x2, double y2) {

    return sqrt(pow(x2 - x1,2)  + pow(y2 - y1,2) );
}

vector<Vertex<Node>*> readFromCityFile(Graph<Node> &graph,string city){
    ifstream cityFile;
    string aux;
    vector<Vertex<Node>*> outIfFail;
    aux="../files/"+city+"/"+city+"_info.txt";
    cityFile.open(aux);
    if(!cityFile){
        cout<<"Couldn't open city file! ";
        return outIfFail;
    }
    getline(cityFile,aux);
    Vertex<Node>* garage=vertexBinarySearch(graph.getVertexSet(),Node(stoi(aux)),0,graph.getVertexSet().size());
    Node newInfo = garage->getInfo();
    newInfo.setType(Type::GARAGEM);
    garage->setInfo(newInfo);

    getline(cityFile,aux);  // clear separator

    while(getline(cityFile,aux)){
        size_t pos = aux.find(')');
        if (pos != string::npos)
            aux = aux.substr(1, pos);


        aux.erase(remove(aux.begin(), aux.end(), ','), aux.end());  //removes ','

        int id1, id2;
        stringstream lineS(aux);
        lineS >> id1 >> id2;

        Vertex<Node>* v1 = vertexBinarySearch(graph.getVertexSet(),Node(id1),0,graph.getVertexSet().size()); //search source vertex
        Vertex<Node>* v2 = vertexBinarySearch(graph.getVertexSet(),Node(id2),0,graph.getVertexSet().size()); //search dest vertex

        if(v1== nullptr|| v2== nullptr){
            cout<<"Failed to find vertex "<<id1<<" or vertex "<<id2<<" while making CFC!!!";
            return outIfFail;
        }
        //remove edge from 1 vertex
        for(int i=0;i<v1->getAdj().size();i++){
            if(v1->getAdj().at(i).getDest()==v2){
                v1->removeEdge(i);
                break;
            }
        }

        //remove edge from the other vertex
        for(int i=0;i<v2->getAdj().size();i++){
            if(v2->getAdj().at(i).getDest()==v1){
                v2->removeEdge(i);
                break;
            }
        }

    }
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
        v->setVisited(false);
    }
    //--------------------GET CFC----------------------------
    graph.DepthFirstSearch(garage, visitedVertex);

    sort(visitedVertex.begin(),visitedVertex.end(),sortById);

    return visitedVertex;
}


Service readService(vector<Vertex<Node>*> graph, string city) {

    string aux;
    ifstream serviceFile;
    vector<int> notFound;
    vector<Vertex<Node>*> pRecolha;

    int id, total = 0;
    bool found = false;

    do {
        cout << "Insert the target service file name (no need for the directory and sufix but MUST be .txt): " << endl;
        cin >> aux;
        aux = "../files/" + city + "/" + aux + ".txt";
        serviceFile.open(aux);
        if (!serviceFile)
            cout << "Couldn't open file! Please insert another one." << endl;

    } while (!serviceFile);

    //------------------FACTORY VERTEX ID-----------------------

    int idFactory;
    serviceFile >> idFactory;
    getline(serviceFile, aux);

    //------------------TOTAL NUMBER OF NODES-----------------------

    int nrPR;
    serviceFile >> nrPR;
    getline(serviceFile, aux);


    while (getline(serviceFile, aux)) {

        id = stoi(aux);

        for (auto i: graph) {
            if (i->getInfo().getId() == id && i->getInfo().getType()!=Type::GARAGEM) {
                Node newInfo = i->getInfo();
                newInfo.setType(Type::PRECOLHA);
                i->setInfo(newInfo);
                pRecolha.push_back(i);
                found = true;
                break;
            }
        }

        if (!found) {
            notFound.push_back(id);
        } else {
            found = false;
        }
        total++;
    }

    //------------------SET FACTORY & GARAGE------------------
    Vertex<Node>* factory = vertexBinarySearch(graph,Node(idFactory),0,graph.size());
    Vertex<Node>* garage;
    Node auxNode = factory->getInfo();
    auxNode.setType(Type::FACTORY);
    factory->setInfo(auxNode);
    for (auto i: graph) {
        if(i->getInfo().getType()==Type::GARAGEM){
            garage = i;
            break;
        }
    }


    //------------------CHECK NODES READ-----------------------

    if (total != nrPR)
        cout << "Not counting unaccessible nodes, it wasn't possible to read all nodes, please check file integrity!\n";

    //------------------OUTPUT THE ID'S THAT COULD NOT BE READ----------------------

    if (!notFound.empty()) {
        cout << "There were " << notFound.size()
             << " id's not accessible from the garage or that simply don't exist in this map.\nThose were:\n";
        for (auto i : notFound) {
            cout << "(" << i << ");\t";
        }
    }

    Service service(1,garage,factory,pRecolha);
    return service;
}


double pathCost(Graph<Node> graph, Vertex<Node> * origem, Vertex<Node> * destino){
    double cost = 0;
    vector<Node> path = graph.getPath(origem->getInfo(), destino->getInfo());
    for (int i = 0; i < graph.getPath(origem->getInfo(), destino->getInfo()).size() - 1; i++) {
        Vertex<Node> *v1 = graph.findVertex(path[i]);
        Vertex<Node> *v2 = graph.findVertex(path[i + 1]);
        for (auto j: v1->getAdj()) {
            if (j.getDest() == v2) {
                cost += j.getWeight();
            }
        }
    }

    return cost;
}

vector<Vertex<Node> *>sortPoints(Service service, Graph<Node> graph){
    vector<Vertex<Node> *> pontosrecolha = service.getPontosRecolha();
    vector<Vertex<Node> *> sortedpoints;
    sortedpoints.push_back(service.getGaragem());
    Vertex<Node> * last = service.getGaragem();
    Vertex<Node> * next;
    vector<Vertex<Node> *> visited;
    double pathcost;


    while (sortedpoints.size() < pontosrecolha.size()+1) {
        double cost = INF;
        for (auto i: pontosrecolha) {
            if (find(visited.begin(), visited.end(), i) != visited.end()) continue;
            else {
                pathcost = pathCost(graph, last, i);
                if (pathcost < cost) {
                    cost = pathcost;
                    next = i;
                }
            }

        }
        sortedpoints.push_back(next);
        last = next;
        visited.push_back(next);
    }
    sortedpoints.push_back(service.getDestino());
    return sortedpoints;

}

vector<Edge<Node>> orderEdges(Service service, Graph<Node> graph) {
    vector<Edge<Node>> res;
    vector<Vertex<Node> *> pontosrecolha = service.getPontosRecolha();
    vector<Node> path;
    vector<Vertex<Node> *> vpontos;

    unsigned int n;
    do {

        cout << "What algorithm should be used?" << endl;
        cout << "0 -> Dijkstra's Shortest Path" << endl;
        cout << "1 -> Bellman-Ford's algorithm" << endl;
        cout << "Tip: if there are edges with negative weight, Bellman-Ford's algorithm is recommended." << endl;
        /*cout
                << "Tip: If the number of edges is about the same as the number of vertex, Dijkstra is recommended but there are way more edges than vertex, Floyd-Warshall is"
                << endl;*/
        cout << "Option: ";
        cin >> n;

        if (n > 1)
            cout << endl << endl << "Invalid option! Try again." << endl << endl;

    } while (n > 1);

    cout << "\n Working, this may take a while depending on CFC size.\n";

    if (n == 0) {
        graph.dijkstraShortestPath(service.getGaragem()->getInfo());
        vpontos = sortPoints(service, graph);
        for (int i = 0; i < vpontos.size() - 1; i++) {
            for (auto i: graph.getPath(vpontos[i]->getInfo(), vpontos[i + 1]->getInfo())) {
                path.push_back(i);
            }
        }
    }
    else {

        /*for (int i = 0; i < vpontos.size() - 1; i++) {
            graph.unweightedShortestPath(vpontos[i]->getInfo());
            for (auto i: graph.getPathTo(vpontos[i]->getInfo(), vpontos[i + 1]->getInfo())) path.push_back(i);
        }
*/
        /*graph.floydWarshallShortestPath();
        vpontos = sortPoints(service, graph, n);

        for (int i = 0; i < vpontos.size(); i++)
        {
            for (auto j: graph.getfloydWarshallPath(vpontos[i]->getInfo(), vpontos[i + 1]->getInfo())) path.push_back(j);
        }*/

        graph.bellmanFordShortestPath(service.getGaragem()->getInfo());
        vpontos = sortPoints(service, graph);
        for (int i = 0; i < vpontos.size() - 1; i++) {
            for (auto i: graph.getPath(vpontos[i]->getInfo(), vpontos[i + 1]->getInfo())) path.push_back(i);
        }
    }
    vector<Vertex<Node> *> temp;
    for (auto i: path){
        for (auto j: graph.getVertexSet()){
            if (i == j->getInfo()) temp.push_back(j);
        }
    }

    for (int i = 1; i < temp.size(); i++) {
        Vertex<Node> *prev = temp[i - 1];
        for (auto j: prev->getAdj()) {
            if (j.getDest() == temp[i]) {
                res.push_back(j);
                break;
            }
        }
    }
    return res;
}

void proccessService(Service &service, Graph<Node> graph){
    Vehicle vehicle(1);
    vehicle.setPRordenados(orderEdges(service, graph));
    service.setVehicle(vehicle);
}

bool sortById(const Vertex<Node>* a,const Vertex<Node>* d){
    return a->getInfo().getId()<d->getInfo().getId();
}

Vertex<Node>* vertexBinarySearch(vector<Vertex<Node>*> vertexSet, const Node &target, int indInicio, int indFim){
    while(indInicio<=indFim){
        int mid = indInicio+(indFim-indInicio)/2;

        if(vertexSet.at(mid)->getInfo().getId()==target.getId()){
            return vertexSet.at(mid);
        }
        if(vertexSet.at(mid)->getInfo().getId()<target.getId()){
            indInicio=mid+1;
        }
        else{
            indFim=mid-1;
        }
    }
    return nullptr;
}

