#include <iostream>
#include <vector>

#include "game.h"
#include "params.h"
#include "gridmanagement.h"
#include "type.h"
#include <map>


/*
 * Corriger bug lors de TP (tour en + pour le joueur qui prend le tp)
 */


using namespace std;
//z, q, x, d, a, e, w, c
//Permet de faire bouger le joueur sur la map en fonction de l'entrée saisie
void MoveToken (CMat & Mat, const char & Move, CPosition & Pos, vector<bool> VectorBloque)
{
    //affichVectBool(VectorBloque);
    //cout << Move << endl;
    char car = Mat [Pos.first][Pos.second];
    Mat [Pos.first][Pos.second] = KEmpty;

    switch (Move)
    {
    case 'Z':
        if (!VectorBloque[0])
            --Pos.first;
        break;
    case 'Q':
        if(Pos.second<=0)
            Pos.second=mod((Pos.second-1),20);

        else if (!VectorBloque[1])
            --Pos.second;
        break;
    case 'X':
        if (!VectorBloque[2])
            ++Pos.first;
        break;
    case 'D':
        if(Pos.second>=int(Mat.size()))
            Pos.second=mod((Pos.second+1),20);
        else if (!VectorBloque[3])
            ++Pos.second;
        break;
    case 'A':
        if (!VectorBloque[4]){
            -- Pos.first;
            -- Pos.second;
        }
        break;
    case 'E':
        if (!VectorBloque[5]){
            --Pos.first;
            ++Pos.second;
        }
        break;
    case 'W':
        if (!VectorBloque[6]){
            ++Pos.first;
            --Pos.second;
        }
        break;
    case 'C':
        if(!VectorBloque[7]){
            ++Pos.first;
            ++Pos.second;
        }
    }affichPair(Pos);
    Mat [Pos.first][Pos.second] = car;
    affichPair(Pos);
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



void Piege_Verif(CPosition & Pos,vector<CPosition> & VectorPiege, bool & Piege_Actif){
    Piege_Actif=false;
    for (size_t i(0); i<VectorPiege.size(); ++i){
        if (Pos==VectorPiege[i])
            Piege_Actif=true;
    }
}


// first --> y
// second --> x
void Mur_Verif (CPosition & Pos, vector<CPosition> VectorMur,vector<bool> & VectorBloque){
    VectorBloque.clear();
    VectorBloque = {false,false,false,false,false,false,false,false,false};
    for (size_t i(0); i<VectorMur.size(); ++i){
        //z
        if (Pos.first-1==VectorMur[i].first && Pos.second==VectorMur[i].second)
            VectorBloque[0]=true;


        //q
        else if (Pos.first==VectorMur[i].first && Pos.second-1==VectorMur[i].second)
            VectorBloque[1]=true;
        //x
        else if (Pos.first+1==VectorMur[i].first && Pos.second==VectorMur[i].second)
            VectorBloque[2]=true;
        //d
        else if (Pos.first==VectorMur[i].first && Pos.second+1==VectorMur[i].second)
            VectorBloque[3]=true;

        //a = (z+q)
        else if (Pos.first-1==VectorMur[i].first && Pos.second-1==VectorMur[i].second)
            VectorBloque[4]=true;

        //e (z + d)
        else if (Pos.first-1==VectorMur[i].first && Pos.second+1==VectorMur[i].second)
            VectorBloque[5]=true;
        //w (q + x)
        else if (Pos.first+1==VectorMur[i].second && Pos.second-1==VectorMur[i].first)
            VectorBloque[6]=true;
        //c (x + d)
        else if (Pos.first+1==VectorMur[i].first && Pos.second+1==VectorMur[i].second)
            VectorBloque[7]=true;
    }

}




int ppal (void){
    bool Victory (false);
    unsigned KSize (10);
    unsigned PartyNum (1);
    const unsigned KMaxPartyNum (KSize * KSize);
    CMat Mat;
    unsigned TypePart;

    bool Player1Turn (true);

    //Stocke les positions courantes des joueurs
    CPosition PosPlayer1, PosPlayer2;
    //Stocke les coordonnées des murstest

    vector<CPosition> VectorMur;
    //Srocke les coordonnées des TP
    vector<TP> VectorTP;
    //Stocke tous les noms des couples de TP
    vector<char> NomTP;
    //Stocke tous les obstacles possédant des coordonnées sur la matrice
    vector<CPosition>VectorMap;
    vector<bool> VectorBloque;
    vector<CPosition> VectorPiege;
    bool Piege_Actif;

    CMyParam Param;
    InitParams(Param);
    LoadParams(Param);

    cout << "Bienvenue sur PacMan :" << endl ;
    cout << "Pour aller au niveau 1 tapez 1" << endl ;
    cout << "Pour aller au niveau 2 tapez 2" << endl ;
    cout << "Pour aller au niveau 3 tapez 3" << endl ;
    cin >> TypePart;
    if (TypePart == 1)
    {
        InitGrid(Mat, Param ,PosPlayer1, PosPlayer2, VectorTP, 4, NomTP,VectorMur, VectorPiege, 3, VectorMap);
    }
    else if (TypePart == 2)
    {
        InitGrid(Mat, Param, PosPlayer1, PosPlayer2, VectorTP, 1, NomTP, VectorMur,VectorPiege, 2, VectorMap);
    }
    else if (TypePart==3)
    {
        InitGrid(Mat, Param,PosPlayer1, PosPlayer2, VectorTP, 1, NomTP, VectorMur, VectorPiege, 1,VectorMap);
    }

    DisplayGrid (Mat, Param,NomTP);
    while (PartyNum <= KMaxPartyNum && ! Victory)
    {


        cout << "tour numero : " << PartyNum << ", Joueur"
             << (Player1Turn ? 'X' : 'O') << ", entrez un déplacement : ";

        char Move;
        cin >> Move;

        Move = toupper (Move);

        Mur_Verif((Player1Turn ? PosPlayer1 : PosPlayer2),VectorMur,VectorBloque);
        MoveToken (Mat, Move, (Player1Turn ? PosPlayer1: PosPlayer2), VectorBloque);
        //affichVectStructPair(VectorTP);
        //affichVectPair(VectorMap);
        //affichVectBool(VectorBloque);
        TP_Verif(Mat, (Player1Turn ? PosPlayer1 : PosPlayer2), VectorTP, Player1Turn);
        Piege_Verif((Player1Turn ? PosPlayer1 : PosPlayer2),VectorPiege, Piege_Actif);


        ClearScreen();
        DisplayGrid (Mat,Param, NomTP);

        cout << Player1Turn << endl;
        //Test de condition de victoire
        if (PosPlayer1 == PosPlayer2) Victory = true;


        if ((Move=='Z' && !VectorBloque[0]) || (Move=='Q' && !VectorBloque[1])  || (Move=='X' && !VectorBloque[2]) ||
            (Move=='D'&& !VectorBloque[3]) || (Move=='A' && !VectorBloque[4]) || (Move=='E' && !VectorBloque[5]) ||
            (Move=='W' && !VectorBloque[6]) || (Move=='C' && !VectorBloque[7])){
            ++PartyNum;
            Player1Turn = !Player1Turn;
        }

        if (Piege_Actif){
            break;
        }

    }

    if (!Victory && !Piege_Actif)
    {
        Color (KColor.find("KMAgenta")->second);
        cout << "Aucun vainqueur" << endl;
        return 1;
    }

    else if (Piege_Actif){
        Color (KColor.find("KGreen")->second);
        cout << "Félicitations Joueur " << (Player1Turn ? 'X' : 'O')
             << " vous avez gagné :). Cause Piège" << endl;
        Color (KColor.find("KReset")->second);
        return 1;
    }
    Color (KColor.find("KGreen")->second);
    cout << "Félicitations Joueur " << (Player1Turn ? 'O' : 'X')
         << " vous avez gagné :)" << endl;
    Color (KColor.find("KReset")->second);
    return 0;
} //ppal ()
