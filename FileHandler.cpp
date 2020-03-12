/*
 * FileHandler.cpp
 *
 *  
 */

#include <iostream>
#include <fstream>
#include "FileHandler.h"

FileHandler::FileHandler(string fileName) {
  ReadFile(fileName);
}

void FileHandler::ReadFile(string fileName) {
  ifstream file;
  file.open(fileName);

  if (!file) {
    throw runtime_error("Couldn't open file named " + fileName);
  }

  //count how many lines there are
  string line;
  int lineCount = 0;
  while (getline(file, line)) {
    ++lineCount;
  }
  file.clear();
  file.seekg(0);  //reset the stream to position 0

  //create an array that houses all the lines from the file
  string* fileLines = new string[lineCount];

  //put all the lines into the array
  int counter = 0;
  while (getline(file, line)) {
    fileLines[counter] = line;
    ++counter;
  }
  file.clear();
  file.seekg(0);  //reset the stream to position 0

  file.close();
  try {
    this->height = stoi((string) fileLines[0]);
  } catch (invalid_argument) {
    throw invalid_argument("The height in the file is not a number.");
  }
  try {
    this->width = stoi((string) fileLines[1]);  //parse width.
  } catch (invalid_argument) {
    throw invalid_argument("The width in the file is not a number.");
  }

  //check to make sure that the file follows the correct
  if (this->height != lineCount - 2
      || IsWidthCorrect(fileLines, lineCount, width) == false) {
    throw runtime_error(
        "The file does not follow the correct standard layout.");
  }

  //now read how many cells are in the provided grid
  int totalPop = 0;
  for (int i = 2; i < lineCount; ++i) {
    for (size_t index = 0; index < fileLines[i].length(); ++index) {
      if (fileLines[i][index] == 'X')
        ++totalPop;
    }
  }
  positions.resize(totalPop);
  this->startPop = totalPop;
  //now iterate through the lines recording their positions
  int currentCell = 0;
  for (int row = 2; row < lineCount; ++row) {
    for (size_t col = 0; col < fileLines[row].length(); ++col) {
      if (fileLines[row][col] == 'X') {
        positions[currentCell].setX(row - 2);
        positions[currentCell].setY(col);

        ++currentCell;
        if (currentCell >= totalPop) {
          return;
        }
      }
    }
  }

}

//determines if all the lines in the file are the correct width
bool FileHandler::IsWidthCorrect(string* &fileLines, int lineCount, int width) {
  for (int i = 2; i < lineCount; ++i) {
    if ((int)fileLines[i].length() != width)
      return false;
  }

  return true;
}

/*This is a static function that takes in a file name and a string to write to that file.*/
void FileHandler::WriteToFile(string fileName, string strToWrite) {
  ofstream outFile;

  outFile.open(fileName, ofstream::app);

  if (!outFile)
    throw runtime_error("Cannot open output file.");

  outFile << strToWrite << endl;

  outFile.close();
}

int FileHandler::getHeight() {
  return height;
}

void FileHandler::setHeight(int h) {
  height = h;
}

int FileHandler::getWidth() {
  return width;
}

void FileHandler::setWidth(int w) {
  width = w;
}

int FileHandler::getStartPop() {
  return startPop;
}

void FileHandler::setStartPop(int s) {
  startPop = s;
}

vector<Point> FileHandler::getPositions() {
  return this->positions;
}
void FileHandler::setPositions(vector<Point> p) {
  positions = p;
}
