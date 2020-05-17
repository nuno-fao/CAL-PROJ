#include <iostream>
#include "lib/Node.h"
#include "lib/Graph.h"
#include "lib/GraphFuncs.h"
#include "graphviewer.h"
#include "GraphViewerFuncs.h"
#include "Menus.h"


int main() {
	Graph<Node> graph;
    GraphViewer* gv;
    vector<Vertex<Node>*> conexo;
    unordered_map<VertexPair, double> table;
    int aux;
    string city;

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
                cout<<"Done!\n\n";
                cout<<"Generating table...\n";
                table = makeTable(conexo,graph);
                cout<<"Done!\n";
                break;
            case 1:
                cout<<"Displaying full graph!\n";
                displayGraph(graph);
                break;
            case 2:
                cout<<"Displaying accessible nodes!\n";
                displayGraphConexo(conexo);
                break;
            case 3:
                help(conexo);
                break;
            case 4:
                cout<<"Reading service...\n";
                Service servico = readService(conexo,city);
                cout<<"Done!\n";

                break;
        }
    }
	return 0;
}
