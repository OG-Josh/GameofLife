/*
 * Cell.h
 *
 *  
 */

#ifndef CELL_H_
#define CELL_H_

#include <string>
#include <vector>
#include "Point.h"
using namespace std;

class Cell {
 public:
  Cell(int xCor, int yCor, bool occupied, int gameMode);
  Cell();
  ~Cell();

  //functions:
  int NumNeighbors(vector<vector<Cell>> &board, int height, int width);
  std::string GetSymbol();

  bool IsNeighbor(int xCor, int yCor, vector<vector<Cell>> &board);
  bool IsAgainstWall();

  // Getter/Setter
  bool checkEmpty();
  void setIsEmpty(bool empty);
  int getGameMode();
  void setGameMode(int mode);

  int getHeight();
  void setHeight(int height);

  int getWidth();
  void setWidth(int width);
  void setCordinates(Point cor);
  Point getCordinates();
 private:
  Point coordinates;
  int boardHeight;
  int boardWidth;
  bool isEmpty;
  int gameMode;
};

#endif /* CELL_H_ */
