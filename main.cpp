#include <iostream>
#include "lib/Node.h"
#include "lib/Graph.h"
#include "lib/GraphFuncs.h"
#include "graphviewer.h"
#include "GraphViewerFuncs.h"
#include "Menus.h"


int main() {
	Graph<Node> graph;
    vector<Vertex<Node>*> conexo;
    unordered_map<VertexPair, double> table;
    int aux;
    string city;
    bool canDisplay=false;

	int option;
    cout << "HELLO, WHAT DO YOU WANT TO DO?" << endl << endl;
    while ((option=mainMenu())!=5){
        switch(option){
            case 0:
                aux=chooseCity(city);
                if(aux<0){
                    break;
                }
                cout<<"Reading graph file...\n";
                graph = loadGraph(city);
                cout<<"Done!\n\n";
                cout<<"Generating CFC...\n";
                conexo = readFromCityFile(graph,city);
                if(conexo.empty()){
                    cout<<"failed to create CFC\n";
                    break;
                }
                canDisplay=true;
                cout<<"Done!\n\n";
                break;
            case 1:
                if(!canDisplay){
                    cout<<"You must first load a graph\n";
                    break;
                }
                cout<<"Displaying full graph!\n";
                displayGraph(graph);
                break;
            case 2:
                if(!canDisplay){
                    cout<<"You must first load a graph\n";
                    break;
                }
                cout<<"Displaying accessible nodes!\n";
                displayGraphConexo(conexo);
                break;
            case 3:
                help(conexo);
                break;
            case 4:
                if(!canDisplay){
                    cout<<"You must first load a graph\n";
                    break;
                }
                cout<<"Reading service...\n";
                Service servico = readService(conexo,city);
                cout<<"Done!\n";
                cout<<"Calculating service...\n";
                proccessService(servico,graph);
                cout<<"Done!\n";
                cout<<"Displaying service...\n";
                //displayService(servico);
                break;
        }
    }
	return 0;
}
