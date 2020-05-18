//
// Created by Nunation on 13/05/2020.
//

#ifndef CAL_PROJ_VEHICLE_H
#define CAL_PROJ_VEHICLE_H

#include "Node.h"
#include "Graph.h"

class Vehicle{
public:
    Vehicle(){}

    Vehicle(int id, const vector<Edge<Node>*> & pRordenados);

    Vehicle(int id);

    int getId() const;

    void setId(int id);

    const vector<Edge<Node>*> & getPRordenados() const;

    void setPRordenados(const vector<Edge<Node>*> & pRordenados);

private:
    int id;
    vector<Edge<Node>*> PRordenados;

};
#endif //CAL_PROJ_VEHICLE_H
