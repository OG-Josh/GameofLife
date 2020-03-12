/*
 * Point.cpp
 *
 *  
 */

#include "Point.h"

Point::Point(int x, int y) {
  xCoordinate = x;
  yCoordinate = y;
}

int Point::getX() {
  return xCoordinate;
}

void Point::setX(int x) {
  xCoordinate = x;
}

int Point::getY() {
  return yCoordinate;
}

void Point::setY(int y) {
  yCoordinate = y;
}
