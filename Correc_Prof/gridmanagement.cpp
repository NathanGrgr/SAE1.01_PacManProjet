#include <iostream>
//#include <iomanip>
#include "gridmanagement.h"
#include "type.h" //nos types
#include <vector>
#include <string>

using namespace std;


void ClearScreen()
{
    cout << "\033[H\033[2J";
}


void Color (const string & Col)
{
    cout << "\033[" << Col.c_str () <<"m";
}


void affichVectChar(vector<char> v){
    for (size_t i(0); i<v.size(); ++i){
        cout << v[i] << " , ";
    }
    cout << endl;
}

//Permet d'afficher les 2 éléments d'un pair
void affichPair(CPosition & Pair){
    cout << Pair.first << " : " << Pair.second << endl;
}

//Affiche tous les éléments d'un vecteur de Pair
void affichVectPair (vector<CPosition> & v){
    for (size_t i(0); i<v.size(); ++i){
        affichPair(v[i]);
        cout << ';';
    }
    cout << endl;
}

//Affiche tous les éléments de 2 à 2 d'un struct composé de 2 vecteurs de pairs
void affichVectStructPair (vector<TP> v){
    for (size_t i(0); i < v.size(); ++i){
        affichPair(v[i].PosTP1);
        affichPair(v[i].PosTP2);
    }
    cout << endl;
}

void affichVectBool(vector<bool> v){
    for (size_t i(0); i<v.size(); ++i){
        cout << i+1 << " : " << v[i] << "\t";
    }
    cout << endl;
}


void DisplayGrid (const CMat & Mat, vector<char> & NomTP)
{
    const unsigned KNbLine = Mat.size ();
    const unsigned KNbCol  = Mat[0].size ();
    //cout << string (KNbCol + 2 , '-') << endl;
    cout << endl;
    for (unsigned i (0); i < KNbLine; ++i)
    {
        for (char c : Mat[i])
        {
            if (c==KEmpty){
                cout << c << ' ';
            }
            else if (c=='X'){
                Color (KColor.find("KYellow")->second);
                cout << c << ' ';
                Color (KColor.find("KReset")->second);
            }
            else if (c=='O'){
                Color (KColor.find("KRed")->second);
                cout << c << ' ';
                Color (KColor.find("KReset")->second);
            }
            else if (c=='M'){
                Color (KColor.find("KBlue")->second);
                cout << c << ' ';
                Color (KColor.find("KReset")->second);
            }
            else{
                for (size_t j(0); j<NomTP.size(); ++j){
                    if (c==NomTP[j]){
                        Color (KColor.find("KGreen")->second);
                        cout << c<< ' ';
                        Color (KColor.find("KReset")->second);
                    }
                }
            }
        }
        cout << endl;
    }

    cout << endl;
    //cout << string (KNbCol + 2 , '-') << endl;
}

//Génère obstacles sur la map
// void Genere_Mur(CMat & Mat, unsigned NbLine, unsigned NbColumn, vector<CPosition> & VectorMur, unsigned NbMur, vector<CPosition> & VectorMap){
//     bool trouv(false);
//     unsigned i(0);
//     while (i<NbMur){
//         trouv=false;
//         CPosition PosMur;
//         PosMur.first=rand()%NbLine;
//         PosMur.second=rand()%NbColumn;

//         for (size_t j(0); j<VectorMap.size(); ++j){
//             if (PosMur==VectorMap[i]){
//                 trouv=true;
//             }
//         }
//         if (trouv==false){
//             Mat [PosMur.first][PosMur.second] = 'M';
//             VectorMap.push_back(PosMur);
//             VectorMur.push_back(PosMur);
//             ++i;
//         }
//     }

// }


//first --> y ligne
//second --> x colonne

void Genere_Mur(CMat & Mat, unsigned NbLine, unsigned NbColumn, vector<CPosition> & VectorMur, vector<CPosition> & VectorMap){
    CPosition PosMur;

    //Génère bord murs
    //Bord Haut
    for (unsigned i(0); i<NbColumn; ++i){
        PosMur.first=0;
        PosMur.second=i;
        Mat [PosMur.first][PosMur.second] = 'M';
        VectorMur.push_back(PosMur);
        VectorMap.push_back(PosMur);
    }
    //Bord Gauche
    for (unsigned i(0); i<NbLine; ++i){
        PosMur.first=i;
        PosMur.second=0;
        if (PosMur.first==4 || PosMur.first==5)
            continue;
        else{
            Mat [PosMur.first][PosMur.second] = 'M';
            VectorMur.push_back(PosMur);
            VectorMap.push_back(PosMur);
        }
    }
    //Bord Bas
    for (unsigned i(0); i<NbColumn; ++i){
        PosMur.first=NbLine-1;
        PosMur.second=i;
        Mat [PosMur.first][PosMur.second] = 'M';
        VectorMur.push_back(PosMur);
        VectorMap.push_back(PosMur);

    }
    //Bord Droite
    for (unsigned i(0); i<NbLine; ++i){
        PosMur.first=i;
        PosMur.second=NbColumn-1;
        if (PosMur.first==4 || PosMur.first==5)
            continue;
        else{
            Mat [PosMur.first][PosMur.second] = 'M';
            VectorMur.push_back(PosMur);
            VectorMap.push_back(PosMur);
        }

    }

    //Début portail haut gauche
    // PosMur.first=3;
    // PosMur.second=1;
    // Mat [PosMur.first][PosMur.second] = 'M';
    // VectorMur.push_back(PosMur);
    // PosMur.first=3;
    // PosMur.second=2;
    // Mat [PosMur.first][PosMur.second] = 'M';
    // VectorMur.push_back(PosMur);

    //Début portail bas gauche
    // PosMur.first=6;
    // PosMur.second=1;
    // Mat [PosMur.first][PosMur.second] = 'M';
    // VectorMur.push_back(PosMur);
    // PosMur.first=6;
    // PosMur.second=2;
    // Mat [PosMur.first][PosMur.second] = 'M';
    // VectorMur.push_back(PosMur);


    //Murs labyrinthe
    //Crochet bas gauche
    PosMur.first=6;
    PosMur.second=3;
    Mat [PosMur.first][PosMur.second] = 'M';
    VectorMur.push_back(PosMur);
    VectorMap.push_back(PosMur);

    PosMur.first=7;
    PosMur.second=3;
    Mat [PosMur.first][PosMur.second] = 'M';
    VectorMur.push_back(PosMur);
    VectorMap.push_back(PosMur);

    PosMur.first=7;
    PosMur.second=4;
    Mat [PosMur.first][PosMur.second] = 'M';
    VectorMur.push_back(PosMur);
    VectorMap.push_back(PosMur);

    PosMur.first=7;
    PosMur.second=5;
    Mat [PosMur.first][PosMur.second] = 'M';
    VectorMur.push_back(PosMur);
    VectorMap.push_back(PosMur);

    //Crochet Bas Droite
    PosMur.first=6;
    PosMur.second=NbColumn-4;
    Mat [PosMur.first][PosMur.second] = 'M';
    VectorMur.push_back(PosMur);
    VectorMap.push_back(PosMur);

    PosMur.first=7;
    PosMur.second=NbColumn-4;
    Mat [PosMur.first][PosMur.second] = 'M';
    VectorMur.push_back(PosMur);
    VectorMap.push_back(PosMur);

    PosMur.first=7;
    PosMur.second=NbColumn-5;
    Mat [PosMur.first][PosMur.second] = 'M';
    VectorMur.push_back(PosMur);
    VectorMap.push_back(PosMur);

    PosMur.first=7;
    PosMur.second=NbColumn-6;
    Mat [PosMur.first][PosMur.second] = 'M';
    VectorMur.push_back(PosMur);
    VectorMap.push_back(PosMur);


    //Barre Bas Milieu
    PosMur.first=7;
    PosMur.second=8;
    Mat [PosMur.first][PosMur.second] = 'M';
    VectorMur.push_back(PosMur);
    VectorMap.push_back(PosMur);

    PosMur.first=7;
    PosMur.second=9;
    Mat [PosMur.first][PosMur.second] = 'M';
    VectorMur.push_back(PosMur);
    VectorMap.push_back(PosMur);

    PosMur.first=7;
    PosMur.second=10;
    Mat [PosMur.first][PosMur.second] = 'M';
    VectorMur.push_back(PosMur);
    VectorMap.push_back(PosMur);

    PosMur.first=7;
    PosMur.second=11;
    Mat [PosMur.first][PosMur.second] = 'M';
    VectorMur.push_back(PosMur);
    VectorMap.push_back(PosMur);

    //Barre Verticale haut gauche
    PosMur.first=1;
    PosMur.second=3;
    Mat [PosMur.first][PosMur.second] = 'M';
    VectorMur.push_back(PosMur);
    VectorMap.push_back(PosMur);

    PosMur.first=2;
    PosMur.second=3;
    Mat [PosMur.first][PosMur.second] = 'M';
    VectorMur.push_back(PosMur);
    VectorMap.push_back(PosMur);

    PosMur.first=3;
    PosMur.second=3;
    Mat [PosMur.first][PosMur.second] = 'M';
    VectorMur.push_back(PosMur);
    VectorMap.push_back(PosMur);

    //Barre Horizontale millieu haut
    PosMur.first=2;
    PosMur.second=7;
    Mat [PosMur.first][PosMur.second] = 'M';
    VectorMur.push_back(PosMur);
    VectorMap.push_back(PosMur);

    PosMur.first=2;
    PosMur.second=8;
    Mat [PosMur.first][PosMur.second] = 'M';
    VectorMur.push_back(PosMur);
    VectorMap.push_back(PosMur);

    PosMur.first=2;
    PosMur.second=9;
    Mat [PosMur.first][PosMur.second] = 'M';
    VectorMur.push_back(PosMur);
    VectorMap.push_back(PosMur);

    PosMur.first=2;
    PosMur.second=10;
    Mat [PosMur.first][PosMur.second] = 'M';
    VectorMur.push_back(PosMur);
    VectorMap.push_back(PosMur);

    PosMur.first=2;
    PosMur.second=11;
    Mat [PosMur.first][PosMur.second] = 'M';
    VectorMur.push_back(PosMur);
    VectorMap.push_back(PosMur);

    PosMur.first=2;
    PosMur.second=12;
    Mat [PosMur.first][PosMur.second] = 'M';
    VectorMur.push_back(PosMur);
    VectorMap.push_back(PosMur);

    //Barre verticale haut droite
    PosMur.first=1;
    PosMur.second=16;
    Mat [PosMur.first][PosMur.second] = 'M';
    VectorMur.push_back(PosMur);
    VectorMap.push_back(PosMur);

    PosMur.first=2;
    PosMur.second=16;
    Mat [PosMur.first][PosMur.second] = 'M';
    VectorMur.push_back(PosMur);
    VectorMap.push_back(PosMur);

    PosMur.first=3;
    PosMur.second=16;
    Mat [PosMur.first][PosMur.second] = 'M';
    VectorMur.push_back(PosMur);
    VectorMap.push_back(PosMur);

    //Génère bloc milieu
    unsigned val_y=4;
    unsigned val_x=NbColumn/2-3;
    for (unsigned i (val_y); i<val_y+2; ++i){
        for(unsigned j(val_x); j<val_x+6; ++j){
            PosMur.first=i;
            PosMur.second=j;
            Mat [PosMur.first][PosMur.second] = 'M';
            VectorMur.push_back(PosMur);
            VectorMap.push_back(PosMur);
        }
    }
}


//Génère les TP en fonction du NbTP et le stocke dans le struc TP
void Genere_TP(CMat & Mat, unsigned NbLine, unsigned NbColumn, vector<TP> & VectorTP, unsigned NbTP, vector<char> & NomTP, vector<CPosition> & VectorMap){
    char val = 'A';
    unsigned i(0);
    bool trouv(false);
    while (i<NbTP){
        trouv=false;
        CPosition PosTP1, PosTP2;
        PosTP1.first = rand()%NbLine;
        PosTP1.second = rand()%NbColumn;
        PosTP2.first = rand()%NbLine;
        PosTP2.second = rand()%NbColumn;

        if (PosTP1==PosTP2){
            continue;
        }
        for (size_t j(0); j<VectorMap.size(); ++j){
            if (PosTP1==VectorMap[j] || PosTP2==VectorMap[j]){
                trouv=true;
                break;
            }
        }
        if (!trouv){
            Mat [PosTP1.first][PosTP1.second] = val;
            Mat [PosTP2.first][PosTP2.second] = val;
            VectorTP.push_back(TP{PosTP1,PosTP2});

            VectorMap.push_back(PosTP1);
            VectorMap.push_back(PosTP2);
            NomTP.push_back(val);
            ++val;
            ++i;
        }
    }
    //affichVectPair(VectorMap);
}



void InitGrid (CMat & Mat, unsigned NbLine, unsigned NbColumn, CPosition & PosPlayer1, CPosition & PosPlayer2, vector<TP> & VectorTP, unsigned NbTP,
                vector<char> & NomTP, vector<CPosition> & VectorMur, vector<CPosition> & VectorMap){

    Mat.resize (NbLine);
    const CVLine KLine (NbColumn, KEmpty);
    for (CVLine &ALine : Mat)
        ALine = KLine;
    PosPlayer1.first = 1;
    PosPlayer1.second = 1;
    Mat [PosPlayer1.first][PosPlayer1.second] = 'X';
    PosPlayer2.first = NbLine-2;
    PosPlayer2.second =NbColumn-2;
    Mat [PosPlayer2.first][PosPlayer2.second]   = 'O';
    Genere_Mur(Mat,NbLine, NbColumn, VectorMur, VectorMap);
    Genere_TP(Mat, NbLine, NbColumn, VectorTP, NbTP, NomTP,VectorMap);

}
