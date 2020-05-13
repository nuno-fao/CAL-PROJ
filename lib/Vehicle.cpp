//
// Created by Nunation on 13/05/2020.
//

#include <queue>
#include "Vehicle.h"

Vehicle::Vehicle(int id, const std::priority_queue <Vertex<Node>> &pRordenados) : id(id), PRordenados(pRordenados) {}

Vehicle::Vehicle(int id) : id(id) {}

int Vehicle::getId() const {
    return id;
}

void Vehicle::setId(int id) {
    Vehicle::id = id;
}

const priority_queue<Vertex<Node>> &Vehicle::getPRordenados() const {
    return PRordenados;
}

void Vehicle::setPRordenados(const priority_queue<Vertex<Node>> &pRordenados) {
    PRordenados = pRordenados;
}
