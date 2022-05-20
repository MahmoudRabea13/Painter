#ifndef SHAPE_H
#define SHAPE_H
#include<iostream>
#include <QGraphicsItem>
using namespace std;
class shape{
  public:
string title;
double a, p;
virtual double area()=0;
virtual double perimeter()=0;

};
#endif
