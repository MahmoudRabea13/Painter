#include "shape.h"
#include "line.h"
#include<iostream>
using namespace std;
line::line(){
}

void line::setLength (double l){length = l;}
double line::getLength(){
return length;
}
double line::perimeter (){
p = length;
return p;
}
double line::area(){
    return 0;
}
void line::setTitle(string s){
    title = s;
}
string line::getTitle(){
    return title;
}
