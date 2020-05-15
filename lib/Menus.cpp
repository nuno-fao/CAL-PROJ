//
// Created by Nunation on 15/05/2020.
//

#include "Menus.h"
#include <iostream>
using namespace std;

int mainMenu(){

    unsigned int i;

    do {
        cout << endl;
        cout << "[0] Load a graph and generate its table" << endl;
        cout << "[1] Read vehicle file" << endl;
        cout << "[2] Display graph" << endl;
        cout << "[3] Display accesible nodes from the garage" << endl;
        cout << "[4] Read service file, calculate and display vehicle paths" << endl;
        cout << "[5] Exit program" << endl;
        cin >> i;
        cout << endl << endl;

        if(i > 5)
            cout << "Invalid option. Please try again." << endl << endl;

    } while(i > 5);

    return i;
}

