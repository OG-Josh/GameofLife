/*
 * Board.cpp
 *
 *  
 */

#include <iostream>
#include "Board.h"
using namespace std;

Board::Board(int height, int width, int gameMode, float initDensity) {
  if (height < 1)
    throw runtime_error("The Height can't be less than 1.");
  if (width < 1)
    throw runtime_error("The width can't be less than 1.");
  if (initDensity <= 0 || initDensity > 1)
    throw runtime_error(
        "The initial density must be greater than 0 and less then or equal to 1.");
  if (gameMode < 1 || gameMode > 3)
    throw runtime_error("The game mode must be 1, 2, or 3.");

  heightBoard = height;
  widthBoard = width;
  this->gameMode = gameMode;

  InitializeGridRandomly(initDensity);
}

Board::Board(string fileName, int gameMode) {
  if (gameMode < 1 || gameMode > 3)
    throw runtime_error("The game mode must be 1, 2, or 3.");

  this->gameMode = gameMode;

  FileHandler reader(fileName);

  heightBoard = reader.getHeight();
  widthBoard = reader.getWidth();

  this->totalCells = reader.getStartPop();

  vector<Point> positions = reader.getPositions();
  InitializeGrid(positions, totalCells);
}

Board::Board(int height, int width, int gameMode, vector<Point>& startingPos,
             int startingPop) {
  if (height < 1)
    throw runtime_error("The Height can't be less than 1.");
  if (width < 1)
    throw runtime_error("The width can't be less than 1.");
  if (startingPop < 0)
    throw runtime_error(
        "The starting population must be greater than or equal to 0.");
  if (gameMode < 1 || gameMode > 3)
    throw runtime_error("The game mode must be 1, 2, or 3.");

  heightBoard = height;
  widthBoard = width;
  this->gameMode = gameMode;

  InitializeGrid(startingPos, startingPop);
}

Board::~Board() {
}

int Board::RandomizeStartPositions(float initDensity,
                                   vector<Point> &startCoords) {
  int totalSpots = heightBoard * widthBoard;
  int startPop = totalSpots * initDensity;
  startCoords.resize(startPop);
  for (int i = 0; i < startPop;) {
    int randX = rand() % (heightBoard);
    int randY = rand() % (widthBoard);
    bool isFree = false;
    for (int index = 0; index < startPop; ++index) {
      //if those x and y coordinates are already taken, then break
      if (startCoords[i].getX() == randX && startCoords[i].getY() == randY) {
        isFree = false;
        break;
      } else {
        isFree = true;
      }
    }

    //Set point
    if (isFree == true) {
      startCoords[i].setX(randX);
      startCoords[i].setY(randY);
      ++i;
    }
  }

  return startPop;
}

void Board::InitializeGridRandomly(float initDensity) {
  vector<Point> starterPos;
  int startPop = RandomizeStartPositions(initDensity, starterPos);
  InitializeGrid(starterPos, startPop);
}

void Board::InitializeGrid(vector<Point>& startCoords, int startPop) {
  this->totalCells = startPop;
  grid.resize(heightBoard);
  //create the inner arrays
  for (int row = 0; row < heightBoard; ++row) {
    grid[row].resize(widthBoard);
    for (int col = 0; col < widthBoard; ++col) {
      //initialize the cells
      grid[row][col].setCordinates(Point(row, col));
      grid[row][col].setGameMode(this->gameMode);
      grid[row][col].setIsEmpty(true);
      grid[row][col].setHeight(heightBoard);
      grid[row][col].setWidth(widthBoard);
    }
  }
  for (int i = 0; i < startPop; ++i) {
    int x = startCoords[i].getX();
    int y = startCoords[i].getY();
    grid[x][y].setCordinates(Point(x, y));
    grid[x][y].setIsEmpty(false);
    grid[x][y].setGameMode(this->gameMode);
  }
}

bool Board::IsPositionEmpty(int xCor, int yCor) {
  return grid[xCor][yCor].checkEmpty();
}

//this function simply prints the whole board
string Board::PrintGrid() {
  string outputStr = "";
  for (int row = 0; row < heightBoard; ++row) {
    for (int col = 0; col < widthBoard; ++col) {
      outputStr += grid[row][col].GetSymbol() + " ";
    }
    outputStr += "\n";
  }
  return outputStr;
}

vector<Point> Board::GetNextGeneration() {
  int numberNext = GetNextGenerationPopulation();
  vector<Point> nextStarterPos(numberNext);
  int cellCounter = 0;
  for (int row = 0; row < heightBoard; ++row) {
    for (int col = 0; col < widthBoard; ++col) {
      int numberNeighbors = grid[row][col].NumNeighbors(grid, heightBoard,
                                                        widthBoard);
      if (numberNeighbors == 2 && grid[row][col].checkEmpty() == false) {
        nextStarterPos[cellCounter].setX(row);
        nextStarterPos[cellCounter].setY(col);
        ++cellCounter;
      }

      else if (numberNeighbors == 3) {
        nextStarterPos[cellCounter].setX(row);
        nextStarterPos[cellCounter].setY(col);
        ++cellCounter;
      }
    }
  }

  return nextStarterPos;
}


bool Board::isCellEmpty(int x, int y)
{
  return grid[x][y].checkEmpty();
}

int Board::GetNextGenerationPopulation() {
  int numberNext = 0;
  for (int row = 0; row < heightBoard; ++row) {
    for (int col = 0; col < widthBoard; ++col) {
      int numberNeighbors = grid[row][col].NumNeighbors(grid, heightBoard,
                                                        widthBoard);
      if (numberNeighbors == 2 && grid[row][col].checkEmpty() == false)
        ++numberNext;
      else if (numberNeighbors == 3)
        ++numberNext;
    }
  }

  return numberNext;
}

int Board::getTotalCells() {
  return totalCells;
}
void Board::setTotalCells(int cells) {
  totalCells = cells;
}
int Board::getGameMode() {
  return gameMode;
}
void Board::setGameMode(int mode) {
  gameMode = mode;
}

int Board::getHeightBoard() {
  return heightBoard;
}

void Board::setHeightBoard(int h) {
  heightBoard = h;
}

int Board::getWidthBoard() {
  return widthBoard;
}
void Board::setWidthBoard(int w) {
  widthBoard = w;
}
