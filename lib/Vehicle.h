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
    queue<Edge<Node>> PRordenados;
public:
    int getId() const;

    void setId(int id);

    const queue<Edge<Node>> &getPRordenados() const;

    void setPRordenados(const queue<Edge<Node>> &pRordenados);

    Vehicle(int id);

    Vehicle(int id, const queue<Edge<Node>> &pRordenados);
};
#endif //CAL_PROJ_VEHICLE_H
