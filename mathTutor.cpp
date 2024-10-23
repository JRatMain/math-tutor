/*
This file contains the functions for the main math tutor program.
        */
#include "mathTutor.h" //including header to allow linking
#include <ctime>       // srand(time())
#include <fstream>     //file input/output
#include <iomanip>     //setw
#include <iostream>    //cin, cout
#include <limits>      //numeric_limits
#include <stdexcept>   // exceptions, throw
#include <string>      // strings
#include <vector>      // vectors, especially for storing questions

using namespace std;

vector<vector<int>> questions;

const string FILENAME = "mathTutor.txt";
/*
This function displays the Math Tutor header.
*/
void DisplayHeader() {
  cout << "o-----------------------------o" << endl;
  cout << "|         Math Tutor          |" << endl;
  cout << "o-----------------------------o" << endl;
  cout << endl;
}
/*
This function displays the list of options available to the user.
Programmed by Matthew Vrbka on 12/3/22
*/
void DisplayMenu() {
  cout << "Please select an option from the following menu. " << endl;
  cout << "Available options:" << endl;
  cout << "==================" << endl;
  cout << "1 = (+) Addition" << endl;
  cout << "2 = (-) Subtraction" << endl;
  cout << "3 = (*) Multiplication" << endl;
  cout << "4 = (/) Division" << endl;
  cout << "==================" << endl;
  cout << "5 = Display Status Report" << endl;
  cout << "6 = Save" << endl;
  cout << "7 = Load Previous Save" << endl;
  cout << "8 = C++ Version Information" << endl;
  cout << "==================" << endl;
  cout << "0 = Quit" << endl;
}

// displays the C++ standard used.
void showVersion() {
	if (__cplusplus == 199711L) {
		cout << "Using C++98/03 standard" << endl;
	} else if (__cplusplus == 201103L) {
		cout << "Using C++11 standard" << endl;
	} else if (__cplusplus == 201402L) {
		cout << "Using C++14 standard" << endl;
	} else if (__cplusplus == 201703L) {
		cout << "Using C++17 standard" << endl;
	} else if (__cplusplus == 202002L) {
		cout << "Using C++20 standard" << endl;
	} else {
		cout << "Using an unknown C++ standard" << endl;
	}
}

/*
This function acquires the user's name and greets them before returning to main
and displaying the main menu
Programmed by Matthew Vrbka on 12/3/22
*/
void WelcomeUser() {
  string userName;
  cout << "Please enter your name:"
       << endl; // prompts the user to enter their name

  // gets the user's name
  getline(cin, userName);

  cout << endl; // ending the line to prevent a long block of text
  cout << "It's a pleasure to meet you, " << userName
       << ". In this game, you will have 3 attempts to answer math questions."
       << endl; // welcomes the user by name and explains the rules
}
/*
This function returns the user's choice from the options they were given in the
main menu.
Programmed by Matthew Vrbka on 12/2/22
*/
int GetUserChoice() {
  int userMenuChoice;

  while (!(cin >> userMenuChoice)) {
    cin.clear(); // clears error from cin
    cin.ignore(numeric_limits<streamsize>::max(), '/n');
    cout << "Invalid input. Please enter a number: ";
  }

  return userMenuChoice;
}
/*
This function gets the user's answer to the math question.
Programmed by Matthew Vrbka on 12/13/2022.
*/
int GetAns(int correctAns, int &numAttempts) {
  int userAns;
  const int MAX_TRIES = 3;

  for (int i = 1; i <= MAX_TRIES; ++i) {
    while (!(cin >> userAns)) {
      cin.clear(); // clears error from cin
      cin.ignore(numeric_limits<streamsize>::max(), '/n');
      cout << "Invalid input. Please enter a number: ";
    }

    if (userAns == correctAns) {
      cout << "Correct! :)" << endl;
      numAttempts = i;
      return 1;
    } else if (userAns != correctAns) {
      cout << "Oops! Try again!" << endl;
      numAttempts = i;
      continue;
    }
  }
  cout << "Oops! the correct answer was: " << correctAns << ".";
  numAttempts = 0;
  return 0;
}
/*
This function generates and displays a math question for the user to answer.
After it is generated, the user answers the question and information about the
question is stored in a vector, including the amount of attempts it took the
user to answer it.
Programmed by Matthew Vrbka on 12/13/2022.
*/
void AskMathQuestion(int userChoice, vector<vector<int>> &questions) {

  int numberOne;
  int numberTwo;
  char operationStr;
  int rightAns;
  int numAttempts = 0;
  bool result;

  numberOne = (rand() % 10 + 1); // generates random number for left equation
  numberTwo = (rand() % 10 + 1); // generates second random number

  switch (userChoice - 1) {
  case 0: // add
    operationStr = '+';
    rightAns = numberOne + numberTwo;
    break;

  case 1: // subtract
    operationStr = '-';
    rightAns = numberOne - numberTwo;
    break;

  case 2: // multiply
    operationStr = 'x';
    rightAns = numberOne * numberTwo;
    break;

  case 3: // divide,
    operationStr = '/';
    rightAns =
        numberOne; // rightAns becomes numberOne to prevent decimal answers
    numberOne =
        numberOne *
        numberTwo; // numberOne is multiplied by numberTwo after numberOne's
                   // value is added to rightAns; this allows for the problem
                   // to be completed without using a decimal
    break;

  default:
    cout << "Error: Invalid operation number! Returned " << userChoice
         << " but expected integers 0-3!" << '/n';
    throw runtime_error("Invalid operation number.");
  }
  cout << numberOne << " " << operationStr << " " << numberTwo << " = ";
  const vector<char> OPERATORS = {'+', '-', 'x', '/'};
  vector<int> row;
  row.push_back(numberOne);
  row.push_back(userChoice - 1);
  row.push_back(numberTwo);
  result = GetAns(rightAns, numAttempts);
  row.push_back(rightAns);
  row.push_back(numAttempts);

  /*
  The full order of the vector "row" is the left number, the operation number,
  the right number, the correct answer, and the amount of attempts for each
  question.

          */
  questions.push_back(row);
}
/*
This function displays the status report for the user, showing them information
such as the amount of questions, each math problem, the amount of attempts, and
the percentage of questions answered correctly.
Programmed by Matthew Vrbka on 12/13/2022.
        */
void ShowStatusReport(vector<vector<int>> questions) {
  int numberOne;
  int numberTwo;
  int operationNum;
  int numAttempts;
  char operationChar;
  int rightAns;
  int amtRightAns = 0;
  int numQuestions = questions.size();
  int percentageRight = 0;

  if (questions.size() == 0) {
    cout << "No questions to display." << endl;
  }
  cout << "===========================" << endl;
  cout << " Math Tutor Detail Report:" << endl;
  cout << "===========================" << endl;
  cout << "Questions:"
       << "    "
       << "Attempts used (0 means incorrect) :" << endl;
  cout << "----------"
       << "    " << setw(3) << "-------------" << endl;

  for (int i = 0; i < questions.size(); ++i) {

    numberOne = questions.at(i).at(0);
    operationNum = questions.at(i).at(1);
    numberTwo = questions.at(i).at(2);
    rightAns = questions.at(i).at(3);
    numAttempts = questions.at(i).at(4);
    if (numAttempts != 0) {
      ++amtRightAns;
    }

    switch (operationNum) {
    case 0: // add
      operationChar = '+';
      rightAns = numberOne + numberTwo;
      break;

    case 1: // subtract
      operationChar = '-';
      rightAns = numberOne - numberTwo;
      break;

    case 2: // multiply
      operationChar = 'x';
      rightAns = numberOne * numberTwo;
      break;

    case 3: // divide
      operationChar = '/';
      rightAns = numberOne / numberTwo;
      break;

    default:
      cout << "Error: Invalid operation number! Program terminated. Returned "
           << operationNum << " but expected integers 0-3!" << '/n';

      throw runtime_error("Invalid operation number.");
    } // end of switch statement

    cout << setw(3) << numberOne << setw(3) << operationChar << left << setw(3)
         << " " << numberTwo << " = " << right << rightAns << " " << numAttempts
         << endl;
  }
  cout << endl;
  cout << "=====================" << endl;
  percentageRight = amtRightAns * 100 / numQuestions;
  cout << "Here's your summary:" << endl;
  cout << setw(4);
  cout << "Amount correct: " << setw(4) << amtRightAns
       << endl; // DEBBIE: use setw(4) to align your numbers
  cout << "Amount incorrect: " << setw(4) << numQuestions - amtRightAns << endl;
  cout << "Total questions: " << setw(4) << numQuestions << endl;
  cout << "Percent correct: " << setw(4) << percentageRight << "%"
       << endl; // DEBBIE: only need one blank line for code logic separation
}
/*
This function saves the information from the "questions" vector in
mathTutor.txt.
Programmed by Matthew Vrbka on 12/13/2022.
        */
void SaveGame(const vector<vector<int>> &questions) {

  cout << "Saving..." << endl;

  if (questions.size() == 0) {
    cout << "No questions to save." << endl;
    return;
  }
  ofstream outFS; // output file stream handle

  outFS.open(FILENAME);

  if (!outFS.is_open()) {
    throw runtime_error(
        "The file is already open for saving! Could not open file.");
  }
  for (int i = 0; i < questions.size(); ++i) {
    outFS << questions.at(i).at(0) << " " << questions.at(i).at(1) << " "
          << questions.at(i).at(2) << " " << questions.at(i).at(3) << " "
          << questions.at(i).at(4) << " ";
  }
  outFS.close(); // closing file after saving
  cout << "Saved " << questions.size() << " question(s) successfully!";
}
/*
This function loads information about previous questions from mathTutor.txt and places them back into the "questions" vector.
Programmed by Matthew Vrbka on 12/13/2022.
	*/
void LoadGame(vector<vector<int>> &questions) {
  int leftNum;
  int rightNum;
  int operationNum;
  int rightAns;
  int numAttempts;

  ifstream inFS; // input stream file handle
  questions.clear();
  cout << "Loading..." << endl;
  inFS.open(FILENAME);

  if (!inFS.is_open()) {
    throw runtime_error("Unable to load file.");
  }
  while (inFS >> leftNum >> operationNum >> rightNum >> rightAns >>
         numAttempts) {
    questions.push_back(
        {leftNum, operationNum, rightNum, rightAns, numAttempts});
  }
  if (!inFS.eof()) {
    throw runtime_error("Something went wrong while reading the file.");
  }
  inFS.close(); // closing file after loading
  cout << "Game loaded " << questions.size() << " questions successfully!"
       << endl;
}
