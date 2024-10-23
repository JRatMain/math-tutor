#include <vector>

#ifndef MATHTUTOR_H
#define MATHTUTOR_H
using namespace std; 
/*
	This file contains function prototypes to link main.cpp and mathTutor.cpp
	Programmed by Matthew Vrbka on 12/13/22
	*/
void DisplayHeader ();

void DisplayMenu();

void WelcomeUser();

int GetUserChoice();

int GetAns (int correctAns, int& numAttempts);

void AskMathQuestion(int userChoice, vector<vector<int>>& questions);

void ShowStatusReport(vector<vector<int>> questions);

void SaveGame(const vector<vector<int>>& questions);

void LoadGame(vector<vector<int>>& questions);

void showVersion();


#endif