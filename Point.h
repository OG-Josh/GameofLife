/*
 * Point.h
 *
 *  
 */
#ifndef POINT_H_
#define POINT_H_

class Point {
 public:
  Point(int x = 0, int y = 0);
  //Getter/Setter
  int getX();
  void setX(int x);
  int getY();
  void setY(int y);
 private:
  int xCoordinate;
  int yCoordinate;
};

#endif /* POINT_H_ */
