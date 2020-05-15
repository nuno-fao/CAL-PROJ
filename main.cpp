#include <iostream>
#include "lib/Node.h"
#include "lib/Graph.h"
#include "lib/GraphFuncs.h"
#include "graphviewer.h"
#include "GraphViewerFuncs.h"


int main() {
	Graph<Node> graph;
	if(!loadGraph(graph)){
	    cout<<"failed to read graph\n";
	}
    readFromCityFile(graph);
	//GraphViewer* gv = displayGraph(graph);
	vector<Vertex<Node>*> conexo = readFromCityFile(graph);
	displayGraphConexo(conexo);
	getchar();
	return 0;
}
