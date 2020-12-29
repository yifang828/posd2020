#ifndef RECTANGLE_H
#define RECTANGLE_H

#define _USE_MATH_DEFINES
#include "shape.h"
#include <string.h>
#include <cmath>
#include <iomanip>

class Rectangle: public Shape {
public:
  Rectangle(std::string id, double length, double width):Shape(id){
    if(length<=0 || width<=0)
        throw rectangleErrorMsg; 
    else
    {
        _length = length;
        _width = width;
    }   
  }
  Rectangle(std::string id, double length, double width, std::string color):Shape(id, color){
    if(length<=0 || width<=0)
        throw rectangleErrorMsg; 
    else
    {
        _length = length;
        _width = width;
    }  
  }

  double area() const{
      return round(_length * _width, 3);
  }
  double perimeter() const{
      return round(_length*2 + _width*2, 3);
  }
  std::string info() const{
      std::stringstream roundedlength;
      roundedlength<<std::fixed<<std::setprecision(3)<<_length;
      std::stringstream roundedwidth;
      roundedwidth<<std::fixed<<std::setprecision(3)<<_width;
      return "Rectangle (" + roundedlength.str() + ", " + roundedwidth.str() + ")";
  }

  std::string type() const{
    return "Rectangle";
  }

  void accept(Visitor *v){
      v->visit(this);
  }

  double getLength() {
    return _length;
  }

  double getWidth() {
    return _width;
  }
  
private:
    double _length, _width;
    const std::string rectangleErrorMsg = "This is not a rectangle!";
    double round(double x, int n) const{
      return floor(x*pow(10, n)+0.5)/pow(10, 3);
  }
};
#endif