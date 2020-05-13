//
// Created by Nunation on 13/05/2020.
//

#include "Service.h"

int Service::getId() const {
    return id;
}

void Service::setId(int id) {
    Service::id = id;
}

Vertex<Node> *Service::getGaragem() const {
    return garagem;
}

void Service::setGaragem(Vertex<Node> *garagem) {
    Service::garagem = garagem;
}

Vertex<Node> *Service::getDestino() const {
    return destino;
}

void Service::setDestino(Vertex<Node> *destino) {
    Service::destino = destino;
}

const vector<Vertex<Node>> &Service::getPontosRecolha() const {
    return pontosRecolha;
}

void Service::setPontosRecolha(const vector<Vertex<Node>> &pontosRecolha) {
    Service::pontosRecolha = pontosRecolha;
}

const Vehicle &Service::getVehicle() const {
    return vehicle;
}

void Service::setVehicle(const Vehicle &vehicle) {
    Service::vehicle = vehicle;
}

Service::Service(int id, Vertex<Node> *garagem, Vertex<Node> *destino, const Vehicle &vehicle) : id(id),
                                                                                                 garagem(garagem),
                                                                                                 destino(destino),
                                                                                                 vehicle(vehicle) {}

Service::Service(int id, Vertex<Node> *garagem, Vertex<Node> *destino, const vector<Vertex<Node>> &pontosRecolha,
                 const Vehicle &vehicle) : id(id), garagem(garagem), destino(destino), pontosRecolha(pontosRecolha),
                                           vehicle(vehicle) {}
