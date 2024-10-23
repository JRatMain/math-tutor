#include "mathTutor.h" //including header file for functions
#include <cstdlib>   // endl
#include <iostream>  //cin, cout
#include <stdexcept> //exceptions
#include <string> //strings
#include <vector> // storing vectors containing questions the user answers

using namespace std;
//This file contains the main Math Tutor function, which loops until the user quits the program
const vector<char> OPERATORS = {'+', '-', 'x', '/'};

const string FILENAME = "mathTutor.txt";
/*
	This function continually loops in a try/catch block, until either a runtime error is encountered, or the user exits the application.
Programmed by Matthew Vrbka on 12/13/22
	*/
int main() {
  string enter = "";

  int userChoice;
  int rightAns;
  int numberOne;
  int numberTwo;
  int numAttempts = 0;
  vector<vector<int>> questions;

  DisplayHeader();

  try {
	  
    WelcomeUser();
	  
    while (true) {
		
      srand(time(0));
		
      DisplayMenu();
		
      userChoice = GetUserChoice();
		
      if (userChoice >= 1 && userChoice <= 4) {
		  
        AskMathQuestion(userChoice, questions);
		  
      }

      else if (userChoice == 5) {
		  
        ShowStatusReport(questions);
		  
      } else if (userChoice == 6) {
		  
        SaveGame(questions);
		  
      } else if (userChoice == 7) {
		  
        LoadGame(questions);
      } 
	  else if (userChoice == 8) {
		  showVersion();
	  } else if (userChoice == 0) {
		  
        cout << "Goodbye!" << endl;
		  
        break;
		  
      } else {
		  
        cout << "Invalid input. Please try again." << endl;
		  
      }
      getline(cin, enter); // clears input buffer
		
      cout << endl;
		
      cout << "Press Enter to continue...";
		
      getline(cin, enter); // waits for user to press enter key
		
      cout << endl;
		
    }
  } catch (runtime_error &excpt) {
	  
    cout << excpt.what() << endl;
	  
    cout << "An error has occurred. Please try again.";
	  
    return -2;
	  
  }
	
  return 0;
}
