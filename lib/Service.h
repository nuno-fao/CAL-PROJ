//
// Created by Nunation on 13/05/2020.
//

#ifndef CAL_PROJ_SERVICE_H
#define CAL_PROJ_SERVICE_H

#include "Node.h"
#include "Graph.h"
#include "Vehicle.h"

class Service{
public:
    Service(int id, Vertex<Node> *garagem, Vertex<Node> *destino);

    Service(int id, Vertex<Node> *garagem, Vertex<Node> *destino, const vector<Vertex<Node>*> & pontosRecolha);

    int getId() const;

    void setId(int id);

    Vertex<Node> *getGaragem() const;

    void setGaragem(Vertex<Node> *garagem);

    Vertex<Node> *getDestino() const;

    void setDestino(Vertex<Node> *destino);

    const vector<Vertex<Node>*> & getPontosRecolha() const;

    void setPontosRecolha(const vector<Vertex<Node>*> & pontosRecolha);

    const Vehicle &getVehicle() const;

    void setVehicle(const Vehicle &vehicle);

private:
    int id; // ID do veículo
    Vertex<Node>* garagem; // vértice da garagem
    Vertex<Node>* destino; // vértice da empresa
    vector<Vertex<Node>*> pontosRecolha;    //vetor dos pontos de recolha
    Vehicle vehicle;    // veículo atribuido;
};
#endif //CAL_PROJ_SERVICE_H
