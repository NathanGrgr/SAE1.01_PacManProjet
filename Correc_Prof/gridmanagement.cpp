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
void affichVectStructPair (vector<TP> & v){
    for (size_t i(0); i < v.size(); ++i){
        affichPair(v[i].PosTP1);
        affichPair(v[i].PosTP2);
    }
    cout << endl;
}


void DisplayGrid (const CMat & Mat, vector<char> & NomTP)
{
    const unsigned KNbLine = Mat.size ();
    const unsigned KNbCol  = Mat[0].size ();
    cout << string (KNbCol + 2 , '-') << endl;

    for (unsigned i (0); i < KNbLine; ++i)
    {
        cout << '|';
        for (char c : Mat[i])
        {
            if (c==KEmpty){
                cout << c;
            }
            else if (c=='X'){
                Color (KColor.find("KBlue")->second);
                cout << c;
                Color (KColor.find("KReset")->second);
            }
            else if (c=='O'){
                Color (KColor.find("KBlue")->second);
                cout << c;
                Color (KColor.find("KReset")->second);
            }
            else if (c=='M'){
                Color (KColor.find("KRed")->second);
                cout << c;
                Color (KColor.find("KReset")->second);
            }
            else{
                for (size_t j(0); j<NomTP.size(); ++j){
                    if (c==NomTP[j]){
                        Color (KColor.find("KGreen")->second);
                        cout << c;
                        Color (KColor.find("KReset")->second);
                    }
                }
            }
        }
        cout << '|' << endl;
    }


    cout << string (KNbCol + 2 , '-') << endl;
}

//Génère obstacles sur la map
void Genere_Mur(CMat & Mat, unsigned NbLine, unsigned NbColumn, vector<CPosition> & VectorMur, unsigned NbMur, vector<CPosition> & VectorMap){
    bool trouv(false);
    unsigned i(0);
    while (i<NbMur){
        trouv=false;
        CPosition PosMur;
        PosMur.first=rand()%NbLine;
        PosMur.second=rand()%NbColumn;

        for (size_t j(0); j<VectorMap.size(); ++j){
            if (PosMur==VectorMap[i]){
                trouv=true;
            }
        }
        if (trouv==false){
            Mat [PosMur.first][PosMur.second] = 'M';
            VectorMap.push_back(PosMur);
            VectorMur.push_back(PosMur);
            ++i;
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
    cout << "coucour" << endl;
    affichVectPair(VectorMap);
}



void InitGrid (CMat & Mat, unsigned NbLine, unsigned NbColumn, CPosition & PosPlayer1, CPosition & PosPlayer2, vector<TP> & VectorTP, unsigned NbTP,
                vector<char> & NomTP, vector<CPosition> & VectorMur, unsigned NbMur, vector<CPosition> & VectorMap){

    Mat.resize (NbLine);
    const CVLine KLine (NbColumn, KEmpty);
    for (CVLine &ALine : Mat)
        ALine = KLine;

    PosPlayer1.first = 0;
    PosPlayer1.second = 0;
    Mat [PosPlayer1.first][PosPlayer1.second] = 'X';
    PosPlayer2.first = NbColumn-1;
    PosPlayer2.second =NbLine-1;
    Mat [PosPlayer2.first][PosPlayer2.second]   = 'O';
    Genere_TP(Mat, NbLine, NbColumn, VectorTP, NbTP, NomTP,VectorMap);
    Genere_Mur(Mat,NbLine, NbColumn, VectorMur, NbMur, VectorMap);

}
