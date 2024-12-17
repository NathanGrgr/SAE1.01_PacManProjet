#include <iostream>

#include "game.h"
#include "params.h"
#include "gridmanagement.h"

#include <map>
using namespace std;


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

void TP (CMat & Mat, CPosition & Pos, CPosition & PosTP1, CPosition & PosTP2, bool & Player1Turn){
    if (Pos.first == PosTP1.first && Pos.second==PosTP1.second){
        Mat[Pos.first][Pos.second]=' ';
        Pos.first=PosTP2.first;
        Pos.second=PosTP2.second;
        if (Player1Turn){
            Mat[Pos.first][Pos.second]='X';

        }
        else if (!Player1Turn){
            Mat[Pos.first][Pos.second]='O';
        }
    }
    //fonctionne
    else if (Pos.first == PosTP2.first && Pos.second==PosTP2.second){
        Mat[Pos.first][Pos.second]=' ';
        Pos.first=PosTP1.first;
        Pos.second=PosTP1.second;
        if (Player1Turn){
            Mat[Pos.first][Pos.second]='X';
        }
        else if (!Player1Turn){
            Mat[Pos.first][Pos.second]='O';
        }
    }
}

int ppal (void)
{

    const unsigned KSize (10);
    unsigned PartyNum (1);
    const unsigned KMaxPartyNum (KSize * KSize);
    CMat Mat;
    size_t TypePart;

    bool Player1Turn (true);
    bool Victory (false);

    CPosition PosPlayer1, PosPlayer2;
    CPosition PosTP1, PosTP2;
    if (TypePart == 1)
    {
        InitGrid(Mat, 10, 10, PosPlayer1, PosPlayer2, PosTP1, PosTP2);
    }
    else if (TypePart == 2)
    {
        InitGrid(Mat, 7, 7, PosPlayer1, PosPlayer2, PosTP1, PosTP2);
    }
    else
    {
        InitGrid(Mat, 4, 4, PosPlayer1, PosPlayer2, PosTP1, PosTP2);
    }

    DisplayGrid (Mat);

    while (PartyNum <= KMaxPartyNum && ! Victory)
    {

        cout << "tour numero : " << PartyNum << ", Joueur"
             << (Player1Turn ? '1' : '2') << ", entrez un déplacement : ";

        char Move;
        cin >> Move;

        Move = toupper (Move);
        MoveToken (Mat, Move, (Player1Turn ? PosPlayer1: PosPlayer2));
        TP(Mat, (Player1Turn ? PosPlayer1 : PosPlayer2), PosTP1, PosTP2, Player1Turn);
        ClearScreen();
        DisplayGrid (Mat);

        //Victiry test
        if (PosPlayer1 == PosPlayer2) Victory = true;

        //Increase party's number
        ++PartyNum;

        //Player changing
        Player1Turn = !Player1Turn;
    }//while (no victory)

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
