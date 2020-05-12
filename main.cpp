#include <iostream>
#include "lib/Node.h"
#include "lib/Graph.h"
#include "lib/GraphFuncs.h"


int main() {
	Graph<Node> graph;
	if(!loadGraph(graph)){
	    cout<<"failed to read graph\n";
	}
    cout<<"funcionou caralho\n";
	return 0;
}
