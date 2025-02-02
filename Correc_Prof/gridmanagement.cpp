#include <iostream>

#include "gridmanagement.h"
#include "type.h"
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


//Fonction implémentant modulo différent de celle par défaut
int mod(int a, int b)
{
    if(b < 0)
        return -mod(-a, -b);
    int ret = a % b;
    if(ret < 0)
        ret+=b;
    return ret;
}


void DisplayGrid (const CMat & Mat, const CMyParam & Param, vector<char> & NomTP)
{
    const unsigned KNbLine = Mat.size ();
    cout << endl;
    for (unsigned i (0); i < KNbLine; ++i)
    {
        for (char c : Mat[i])
        {
            if (c==KEmpty){
                cout << c << ' ';
            }
            else if (c==Param.MapParamChar.find("TokenP2")->second){
                Color (Param.MapParamString.find("ColorP2")->second);
                cout << c << ' ';
                Color (KColor.find("KReset")->second);
            }
            else if (c==Param.MapParamChar.find("TokenP1")->second){
                Color (Param.MapParamString.find("ColorP1")->second);
                cout << c << ' ';
                Color (KColor.find("KReset")->second);
            }
            else if (c==Param.MapParamChar.find("TokenMur")->second){
                Color (KColor.find("KBlue")->second);
                cout << c << ' ';
                Color (KColor.find("KReset")->second);
            }
            else if (c==Param.MapParamChar.find("TokenPiege")->second){
                Color (KColor.find("KRed")->second);
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
}

//first --> y ligne
//second --> x colonne
void Genere_Mur(CMat & Mat, unsigned NbLine, unsigned NbColumn, vector<CPosition> & VectorMur, const CMyParam Param,vector<CPosition> & VectorMap){
    CPosition PosMur;
    //Génère bord murs
    //Bord Haut
    for (unsigned i(0); i<NbColumn; ++i){
        PosMur.first=0;
        PosMur.second=i;
        Mat [PosMur.first][PosMur.second] = Param.MapParamChar.find("TokenMur")->second;
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
            Mat [PosMur.first][PosMur.second] = Param.MapParamChar.find("TokenMur")->second;
            VectorMur.push_back(PosMur);
            VectorMap.push_back(PosMur);
        }
    }
    //Bord Bas
    for (unsigned i(0); i<NbColumn; ++i){
        PosMur.first=NbLine-1;
        PosMur.second=i;
        Mat [PosMur.first][PosMur.second] = Param.MapParamChar.find("TokenMur")->second;
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
            Mat [PosMur.first][PosMur.second] = Param.MapParamChar.find("TokenMur")->second;
            VectorMur.push_back(PosMur);
            VectorMap.push_back(PosMur);
        }

    }

    //Murs labyrinthe
    //Crochet bas gauche
    PosMur.first=6;
    PosMur.second=3;
    Mat [PosMur.first][PosMur.second] = Param.MapParamChar.find("TokenMur")->second;
    VectorMur.push_back(PosMur);
    VectorMap.push_back(PosMur);


    for (unsigned i(3); i<6; ++i){
        PosMur.first=7;
        PosMur.second=i;
        Mat [PosMur.first][PosMur.second] = Param.MapParamChar.find("TokenMur")->second;
        VectorMur.push_back(PosMur);
        VectorMap.push_back(PosMur);
    }

    //Crochet Bas Droite
    PosMur.first=6;
    PosMur.second=NbColumn-4;
    Mat [PosMur.first][PosMur.second] = Param.MapParamChar.find("TokenMur")->second;
    VectorMur.push_back(PosMur);
    VectorMap.push_back(PosMur);

    for (unsigned i(4); i<7; ++i){
        PosMur.first=7;
        PosMur.second=NbColumn-i;
        Mat [PosMur.first][PosMur.second] = Param.MapParamChar.find("TokenMur")->second;
        VectorMur.push_back(PosMur);
        VectorMap.push_back(PosMur);
    }

    //Barre Bas Milieu
    for (unsigned i(8); i<12; ++i){
        PosMur.first=7;
        PosMur.second=i;
        Mat [PosMur.first][PosMur.second] = Param.MapParamChar.find("TokenMur")->second;
        VectorMur.push_back(PosMur);
        VectorMap.push_back(PosMur);
    }


    //Barre Verticale haut gauche
    for (unsigned i(1); i<4; ++i){
        PosMur.first=i;
        PosMur.second=3;
        Mat [PosMur.first][PosMur.second] = Param.MapParamChar.find("TokenMur")->second;
        VectorMur.push_back(PosMur);
        VectorMap.push_back(PosMur);
    }

    //Barre Horizontale millieu haut
    for (unsigned i(7); i<13; ++i){
        PosMur.first=2;
        PosMur.second=i;
        Mat [PosMur.first][PosMur.second] = Param.MapParamChar.find("TokenMur")->second;
        VectorMur.push_back(PosMur);
        VectorMap.push_back(PosMur);
    }

    //Barre verticale haut droite
    for (unsigned i(1); i<4; ++i){
        PosMur.first=i;
        PosMur.second=16;
        Mat [PosMur.first][PosMur.second] = Param.MapParamChar.find("TokenMur")->second;
        VectorMur.push_back(PosMur);
        VectorMap.push_back(PosMur);
    }

    //Génère bloc milieu
    unsigned val_y=4;
    unsigned val_x=NbColumn/2-3;
    for (unsigned i (val_y); i<val_y+2; ++i){
        for(unsigned j(val_x); j<val_x+6; ++j){
            PosMur.first=i;
            PosMur.second=j;
            Mat [PosMur.first][PosMur.second] = Param.MapParamChar.find("TokenMur")->second;
            VectorMur.push_back(PosMur);
            VectorMap.push_back(PosMur);
        }
    }
}



void Genere_MurV2(CMat & Mat, unsigned NbLine, unsigned NbColumn, vector<CPosition> & VectorMur, CMyParam Param, vector<CPosition> & VectorMap){
    CPosition PosMur;
    //Génère bord murs
    //Bord Haut
    for (unsigned i(0); i<NbColumn; ++i){
        PosMur.first=0;
        PosMur.second=i;
        Mat [PosMur.first][PosMur.second] = Param.MapParamChar.find("TokenMur")->second;
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
            Mat [PosMur.first][PosMur.second] = Param.MapParamChar.find("TokenMur")->second;
            VectorMur.push_back(PosMur);
            VectorMap.push_back(PosMur);
        }
    }
    //Bord Bas
    for (unsigned i(0); i<NbColumn; ++i){
        PosMur.first=NbLine-1;
        PosMur.second=i;
        Mat [PosMur.first][PosMur.second] = Param.MapParamChar.find("TokenMur")->second;
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
            Mat [PosMur.first][PosMur.second] = Param.MapParamChar.find("TokenMur")->second;
            VectorMur.push_back(PosMur);
            VectorMap.push_back(PosMur);
        }

    }

    //rectangle bas gauche
    PosMur.first=6;
    PosMur.second=2;
    Mat [PosMur.first][PosMur.second] = Param.MapParamChar.find("TokenMur")->second;
    VectorMur.push_back(PosMur);
    VectorMap.push_back(PosMur);


    for (unsigned i(3); i<6; ++i){
        PosMur.first=6;
        PosMur.second=i;
        Mat [PosMur.first][PosMur.second] = Param.MapParamChar.find("TokenMur")->second;
        VectorMur.push_back(PosMur);
        VectorMap.push_back(PosMur);
    }

    for (unsigned i(3); i<6; ++i){
        PosMur.first=7;
        PosMur.second=i;
        Mat [PosMur.first][PosMur.second] = Param.MapParamChar.find("TokenMur")->second;
        VectorMur.push_back(PosMur);
        VectorMap.push_back(PosMur);
    }
    PosMur.first=7;
    PosMur.second=2;
    Mat [PosMur.first][PosMur.second] = Param.MapParamChar.find("TokenMur")->second;
    VectorMur.push_back(PosMur);
    VectorMap.push_back(PosMur);


    //ligne Bas et haut Droite
    for (unsigned i(6); i<9; ++i){
        PosMur.first=i;
        PosMur.second=NbColumn-5;
        Mat [PosMur.first][PosMur.second] = Param.MapParamChar.find("TokenMur")->second;
        VectorMur.push_back(PosMur);
        VectorMap.push_back(PosMur);
    }


    for (unsigned i(0); i<4; ++i){
        PosMur.first=i;
        PosMur.second=NbColumn-5;
        Mat [PosMur.first][PosMur.second] = Param.MapParamChar.find("TokenMur")->second;
        VectorMur.push_back(PosMur);
        VectorMap.push_back(PosMur);
    }

    //Barre Bas Milieu
    for (unsigned i(6); i<8; ++i){
        PosMur.first=i;
        PosMur.second=9;
        Mat [PosMur.first][PosMur.second] = Param.MapParamChar.find("TokenMur")->second;
        VectorMur.push_back(PosMur);
        VectorMap.push_back(PosMur);
    }


    for (unsigned i(6); i<8; ++i){
        PosMur.first=i;
        PosMur.second=10;
        Mat [PosMur.first][PosMur.second] = Param.MapParamChar.find("TokenMur")->second;
        VectorMur.push_back(PosMur);
        VectorMap.push_back(PosMur);
    }

    //Crochet en haut à gauche
    for (unsigned i(2); i<5; ++i){
        PosMur.first=i;
        PosMur.second=2;
        Mat [PosMur.first][PosMur.second] = Param.MapParamChar.find("TokenMur")->second;
        VectorMur.push_back(PosMur);
        VectorMap.push_back(PosMur);
    }

    for (unsigned i(2); i<5; ++i){
        PosMur.first=i;
        PosMur.second=3;
        Mat [PosMur.first][PosMur.second] = Param.MapParamChar.find("TokenMur")->second;
        VectorMur.push_back(PosMur);
        VectorMap.push_back(PosMur);
    }

    for (unsigned i(4); i<6; ++i){
        PosMur.first=4;
        PosMur.second=i;
        Mat [PosMur.first][PosMur.second] = Param.MapParamChar.find("TokenMur")->second;
        VectorMur.push_back(PosMur);
        VectorMap.push_back(PosMur);
    }

    for (unsigned i(1); i<4; ++i){
        PosMur.first=i;
        PosMur.second=5;
        Mat [PosMur.first][PosMur.second] = Param.MapParamChar.find("TokenMur")->second;
        VectorMur.push_back(PosMur);
        VectorMap.push_back(PosMur);
    }

    //Barre Horizontale millieu haut
    for (unsigned i(7); i<11; ++i){
        PosMur.first=2;
        PosMur.second=i;
        Mat [PosMur.first][PosMur.second] = Param.MapParamChar.find("TokenMur")->second;
        VectorMur.push_back(PosMur);
        VectorMap.push_back(PosMur);
    }

    for (unsigned i(12); i<14; ++i){
        PosMur.first=2;
        PosMur.second=i;
        Mat [PosMur.first][PosMur.second] = Param.MapParamChar.find("TokenMur")->second;
        VectorMur.push_back(PosMur);
        VectorMap.push_back(PosMur);
    }


    //Barre verticale haut droite
    for (unsigned i(1); i<4; ++i){
        PosMur.first=i;
        PosMur.second=16;
        Mat [PosMur.first][PosMur.second] = Param.MapParamChar.find("TokenMur")->second;
        VectorMur.push_back(PosMur);
        VectorMap.push_back(PosMur);
    }

    //Génère bloc milieu
    unsigned val_y=4;
    unsigned val_x=NbColumn/2-3;
    for (unsigned i (val_y); i<val_y+2; ++i){
        for(unsigned j(val_x); j<val_x+6; ++j){
            PosMur.first=i;
            PosMur.second=j;
            Mat [PosMur.first][PosMur.second] = Param.MapParamChar.find("TokenMur")->second;
            VectorMur.push_back(PosMur);
            VectorMap.push_back(PosMur);
        }
    }
}

void Genere_Piege(CMat & Mat, unsigned NbLine, unsigned NbColumn, vector<CPosition> & VectorPiege, unsigned NbPiege, vector<CPosition> & VectorMap){

    unsigned i(0);
    bool trouv(false);
    while (i<NbPiege){
        trouv=false;
        CPosition PosPiege;
        PosPiege.first= rand()%NbLine;
        PosPiege.second = rand()%NbColumn;

        //Détecte si les pièges générés sont sur des cases occupés
        for (size_t j(0); j<VectorMap.size(); ++j){
            if (PosPiege==VectorMap[j]){
                trouv=true;
                break;
            }
        }
        if (!trouv){
            Mat[PosPiege.first][PosPiege.second]='*';
            VectorPiege.push_back(PosPiege);
            VectorMap.push_back(PosPiege);
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
        //Détecte si les points de TP sont sur des cases occupés
        for (size_t j(0); j<VectorMap.size(); ++j){
            if (PosTP1==VectorMap[j] || PosTP2==VectorMap[j]){
                trouv=true;
                break;
            }
        }
        //Case Libre
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
}



void InitGrid (CMat & Mat, CMyParam & Param, CPosition & PosPlayer1, CPosition & PosPlayer2, vector<TP> & VectorTP, unsigned NbTP,
                vector<char> & NomTP, vector<CPosition> & VectorMur, vector<CPosition> & VectorPiege, unsigned NbPiege, vector<CPosition> & VectorMap, unsigned TypePart){

    unsigned NbLine =Param.MapParamUnsigned.find("NbLine")->second;
    unsigned NbColumn=Param.MapParamUnsigned.find("NbColumn")->second;

    //Initialise la grille sous forme de matrice
    Mat.resize (NbLine);
    const CVLine KLine (NbColumn, KEmpty);
    for (CVLine &ALine : Mat)
        ALine = KLine;

    //Place les joueurs sur la grille
    PosPlayer1.first = 1;
    PosPlayer1.second = 1;
    Mat [PosPlayer1.first][PosPlayer1.second] = Param.MapParamChar.find("TokenP2")-> second;
    PosPlayer2.first = NbLine-2;
    PosPlayer2.second =NbColumn-2;
    Mat [PosPlayer2.first][PosPlayer2.second]= Param.MapParamChar.find("TokenP1")-> second;

    //Génère les obstacles sur la grille
    if (TypePart==1)
        Genere_Mur(Mat,NbLine, NbColumn, VectorMur,Param, VectorMap);
    else
        Genere_MurV2(Mat,NbLine,NbColumn, VectorMur, Param, VectorMap);

    Genere_TP(Mat, NbLine, NbColumn, VectorTP, NbTP, NomTP,VectorMap);
    Genere_Piege(Mat,NbLine,NbColumn,VectorPiege, NbPiege,VectorMap);

}
