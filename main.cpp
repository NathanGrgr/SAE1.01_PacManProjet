/*!
 * \file   main.cpp
 * \authors Alain Casali, Marc Laporte
 * \date december 8 2016
 * \brief   Terminal's color management
 *          beginning of the project titled "catch me if you can"
 */

#include <iostream>
#include "Correc_Prof/game.h"
#include <termios.h>
#include <unistd.h>

using namespace std;
/**
 * @brief main
 * @return return 0 iff everything is OK, 1 if we have an exception, 2 if we can't load the params' file
 */




// Fonction pour configurer le terminal en mode non canonique
void configureTerminal(struct termios& anciensParam, struct termios& nvxParams) {
    // tcgetattr -> Récupére les paramètres actuels
    tcgetattr(STDIN_FILENO, &anciensParam);

    // Configure les nouveaux paramètres et en copie pour restaurer plus tard
    nvxParams = anciensParam;
    // Désactive le mode canonique
    nvxParams.c_lflag &= ~(ICANON);

    // Applique les paramètres
    tcsetattr(STDIN_FILENO, TCSANOW, &nvxParams);
}

// Fonction pour restaurer les paramètres d'origine du terminal
void restoreTerminal(const struct termios& anciensParam) {

    tcsetattr(STDIN_FILENO, TCSANOW, &anciensParam);
}


int main()
{
    struct termios anciensParam, nvxParams;

    // Configure le terminal
    configureTerminal(anciensParam, nvxParams);

    try
    {
        int result = ppal();
        // Restaure le terminal avant de quitter pour ne pas créer de conflit
        restoreTerminal(anciensParam);
        return result;
    }
    catch (...)
    {
        cerr << "ça s'est mal passé quelque part" << endl;
        return 1;
    }
} //main ()



