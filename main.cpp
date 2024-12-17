/*!
 * \file   main.cpp
 * \authors Alain Casali, Marc Laporte
 * \date december 8 2016
 * \brief   Terminal's color management
 *          beginning of the project titled "catch me if you can"
 */

#include <iostream>
#include "Correc_Prof/game.h"

using namespace std;
/**
 * @brief main
 * @return return 0 iff everything is OK, 1 if we have an exception, 2 if we can't load the params' file
 */
int main()
{
    try
    {
        size_t TypePart;
        cout << "veuillez choisir votre type de partie :" << endl ;
        cout << "Pour effectuer une Partie longue tapez 1" << endl ;
        cout << "Pour effectuer une Partie classique tapez 2" << endl ;
        cout << "Pour effectuer une Partie rapide tapez 3" << endl ;
        cin >> TypePart ;
        if (TypePart > 3)
        {
            cout << "Il n'existe pas de partie associé a ce chiffre" << endl;
        }

        return ppal ();
    }
    catch (...)
    {
        cerr << "ca c'est mal passe quelque part" << endl;
        return 1;
    }
} //main ()



