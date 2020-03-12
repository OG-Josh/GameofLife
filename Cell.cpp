/*
 * Cell.cpp
 *
 *  
 */
#include <iostream>
#include "Cell.h"

Cell::Cell() {
  isEmpty = true;
}

Cell::Cell(int xCor, int yCor, bool occupied, int gameMode) {
  coordinates.setX(xCor);
  coordinates.setY(yCor);
  isEmpty = occupied;
  this->gameMode = gameMode;
}

Cell::~Cell() {
}

int Cell::NumNeighbors(vector<vector<Cell>> &board, int height, int width) {
  int result = 0;
  //check straight right
  if (IsNeighbor(coordinates.getX() + 1, coordinates.getY(), board)) {
    result++;
  }
  //right and up
  if (IsNeighbor(coordinates.getX() - 1, coordinates.getY(), board)) {
    result++;
  }

  //up
  if (IsNeighbor(coordinates.getX(), coordinates.getY() + 1, board))
    result++;

  //up and left
  if (IsNeighbor(coordinates.getX(), coordinates.getY() - 1, board))
    result++;

  //left
  if (IsNeighbor(coordinates.getX() - 1, coordinates.getY() - 1, board))
    result++;

  //left and down
  if (IsNeighbor(coordinates.getX() + 1, coordinates.getY() + 1, board))
    result++;

  //down
  if (IsNeighbor(coordinates.getX() - 1, coordinates.getY() + 1, board))
    result++;

  //right and down
  if (IsNeighbor(coordinates.getX() + 1, coordinates.getY() - 1, board))
    result++;
  return result;
}

string Cell::GetSymbol() {
  if (isEmpty == true)
    return "-";
  else
    return "X";
}

bool Cell::IsNeighbor(int xCor, int yCor, vector<vector<Cell>> &board) {
  Point coordToCheck(xCor, yCor);
  //classic is 1
  if (gameMode == 1) {
    //if the coord to check is out of bounds, do nothing
    if (coordToCheck.getX() < 0 || coordToCheck.getX() >= boardHeight
        || coordToCheck.getY() < 0 || coordToCheck.getY() >= boardWidth) {
      return false;
    } else if (board[coordToCheck.getX()][coordToCheck.getY()].isEmpty == false)
      return true;
    return false;
  }
  //doughnut mode
  else if (gameMode == 2) {
    if (IsAgainstWall()) {
      if (coordToCheck.getX() < 0)
        coordToCheck.setX(boardHeight - 1);
      if (coordToCheck.getX() >= boardHeight)
        coordToCheck.setX(0);
      if (coordToCheck.getY() < 0)
        coordToCheck.setY(boardWidth - 1);
      if (coordToCheck.getY() >= boardWidth)
        coordToCheck.setY(0);
    }
    if (board[coordToCheck.getX()][coordToCheck.getY()].isEmpty == false)
      return true;
    else
      return false;
  }
  //mirror
  else if (gameMode == 3) {
    if (IsAgainstWall()) {
      if (coordToCheck.getX() < 0)
        coordToCheck.setX(0);
      else if (coordToCheck.getX() >= boardHeight)
        coordToCheck.setX(boardHeight - 1);

      if (coordToCheck.getY() < 0)
        coordToCheck.setY(0);
      else if (coordToCheck.getY() >= boardWidth)
        coordToCheck.setY(boardWidth - 1);
    }
    if (board[coordToCheck.getX()][coordToCheck.getY()].isEmpty == false)
      return true;
    else
      return false;
  }
  return false;
}

bool Cell::IsAgainstWall() {
  if (coordinates.getX() <= 0)
    return true;
  else if (coordinates.getX() >= (boardHeight - 1))
    return true;

  if (coordinates.getY() <= 0)
    return true;
  else if (coordinates.getY() >= (boardWidth - 1))
    return true;

  return false;
}

bool Cell::checkEmpty() {
  return isEmpty;
}

void Cell::setIsEmpty(bool empty) {
  isEmpty = empty;
}

int Cell::getGameMode() {
  return gameMode;
}

void Cell::setGameMode(int mode) {
  gameMode = mode;
}

int Cell::getHeight() {
  return this->boardHeight;
}

void Cell::setHeight(int height) {
  boardHeight = height;
}

int Cell::getWidth() {
  return boardWidth;
}

void Cell::setWidth(int width) {
  boardWidth = width;
}

void Cell::setCordinates(Point coor) {
  coordinates.setX(coor.getX());
  coordinates.setY(coor.getY());
}

Point Cell::getCordinates() {
  return coordinates;
}
