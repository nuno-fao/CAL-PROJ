//
// Created by Nunation on 13/05/2020.
//

#ifndef CAL_PROJ_VEHICLE_H
#define CAL_PROJ_VEHICLE_H

#include "Node.h"
#include "Graph.h"

class Vehicle{
private:
    int id;
    priority_queue<Vertex<Node>> PRordenados;
public:
    int getId() const;

    void setId(int id);

    const priority_queue<Vertex<Node>> &getPRordenados() const;

    void setPRordenados(const priority_queue<Vertex<Node>> &pRordenados);

    Vehicle(int id);

    Vehicle(int id, const priority_queue<Vertex<Node>> &pRordenados);
};
#endif //CAL_PROJ_VEHICLE_H
