#ifndef ELLIPSE_H
#define ELLIPSE_H

#define _USE_MATH_DEFINES
#include "shape.h"
#include <cmath>
#include <iomanip>

class Ellipse: public Shape {
public:
  Ellipse(std::string id, double semiMajorAxes, double semiMinorAxes):Shape(id){
    if(semiMajorAxes <= 0 || semiMinorAxes <= 0 || semiMajorAxes < semiMinorAxes)
        throw ellipseErrorMsg;
    else{
        _semiMajorAxes = semiMajorAxes;
        _semiMinorAxes = semiMinorAxes;
    }
  }
  Ellipse(std::string id, double semiMajorAxes, double semiMinorAxes, std::string color):Shape(id, color){
    if(semiMajorAxes <= 0 || semiMinorAxes <= 0 || semiMajorAxes < semiMinorAxes)
        throw ellipseErrorMsg;
    else{
        _semiMajorAxes = semiMajorAxes;
        _semiMinorAxes = semiMinorAxes;
    }
  }
  double area() const{
      double result = M_PI * _semiMajorAxes * _semiMinorAxes;
      return round(result, 3);
  }

  double perimeter() const{
      double result = 2*M_PI*_semiMinorAxes+4*(_semiMajorAxes-_semiMinorAxes);
      return result;
  }

  std::string info() const{
      std::stringstream semiMjStream;
      semiMjStream<<std::fixed<<std::setprecision(3)<<_semiMajorAxes;
      std::stringstream semiMnStream;
      semiMnStream<<std::fixed<<std::setprecision(3)<<_semiMinorAxes;
      return "Ellipse ("+ semiMjStream.str() + ", " + semiMnStream.str()+")";
  }
  
  std::string type() const{
    return "Ellipse";
  }

  void accept(Visitor *v){
        v->visit(this);
  }

  double getSemiMajorAxes(){
    return _semiMajorAxes;
  }

  double getSemiMinorAxes(){
    return _semiMinorAxes;
  }
  
private:
  double _semiMajorAxes, _semiMinorAxes;
  const std::string ellipseErrorMsg = "This is not an ellipse!";

  double round(double x, int n) const{
      return floor(x*pow(10, n)+0.5)/pow(10, 3);
  }
};
#endif