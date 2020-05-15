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

	int option;
    cout << "HELLO, WHAT DO YOU WANT TO DO?" << endl << endl;
    while ((option=mainMenu())!=5){
        switch(option){
            case 0:
                cout<<"Reading graph file...\n";
                if(!loadGraph(graph)){
                    cout<<"failed to read graph\n";
                }
                else{
                    cout<<"Done!\n";
                }
                break;
            case 1:

                break;
            case 2:
                cout<<"Displaying full graph!\n";
                displayGraph(graph);
                break;
            case 3:
                cout<<"Reading data from files...\n";
                conexo = readFromCityFile(graph);
                cout<<"Done!\n";
                cout<<"Displaying accessible nodes!\n";
                displayGraphConexo(conexo);
                break;
            case 4:

                break;

        }
    }
	return 0;
}
