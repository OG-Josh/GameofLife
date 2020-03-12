/*
 * FileHandler.h
 *
 *  
 */

#ifndef FILEHANDLER_H_
#define FILEHANDLER_H_

#include <string>
#include <vector>
#include "Point.h"
using namespace std;
class FileHandler {
public:
    FileHandler(string fileName);
    void ReadFile(string fileName);
    bool IsWidthCorrect(string*& fileLines, int lineCount, int width);
    static void WriteToFile(string fileName, string strToWrite);
    // Getter/Setter
    int getHeight();
    void setHeight(int h);
    int getWidth();
    void setWidth(int w);
    int getStartPop();
    void setStartPop(int s);
    vector<Point> getPositions();
    void setPositions(vector<Point> p);

private:
    int height;
    int width;
    int startPop;
    vector<Point> positions;
};

#endif /* FILEHANDLER_H_ */
