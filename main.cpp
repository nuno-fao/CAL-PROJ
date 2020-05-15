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
    int aux;
    string city;

	int option;
    cout << "HELLO, WHAT DO YOU WANT TO DO?" << endl << endl;
    while ((option=mainMenu())!=4){
        switch(option){
            case 0:
                aux=chooseCity(city);
                if(aux<0){
                    break;
                }
                else{

                }
                cout<<"Reading graph file...\n";
                graph = loadGraph(city);
                cout<<"Done!\n\n";
                cout<<"Processing important data...\n";
                conexo = readFromCityFile(graph,city);
                if(conexo.empty()){
                    cout<<"failed to create CFC\n";
                    break;
                }
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

                break;
        }
    }
	return 0;
}
