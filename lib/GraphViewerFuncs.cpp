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
    gv->defineEdgeCurved(true);

    //--------------------ADDING VERTEX--------------------

    for(auto i : graph.getVertexSet()) {

        auxX = ( i->getInfo().getXCoord() - xMin ) * w / (xMax-xMin) ;
        auxY = ( i->getInfo().getYCoord() - yMin ) * h / (yMax-yMin) ;
        auxY = h - auxY;

        gv->addNode(i->getInfo().getId(), (int)auxX, (int)auxY);
    }


    //--------------------ADDING EDGES------------------------

    for(auto i : graph.getVertexSet()){
        for(auto j: i->getAdj()){
            if(j.displayEdge()) {
                gv->addEdge(auxID, i->getInfo().getId(), j.getDest()->getInfo().getId(), EdgeType::DIRECTED);
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
    gv->defineEdgeCurved(true);
    gv->defineVertexSize(10);

    for(auto i : graph) {

        auxX = ( i->getInfo().getXCoord() - xMin ) * w / (xMax-xMin) ;
        auxY = ( i->getInfo().getYCoord() - yMin ) * h / (yMax-yMin) ;
        auxY = h - auxY;

        gv->addNode(i->getInfo().getId(), (int)auxX, (int)auxY);
        if(i->getInfo().getType()==Type::GARAGEM){
            gv->setVertexColor(i->getInfo().getId(),"BLUE");
            gv->setVertexLabel(i->getInfo().getId(),"GARAGEM");
            gv->setVertexSize(i->getInfo().getId(),30);
        }
    }

    for(auto i : graph){
        for(auto j: i->getAdj()){
            if(j.displayEdge()) {
                gv->addEdge(auxID, i->getInfo().getId(), j.getDest()->getInfo().getId(), EdgeType::UNDIRECTED);
                gv->setEdgeThickness(auxID,2);
                auxID++;
            }
        }
    }


    gv->rearrange();
}

void displayService(Service service){
    int h, w;
    h=w=750;
    double xMin,yMin,xMax,yMax;
    xMin=yMin=DBL_MAX;
    xMax=yMax=0;
    double auxX, auxY;
    int auxID =1;
    for(auto i:service.getVehicle().getPRordenados()){
        Node node = i.getDest()->getInfo();
        auxX = node.getXCoord();
        auxY = node.getYCoord();
        if(auxX < xMin){xMin = auxX;}
        if(auxY < yMin){yMin = auxY;}
        if(auxX > xMax){xMax = auxX;}
        if(auxY > yMax){yMax = auxY;}
    }
    if(service.getGaragem()->getInfo().getXCoord()<xMin){xMin=service.getGaragem()->getInfo().getXCoord();}
    if(service.getGaragem()->getInfo().getYCoord()<yMin){yMin=service.getGaragem()->getInfo().getYCoord();}
    if(service.getGaragem()->getInfo().getXCoord()>xMax){xMax=service.getGaragem()->getInfo().getXCoord();}
    if(service.getGaragem()->getInfo().getYCoord()>yMax){yMax=service.getGaragem()->getInfo().getYCoord();}
    if(service.getDestino()->getInfo().getXCoord()<xMin){xMin=service.getDestino()->getInfo().getXCoord();}
    if(service.getDestino()->getInfo().getYCoord()<yMin){yMin=service.getDestino()->getInfo().getYCoord();}
    if(service.getDestino()->getInfo().getXCoord()>xMax){xMax=service.getDestino()->getInfo().getXCoord();}
    if(service.getDestino()->getInfo().getYCoord()>yMax){yMax=service.getDestino()->getInfo().getYCoord();}

    //----------------SET WIDTH------------

    w = (int) ((xMax-xMin)*h/(yMax-yMin));



    //------------------CREATE GRAPH------------

    GraphViewer* gv = new GraphViewer(w,h,false);
    gv->createWindow(w,h);
    gv->defineEdgeColor("GREEN");
    gv->defineVertexColor("LIGHT_GREY");
    gv->defineEdgeCurved(true);
    gv->defineVertexSize(10);

    //------------------ADD GARAGE & FACTORY----------------

    auxX = ( service.getGaragem()->getInfo().getXCoord() - xMin ) * w / (xMax-xMin) ;
    auxY = ( service.getGaragem()->getInfo().getYCoord() - yMin ) * h / (yMax-yMin) ;
    auxY = h - auxY;

    gv->addNode(service.getGaragem()->getInfo().getId(), auxX, auxY);
    gv->setVertexColor(service.getGaragem()->getInfo().getId(),"GREEN");
    gv->setVertexSize(service.getGaragem()->getInfo().getId(),30);
    gv->setVertexLabel(service.getGaragem()->getInfo().getId(),"GARAGEM");

    auxX = ( service.getDestino()->getInfo().getXCoord() - xMin ) * w / (xMax-xMin) ;
    auxY = ( service.getDestino()->getInfo().getYCoord() - yMin ) * h / (yMax-yMin) ;
    auxY = h - auxY;

    gv->addNode(service.getDestino()->getInfo().getId(), auxX, auxY);
    gv->setVertexColor(service.getDestino()->getInfo().getId(),"RED");
    gv->setVertexSize(service.getDestino()->getInfo().getId(),30);
    gv->setVertexLabel(service.getDestino()->getInfo().getId(),"FACTORY");


    //----------------ADD REST OF THE PATH----------------------------
    Vertex<Node>* origem;
    origem=service.getGaragem();

    for(auto i: service.getVehicle().getPRordenados()){
        auxX = ( i.getDest()->getInfo().getXCoord() - xMin ) * w / (xMax-xMin) ;
        auxY = ( i.getDest()->getInfo().getYCoord() - yMin ) * h / (yMax-yMin) ;
        auxY = h - auxY;
        gv->addNode(i.getDest()->getInfo().getId(),(int)auxX,(int)auxY);
        gv->addEdge(auxID,origem->getInfo().getId(),i.getDest()->getInfo().getId(),EdgeType::DIRECTED);
        gv->setEdgeThickness(auxID,2);
        gv->setEdgeLabel(auxID,to_string(auxID));
        origem=i.getDest();
        auxID++;
    }

    //------------------MAKE PR CLEARER----------------------------
    int auxPRID=1;
    string auxString;
    for(auto i: service.getPontosRecolha()){
        auxString="PR"+to_string(auxPRID);
        gv->setVertexSize(i->getInfo().getId(),30);
        gv->setVertexLabel(i->getInfo().getId(),auxString);
        gv->setVertexColor(i->getInfo().getId(),"BLUE");
        auxPRID++;
    }

    gv->rearrange();

}
