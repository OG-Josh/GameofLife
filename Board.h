/*
 * Board.h
 *
 *  
 */

#ifndef BOARD_H_
#define BOARD_H_

#include "Cell.h"
#include "FileHandler.h"

class Board
{
public:
    //consider taking out the gameMode?
    Board(int height, int width, int gameMode, float initDensity);
    Board(int height, int width, int gameMode, vector<Point> &startingPos, int startingPop);
    Board(string fileName, int gameMode);
    ~Board();

    string PrintGrid();
    vector<Point> GetNextGeneration();
    int GetNextGenerationPopulation();
    bool isCellEmpty(int x, int y);
    // Getter/Setter
    int getTotalCells();
    void setTotalCells(int cells);
    int getGameMode();
    void setGameMode(int mode);
    int getHeightBoard();
    void setHeightBoard(int h);
    int getWidthBoard();
    void setWidthBoard(int w);

private:
    vector<vector<Cell>> grid;
    int heightBoard;
    int widthBoard;
    int gameMode;
    int totalCells;
    //functions
    int RandomizeStartPositions(float initDensity, vector<Point> &startCoords);
    void InitializeGridRandomly(float initDensity);
    bool IsPositionEmpty(int xCor, int yCor);
    void InitializeGrid(vector<Point>& startCoords, int startPop);
};


#endif /* BOARD_H_ */
