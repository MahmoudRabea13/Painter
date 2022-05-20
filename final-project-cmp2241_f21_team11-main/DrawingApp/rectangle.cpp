#include"shape.h"
#include "rectangle.h"
#include<iostream>
using namespace std;
rectangle::rectangle(){

}

double rectangle::getLength(){return length;}
void rectangle::setLength(double L){
length =L;
}
double rectangle::getWidth(){return width;}

void rectangle::setWidth(double w){width=w;}

double rectangle::area(){a = length * width;
return a;}

double rectangle::perimeter () {
p = 2* (length+width);
return p;
}
void rectangle::setTitle(string s){
    title = s;
}
string rectangle::getTitle(){
    return title;
}
