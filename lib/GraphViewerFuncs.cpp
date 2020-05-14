//
// Created by Nunation on 13/05/2020.
//

#include "GraphViewerFuncs.h"

GraphViewer* displayGraph( Graph<Node>& graph){
    double xMin, yMin, xMax, yMax;
    int h = 750; //set height for GV
    int w;
    int auxX, auxY;
    int auxID=1;

    if(getMinMax(xMin,yMin,xMax,yMax,graph)<0){
        cout<<"Failed reading min & max coords for graphviewer";
    }

    //----------------SET WIDTH------------

    w = (int) ((xMax-xMin)*h/(yMax-yMin));

    //--------------------CREATE GRAPHVIEWER OBJECT--------------

    GraphViewer* gv = new GraphViewer(w,h,false);
    gv->createWindow(w,h);
    gv->defineEdgeColor("BLACK");
    gv->defineVertexColor("LIGHT_GRAY");

    //--------------------ADDING VERTEX--------------------

    for(auto i : graph.getVertexSet()) {

        auxX = ( i->getInfo().getXCoord() - xMin ) * w / (xMax-xMin) ;
        auxY = ( i->getInfo().getYCoord() - yMin ) * h / (yMax-yMin) ;
        auxY = h - auxY;

        gv->addNode(i->getInfo().getId(), auxX, auxY);
        if(i->getInfo().getType()==Type::GARAGEM){
            gv->setVertexColor(i->getInfo().getId(),"BLUE");
        }
    }


    //--------------------ADDING EDGES------------------------

    for(auto i : graph.getVertexSet()){
        for(auto j: i->getAdj()){
            if(j.displayEdge()) {
                gv->addEdge(auxID, i->getInfo().getId(), j.getDest()->getInfo().getId(), EdgeType::UNDIRECTED);
                auxID++;
            }
        }
    }


    gv->rearrange();

    return gv;

}

int getMinMax(double &xMin,double &yMin, double &xMax, double &yMax , Graph<Node>& graph){

    xMin=yMin=DBL_MAX;
    xMax=yMax=0;
    double auxX, auxY;

    for(auto i : graph.getVertexSet()) {
        Node node = i->getInfo();
        auxX = node.getXCoord();
        auxY = node.getYCoord();
        if(auxX < xMin){xMin = auxX;}
        if(auxY < yMin){yMin = auxY;}
        if(auxX > xMax){xMax = auxX;}
        if(auxY > yMax){yMax = auxY;}
    }
    if(xMin>xMax || yMin>yMax){ return -1;}
    return 0;
}

int getMinMaxVector(double &xMin,double &yMin, double &xMax, double &yMax , vector<Vertex<Node>*>& graph){

    xMin=yMin=DBL_MAX;
    xMax=yMax=0;
    double auxX, auxY;

    for(auto i : graph) {
        Node node = i->getInfo();
        auxX = node.getXCoord();
        auxY = node.getYCoord();
        if(auxX < xMin){xMin = auxX;}
        if(auxY < yMin){yMin = auxY;}
        if(auxX > xMax){xMax = auxX;}
        if(auxY > yMax){yMax = auxY;}
    }
    if(xMin>xMax || yMin>yMax){ return -1;}
    return 0;
}

void displayGraphConexo( vector<Vertex<Node>*>& graph){
    double xMin, yMin, xMax, yMax;
    int h = 750; //set height for GV
    int w;
    int auxX, auxY;
    int auxID=1;

    if(getMinMaxVector(xMin,yMin,xMax,yMax,graph)<0){
        cout<<"Failed reading min & max coords for graphviewer";
    }

    //----------------SET WIDTH------------

    w = (int) ((xMax-xMin)*h/(yMax-yMin));

    //--------------------CREATE GRAPHVIEWER OBJECT--------------

    GraphViewer* gv = new GraphViewer(w,h,false);
    gv->createWindow(w,h);
    gv->defineEdgeColor("BLACK");
    gv->defineVertexColor("LIGHT_GRAY");

    for(auto i : graph) {

        auxX = ( i->getInfo().getXCoord() - xMin ) * w / (xMax-xMin) ;
        auxY = ( i->getInfo().getYCoord() - yMin ) * h / (yMax-yMin) ;
        auxY = h - auxY;

        i->getInfo().setGraphViewerX((int) auxX);
        i->getInfo().setGraphViewerY((int) auxY);
        gv->addNode(i->getInfo().getId(), auxX, auxY);
        if(i->getInfo().getType()==Type::GARAGEM){
            gv->setVertexColor(i->getInfo().getId(),"BLUE");
        }
    }

    for(auto i : graph){
        for(auto j: i->getAdj()){
            if(j.displayEdge()) {
                gv->addEdge(auxID, i->getInfo().getId(), j.getDest()->getInfo().getId(), EdgeType::UNDIRECTED);
                auxID++;
            }
        }
    }


    gv->rearrange();

    return;


}
