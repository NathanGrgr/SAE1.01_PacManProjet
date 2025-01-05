#include <string>
#include "params.h"
#include <fstream>
#include <iostream>
#include <map>
#include <iostream>
#include <algorithm>

using namespace std;

void InitParams (CMyParam & Param){
    //Move Keys
    Param.MapParamChar["KeyUp"]='z';
    Param.MapParamChar["KeyDown"]='s';
    Param.MapParamChar["KeyLeft"]='q';
    Param.MapParamChar["KeyRight"]='d';

    Param.MapParamChar["TokenP1"]='O';
    Param.MapParamChar["TokenP2"]='X';

    //Size of grid - suppose to be a rectangle
    Param.MapParamUnsigned["NbColumn"]=20;
    Param.MapParamUnsigned["NbLine"]=10;

    //Display Colors
    Param.MapParamString["ColorP1"]=KColor.find("KRed")->second;
    Param.MapParamString["ColorP2"]=KColor.find("KBlue")->second;
}

void LoadParams(CMyParam & Param){
    ifstream ifs ("../SAE1.01_PacManProjet/Nos_fichiers/config.yaml");
    /*
    if (!ifs){
        cerr << "pas de fichier de configuration ici" << endl;
        exit (-1);
    }
    */
    cout << "fichier ok" << endl;
    for (string cle, poubelle; ifs >> cle; ){
        char deuxpoints;
        ifs >>  deuxpoints;
        if (find(KAuthorizedKey.VParamChar.begin(), KAuthorizedKey.VParamChar.end(),
                 cle) != KAuthorizedKey.VParamChar.end()){
            char val;
            ifs >>val;
            Param.MapParamChar[cle]=val;
        }
        else if (find(KAuthorizedKey.VParamUnsigned.begin(), KAuthorizedKey.VParamUnsigned.end(),
                        cle) != KAuthorizedKey.VParamUnsigned.end()){
            unsigned val;
            ifs >> val;
            Param.MapParamUnsigned[cle] =val;
        }
        else if (find(KAuthorizedKey.VParamString.begin(), KAuthorizedKey.VParamString.end(),
                      cle) != KAuthorizedKey.VParamString.end()){
            string val;
            ifs >> val;
            auto it = KColor.find(val);
            if (it != KColor.end()){
                Param.MapParamString[cle] = it->second;
            }
        }
        else
            getline(ifs, poubelle);
    }
}
