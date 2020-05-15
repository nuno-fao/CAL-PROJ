//
// Created by Nunation on 15/05/2020.
//

#ifndef CAL_PROJ_MENUS_H
#define CAL_PROJ_MENUS_H

#include <string>

using namespace std;

/**
 * Menu inicial
 *
 * @return Um inteiro que indica o que utilizador quer fazer
 */
int mainMenu();

/**
 * Menu que pergunta ao utilizar de qual cidade pretende carregar o grafo
 *
 * @param string objeto para onde vai ser escrito o nome da cidade para uso futuro
 *
 * @return 0 se o utilizador escolheu alguma cidade, -1 se cancelou
 */
int chooseCity(string& city);

#endif //CAL_PROJ_MENUS_H
