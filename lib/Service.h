//
// Created by Nunation on 13/05/2020.
//

#ifndef CAL_PROJ_SERVICE_H
#define CAL_PROJ_SERVICE_H

#include "Node.h"
#include "Graph.h"
#include "Vehicle.h"

class Service{
private:
    int id;
    Vertex<Node>* garagem;
    Vertex<Node>* destino;
    vector<Vertex<Node>> pontosRecolha;
    Vehicle vehicle;
public:
    const Vehicle &getVehicle() const;

    void setVehicle(const Vehicle &vehicle);

    Service(int id, Vertex<Node> *garagem, Vertex<Node> *destino, const vector<Vertex<Node>> &pontosRecolha);

    Service(int id, Vertex<Node> *garagem, Vertex<Node> *destino, const Vehicle &vehicle);

    Service(int id, Vertex<Node> *garagem, Vertex<Node> *destino, const vector<Vertex<Node>> &pontosRecolha,
            const Vehicle &vehicle);

    int getId() const;

    void setId(int id);

    Vertex<Node> *getGaragem() const;

    void setGaragem(Vertex<Node> *garagem);

    Vertex<Node> *getDestino() const;

    void setDestino(Vertex<Node> *destino);

    const vector<Vertex<Node>> &getPontosRecolha() const;

    void setPontosRecolha(const vector<Vertex<Node>> &pontosRecolha);


};
#endif //CAL_PROJ_SERVICE_H
