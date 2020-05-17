//
// Created by Nunation on 13/05/2020.
//

#include <queue>
#include "Vehicle.h"

int Vehicle::getId() const {
    return id;
}

void Vehicle::setId(int id) {
    Vehicle::id = id;
}

const vector<Edge<Node>*> & Vehicle::getPRordenados() const{
return
PRordenados;
}

void Vehicle::setPRordenados(const vector<Edge<Node>*> & pRordenados) {
    PRordenados = pRordenados;
}

Vehicle::Vehicle(int id, const vector<Edge<Node>*> & pRordenados) : id(id), PRordenados(pRordenados) {}
