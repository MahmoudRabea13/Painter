#include "shape.h"
#include "circle.h"
#include<iostream>
using namespace std;
circle::circle(){

}
void circle::setRadius(double rad){
radius = rad;
}
double circle::getRadius(){
return radius;
}
double circle::area() {
  double a = M_PI * (radius*radius);
  return a;
}
double circle::perimeter () {
  double p = 2* M_PI * radius ;
  return p;
}
void circle::setTitle(string s){
    title = s;
}
string circle::getTitle(){
    return title;
}
