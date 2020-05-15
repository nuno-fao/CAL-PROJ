//
// Created by Nunation on 15/05/2020.
//

#include "Menus.h"
#include <iostream>

int mainMenu(){

    unsigned int i;

    do {
        cout << endl;
        cout << "[0] Load a graph and generate its table and accessible nodes (VERY IMPORTANT TO DO THIS BEFORE ANYTHING ELSE!!!)" << endl;
        cout << "[1] Display full graph" << endl;
        cout << "[2] Display accesible nodes from the garage" << endl;
        cout << "[3] Explain how to generate a service and list accesible nodes from the garage (in case you need help)" << endl;
        cout << "[4] Load a service and display optimal path solution" << endl;
        cout << "[5] Exit program" << endl;
        cin >> i;
        cout << endl << endl;

        if(i > 5)
            cout << "Invalid option. Please try again." << endl << endl;

    } while(i > 5);

    return i;
}

int chooseCity(string& city){
    unsigned int i;

    do {
        cout << "Please select the desired map:" << endl;
        cout << "[0] Aveiro" << endl;
        cout << "[1] Braga" << endl;
        cout << "[2] Coimbra" << endl;
        cout << "[3] Ermesinde" << endl;
        cout << "[4] Fafe" << endl;
        cout << "[5] Gondomar" << endl;
        cout << "[6] Lisboa (not recommended, may take a while due to huge size)" << endl;
        cout << "[7] Maia" << endl;
        cout << "[8] Porto" << endl;
        cout << "[9] Viseu" << endl;
        cout << "[10] Cancelar..." << endl;

        cin >> i;
        cout << endl;

        if(i > 10)
            cout << "Invalid map number!" << endl;

    } while(i > 10);

    if(i==10){return -1;}

    switch(i){
        case 0:
            city="aveiro";
            break;
        case 1:
            city="braga";
            break;
        case 2:
            city="coimbra";
            break;
        case 3:
            city="ermesinde";
            break;
        case 4:
            city="fafe";
            break;
        case 5:
            city="gondomar";
            break;
        case 6:
            city="lisboa";
            break;
        case 7:
            city="maia";
            break;
        case 8:
            city="porto";
            break;
        case 9:
            city="viseu";
            break;
        default:
            break;
    }

    return 0;

}

void help(vector<Vertex<Node>*> accessible){
    cout<<"Here all accessible nodes:"<<endl<<endl;
    for(auto i : accessible){
        cout<<"("<<i->getInfo().getId()<<");\t";
    }
    cout<<endl<<endl;

    cout<<"About the service criation:\n";
    cout<<"1 - Create a text file with whatever name you whish (i.e. banana.txt)\n";
    cout<<"2 - The first line of the file should be the integer of the ID of your factory's node and nothing else\n";
    cout<<"3 - The next should also be an integer indicating how many pickup nodes are about to be read (that you will list) and nothing else\n";
    cout<<"4 - All the lines following these should only cointain one integer corresponding to the ID of a pickup node\n";
    cout<<"5 - Put that file inside the corresponding city folder in the 'files' directory\n\n";
    cout<<"Example of the content of a service file:\n\n";
    cout<<"15202115\n";
    cout<<"2\n";
    cout<<"561235\n";
    cout<<"5165518\n";
    cout<<"\n-------------------\n";
}