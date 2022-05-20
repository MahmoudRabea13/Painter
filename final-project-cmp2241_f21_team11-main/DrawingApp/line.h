#include "shape.h"
#ifndef LINE_H
#define LINE_H
class line : public shape{
private:
double length;
public:
line();

void setLength (double l);
double getLength();
double perimeter ();
double area();
void setTitle(string s);
string getTitle();
};
#endif // LINE_H
