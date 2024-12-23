#include <iostream>
#include <vector>

#include "game.h"
#include "params.h"
#include "gridmanagement.h"
#include "type.h"
#include <map>

using namespace std;

//Permet de faire bouger le joueur sur la map en fonction de l'entrée saisie
void MoveToken (CMat & Mat, const char & Move, CPosition & Pos)
{
    char car = Mat [Pos.first][Pos.second];
    Mat [Pos.first][Pos.second] = KEmpty;
    switch (Move)
    {
    case 'A':
        -- Pos.first;
        -- Pos.second;
        break;
    case 'Z':
        --Pos.first;
        break;
    case 'E':
        --Pos.first;
        ++Pos.second;
        break;
    case 'Q':
        --Pos.second;
        break;
    case 'D':
        ++Pos.second;
        break;
    case 'W':
        ++Pos.first;
        --Pos.second;
        break;
    case 'X':
        ++Pos.first;
        break;
    case 'C':
        ++Pos.first;
        ++Pos.second;
        break;
    }
    Mat [Pos.first][Pos.second] = car;
} //MoveToken ()


//Vérifie si le joueur est sur un des points du/des TP
void TP_Verif (CMat & Mat, CPosition & Pos, vector<TP> & PosTP, bool & Player1Turn){
    for (size_t i(0); i < PosTP.size(); ++i){
        if (Pos.first == PosTP[i].PosTP1.first && Pos.second==PosTP[i].PosTP1.second){
            Mat[Pos.first][Pos.second]=' ';
            Pos.first=PosTP[i].PosTP2.first;
            Pos.second=PosTP[i].PosTP2.second;
            PosTP.erase(PosTP.begin()+i);
            if (Player1Turn){
                Mat[Pos.first][Pos.second]='X';
            }
            else if (!Player1Turn){
                Mat[Pos.first][Pos.second]='O';
            }
        }
        else if (Pos.first == PosTP[i].PosTP2.first && Pos.second==PosTP[i].PosTP2.second){
            Mat[Pos.first][Pos.second]=' ';
            Pos.first=PosTP[i].PosTP1.first;
            Pos.second=PosTP[i].PosTP1.second;
            PosTP.erase(PosTP.begin()+i);
            if (Player1Turn){
                Mat[Pos.first][Pos.second]='X';
            }
            else if (!Player1Turn){
                Mat[Pos.first][Pos.second]='O';
            }
        }
    }
}

void Mur_Verif (CMat & Mat, CPosition & Pos, vector<CPosition> & VectorMur){
}

int ppal (void){

    unsigned KSize (10);
    unsigned PartyNum (1);
    const unsigned KMaxPartyNum (KSize * KSize);
    CMat Mat;
    unsigned TypePart;

    bool Player1Turn (true);
    bool Victory (false);
    CPosition PosPlayer1, PosPlayer2;
    vector<CPosition> VectorMur;
    vector<TP> VectorTP;
    vector<char> NomTP;

    cout << "veuillez choisir votre type de partie :" << endl ;
    cout << "Pour effectuer une Partie longue tapez 1" << endl ;
    cout << "Pour effectuer une Partie classique tapez 2" << endl ;
    cout << "Pour effectuer une Partie rapide tapez 3" << endl ;
    cin >> TypePart;
    if (TypePart == 1)
    {
        InitGrid(Mat, 10, 10, PosPlayer1, PosPlayer2, VectorTP, 3, NomTP,VectorMur, 1);
    }
    else if (TypePart == 2)
    {
        InitGrid(Mat, 7, 7, PosPlayer1, PosPlayer2, VectorTP, 1, NomTP, VectorMur, 1);
    }
    else if (TypePart==3)
    {
        InitGrid(Mat, 4, 4, PosPlayer1, PosPlayer2, VectorTP, 1, NomTP, VectorMur, 1);
    }

    DisplayGrid (Mat);
    while (PartyNum <= KMaxPartyNum && ! Victory)
    {
        affichStructVectPair(VectorTP);
        cout << "tour numero : " << PartyNum << ", Joueur"
             << (Player1Turn ? 'X' : 'O') << ", entrez un déplacement : ";

        char Move;
        cin >> Move;

        Move = toupper (Move);
        MoveToken (Mat, Move, (Player1Turn ? PosPlayer1: PosPlayer2));
        TP_Verif(Mat, (Player1Turn ? PosPlayer1 : PosPlayer2), VectorTP, Player1Turn);
        ClearScreen();
        DisplayGrid (Mat);

        //Test de condition de victoire
        if (PosPlayer1 == PosPlayer2) Victory = true;

        ++PartyNum;

        //Change tour du joueur
        Player1Turn = !Player1Turn;
    }

    if (!Victory)
    {
        Color (KColor.find("KMAgenta")->second);
        cout << "Aucun vainqueur" << endl;
        return 1;
    }

    Color (KColor.find("KGreen")->second);
    cout << "Félicitations Joueur" << (Player1Turn ? '2' : '1')
         << " vous avez gagné :)" << endl;
    Color (KColor.find("KReset")->second);
    return 0;
} //ppal ()
