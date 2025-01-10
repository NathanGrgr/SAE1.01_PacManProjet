#ifndef GRIDMANAGEMENT_H
#define GRIDMANAGEMENT_H

/*!
 * \file gridmanagement.h
 * \brief Set of usefull functions for the grid management
 * \author Alain Casali
 * \author Marc Laporte
 * \version 1.0
 * \date 18 décembre 2018
 */

#include <string>
#include <vector>
#include "type.h" //nos types

/**
 * @brief Clear the current terminal
 * @fn void ClearScreen ();
 */
void ClearScreen ();

/**
 * @brief Set the color of the future input in the terminal
 * @param[in] Col : Next color to be used
 * @fn void Color (const std::string & Col);
 */
void Color (const std::string & Col);


/**
 * @brief Display the grid according to the parameters
 * @param[in] Mat : Game grid
 * @param[in] Params : : List of usefull parameters
 * @fn void DisplayGrid (const CMat & Mat, const CMyParam & Params, bool ShowLineNumber = true, bool ShowColor = true);
 */

void DisplayGrid (const CMat & Mat, const CMyParam & Param, std::vector<char> & NomTP);

void affichVectChar(std::vector<char> v);

void affichPair(CPosition & Pair);

void affichVectPair (std::vector<CPosition> & v);

void affichVectBool(std::vector<bool> v);

void affichVectStructPair (std::vector<TP> & v);

int mod(int a, int b);

void Genere_Mur(CMat & Mat, unsigned NbLine, unsigned NbColumn, std::vector<CPosition> & PosMur,  const CMyParam Param, std::vector<CPosition> & VectorMap);

void Genere_MurV2(CMat & Mat, unsigned NbLine, unsigned NbColumn, std::vector<CPosition> & VectorMur, const CMyParam Param,  std::vector<CPosition> & VectorMap);


void Genere_TP(CMat & Mat, unsigned NbLine, unsigned NbColumn, std::vector<TP> & PosTP, unsigned NbTP, std::vector<CPosition> & VectorMap);

void Genere_Piege(CMat & Mat, unsigned NbLine, unsigned NbColumn, std::vector<CPosition> & VectorPiege, unsigned NbPiege, std::vector<CPosition> & VectorMap);

/*!
 * \brief Initialization of the Matrix from scratch
 * \param[out] Mat the matrix to be initialized
 * \param[in] Parms Set of game's parameters
 * \param[out] PosPlayer1 position of the first player's token in Mat
 * \param[out] PosPlayer2 position of the second player's token in Mat
 * @fn void InitGrid (CMat & Mat, const CMyParam & Params, CPosition & PosPlayer1, CPosition & PosPlayer2);
 */


void InitGrid (CMat & Mat, CMyParam & Param, CPosition & PosPlayer1, CPosition & PosPlayer2,
              std::vector<TP> & VectorTP, unsigned NbTP, std::vector<char> & NomTP, std::vector<CPosition> & VectorMur,
              std::vector<CPosition> & VectorPiege, unsigned NbPiege, std::vector<CPosition> & VectorMap, unsigned Typepart);

#endif // GRIDMANAGEMENT_H
