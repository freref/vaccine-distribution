//============================================================================
// Name        : TicTacToeUtils.h
// Author      : Serge Demeyer
// Version     :
// Copyright   : Project Software Engineering - BA1 Informatica - Serge Demeyer - University of Antwerp
// Description : TicTactToe in C++, Ansi-style
//============================================================================

// Below are two lines serving as a so-called ``header guard''.
// Prevents from loading the same .h file multiple times
#ifndef PROJECTPSE_FILECOMPARE_H
#define PROJECTPSE_FILECOMPARE_H


#include <iostream>

bool FileIsEmpty(const std::string filename);

bool FileCompare(const std::string leftFileName, const std::string rightFileName);


#endif //PROJECTPSE_FILECOMPARE_H
