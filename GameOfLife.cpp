/*
 * GameOfLife.cpp
 *
 *  
 */

#include <fstream>
#include <iostream>
#include <time.h>
#include <chrono>
#include <thread>
#include "Board.h"

using namespace std::this_thread;
using namespace std::chrono;
// nanoseconds, system_clock, seconds
using namespace std;

bool isRunning(Board*& curGen, Board*& nextGen);

int stabalizedGens = 0;
string prevGenStrings[3];
int main(int argc, char** argv) {
  srand(time(NULL));

  cout << "============THE GAME OF LIFE===================" << endl;
  cout
      << "You want to start game with random configuration or specify a flat file configuration?:"
      << endl;
  cout << "1. Random configuration" << endl;
  cout << "2. a flat file configuration" << endl;
  string answer = "";
  cin >> answer;

  bool isRandom;
  if (answer == "1")
    isRandom = true;
  else if (answer == "2")
    isRandom = false;
  else {
    cout << "Invalid choice. Exiting" << endl;
    return 1;
  }

  int height = 0;
  int width = 0;
  float density = 0;
  string filePath = "";
  if (isRandom) {
    cout << "Enter the board game information:" << endl;
    cout << "Height: ";
    cin >> answer;
    try {
      height = stoi(answer);
    } catch (...) {
      cout << "Invalid input. We need integer number." << endl;
      return 1;
    }

    if (height <= 0) {
      cout << "The Height can't be less than 1." << endl;
      return 1;
    }

    cout << "Width: ";
    cin >> answer;
    try {
      width = stoi(answer);
    } catch (...) {
      cout << "Invalid input. We need integer number." << endl;
      return 1;
    }
    if (width <= 0) {
      cout << "The Width can't be less than 1" << endl;
      return 1;
    }

    cout << "What should the initial population density be? (0 < density <= 1)"
         << endl;
    cin >> answer;
    try {
      density = stof(answer);
    } catch (...) {
      cout << "Invalid input. We need number.\n";
      return 1;
    }
    if (density < 0 || density > 1) {
      cout
          << "That was not a valid density. (Make sure you follow the rules)\n";
      return 1;
    }
    cout << "Game information: " << endl;
    cout << "\t-Height: " << height << endl;
    cout << "\t-Width: " << width << endl;
    cout << "\t-Density: " << density << endl;
  } else {
    cout << "Please enter the filename of configuration: ";
    cin >> filePath;
  }

  cout << "Please choice the game mode:" << endl;
  cout << "\t1. Classic" << endl;
  cout << "\t2. Doughnut" << endl;
  cout << "\t3. Mirror" << endl;
  cin >> answer;
  int gameMode = 0;
  try {
    gameMode = stoi(answer);
    if (gameMode < 1 || gameMode > 3)
      throw runtime_error("Invalid input");
  } catch (...) {
    cout << "Invalid choice. So pick the default game mode CLASSIC" << endl;
    gameMode = 1;
  }

  cout << "Setting:" << endl;
  cout << "\t1. A short pause in between." << endl;
  cout << "\t2. Pressing enter between each generation." << endl;
  cout << "\t3. Just run and then output to a file." << endl;
  int settingMode = 0;
  cin >> answer;
  try {
    settingMode = stoi(answer);

    if (settingMode < 1 || settingMode > 3)
      throw runtime_error("Invalid choice");
  } catch (...) {
    cout << "Choice the default view mode. Press enter between generation\n";
    settingMode = 2;
  }
  //ask for the file
  string outputFileName = "";
  if (settingMode == 3) {
    cout << "Output file: \n";
    cin >> outputFileName;

    try {
      FileHandler::WriteToFile(outputFileName, "Beginning of Simulation.");
    } catch (...) {
      cout << "ERROR!!!!!!";
      return 1;
    }
  }

  Board* curBoard;
  Board* nextGen;
  bool keepRunning = false;

  if (isRandom)
    curBoard = new Board(height, width, gameMode, density);
  else {
    try {
      curBoard = new Board(filePath, gameMode);
    } catch (runtime_error e) {
      cout << "You must enter a valid file name. " << e.what() << endl;
      return 1;
    }
  }

  int currentGenPopulation = curBoard->getTotalCells();
  int nextGenPop = 0;
  cin.get();
  int generationCounter = 0;
  do {
    currentGenPopulation = curBoard->getTotalCells();
    cout << "Generation Number: " << generationCounter << endl;
    if (settingMode == 3) {
      string outStr = "Generation Number: " + to_string(generationCounter);
      FileHandler::WriteToFile(outputFileName, outStr);
      outStr = curBoard->PrintGrid();
      FileHandler::WriteToFile(outputFileName, outStr);
    } else if (settingMode == 2 || settingMode == 1)
      cout << curBoard->PrintGrid() << endl;

    //get the starter coordinates of the next generation
    vector<Point> nextGenStarterPos = curBoard->GetNextGeneration();
    //get the number of occupied cells in the next generation (also the length of the array gathered on the previous line)
    nextGenPop = curBoard->GetNextGenerationPopulation();
    //instantiate the next gameboard with the same dimentions, but the new starter positions
    nextGen = new Board(curBoard->getHeightBoard(), curBoard->getWidthBoard(),
                        gameMode, nextGenStarterPos, nextGenPop);

    if (settingMode == 3) {
      string outStr = "Next Generation Population: " + to_string(nextGenPop);
      FileHandler::WriteToFile(outputFileName, outStr);
    } else if (settingMode == 2 || settingMode == 1)
      cout << "Next Generation Population: " << nextGenPop << endl;

    //place the last couple generation strings into the array
    prevGenStrings[generationCounter % 3] = curBoard->PrintGrid();
    prevGenStrings[(generationCounter + 1) % 3] = nextGen->PrintGrid();

    keepRunning = isRunning(curBoard, nextGen);

    delete curBoard;
    //reassign the variables
    curBoard = nextGen;

    //this is to wait for user input if they select the option to press enter every time
    if (settingMode == 2) {
      cout << "Press ENTER to continue to next generation.\n";
      cin.get();
    }
    //sleep for 2 seconds if the option was selected
    if (settingMode == 1) {
      sleep_for(seconds(2));
    }

    ++generationCounter;
  } while (keepRunning);

  //print the last generation
  if (settingMode == 3) {
    string outStr = "Generation Number: " + to_string(generationCounter);
    FileHandler::WriteToFile(outputFileName, outStr);
    outStr = curBoard->PrintGrid();
    FileHandler::WriteToFile(outputFileName, outStr);
    FileHandler::WriteToFile(outputFileName, "Simulation Finished");
  }
  cout << "Generation Number: " << generationCounter << endl;
  cout << curBoard->PrintGrid() << endl;
  cout << "This is the last generation.\n";
  cout << "Goodbye! :)\n";
}

bool isRunning(Board*& curGen, Board*& nextGen) {
  if (nextGen->getTotalCells() == 0)
    return false;
  bool areGridsEqual = true;
  for (int row = 0; row < curGen->getHeightBoard(); ++row) {
    for (int col = 0; col < curGen->getWidthBoard(); ++col) {
      if (curGen->isCellEmpty(row, col) != nextGen->isCellEmpty(row, col)) {
        areGridsEqual = false;
        break;
      }
    }
    if (areGridsEqual == false)
      break;
  }

  if (areGridsEqual)
    return false;
  if (curGen->getTotalCells() == nextGen->getTotalCells()) {
    stabalizedGens++;
    if (stabalizedGens > 4)
      return false;
  } else
    stabalizedGens = 0;
  for (int i = 0; i < 3; ++i) {
    for (int j = 0; j < 3; ++j) {
      if (i == j)
        continue;
      if (prevGenStrings[i] == prevGenStrings[j])
        return false;
    }
  }

  return true;
}
