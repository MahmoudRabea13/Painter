#include"shape.h"
#include <cmath>
#ifndef CIRCLE_H
#define CIRCLE_H
class circle :public shape{
private:
double radius;
public:
circle();
void setRadius(double rad);
double getRadius();
double area();
double perimeter();
void setTitle(string s);
string getTitle();

};

#endif // CIRCLE_H
