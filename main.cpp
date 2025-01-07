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
void configureTerminal(struct termios& oldSettings, struct termios& newSettings) {
    // Récupérer les paramètres actuels
    tcgetattr(STDIN_FILENO, &oldSettings);

    // Configurer les nouveaux paramètres
    newSettings = oldSettings;
    newSettings.c_lflag &= ~(ICANON | ECHO); // Désactiver le mode canonique et l'écho
    newSettings.c_cc[VMIN] = 1;  // Lire au moins 1 caractère avant de continuer
    newSettings.c_cc[VTIME] = 0; // Pas de délai pour la lecture

    // Appliquer les paramètres
    tcsetattr(STDIN_FILENO, TCSANOW, &newSettings);
}

// Fonction pour restaurer les paramètres d'origine du terminal
void restoreTerminal(const struct termios& oldSettings) {
    tcsetattr(STDIN_FILENO, TCSANOW, &oldSettings); // Restaurer les paramètres
}


int main()
{
    struct termios oldSettings, newSettings;

    // Configurer le terminal
    configureTerminal(oldSettings, newSettings);

    try
    {
        int result = ppal(); // Appel de la fonction principale
        restoreTerminal(oldSettings); // Restaurer le terminal avant de quitter
        return result;
    }
    catch (...)
    {
        cerr << "ça s'est mal passé quelque part" << endl;
        return 1;
    }
} //main ()



