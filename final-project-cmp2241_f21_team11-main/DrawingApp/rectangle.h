#include "shape.h"
#ifndef RECTANGLE_H
#define RECTANGLE_H
class rectangle : public shape {
private:
double length, width;
public:
rectangle();
double getLength();
void setLength(double L);
double getWidth();
void setWidth(double w);
double area();
double perimeter ();
void setTitle(string s);
string getTitle();

};

#endif // RECTANGLE_H
