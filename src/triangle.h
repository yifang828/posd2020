#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "shape.h"
#include "two_dimensional_coordinate.h"
#include <iomanip>

class Triangle: public Shape{
public:
  Triangle(std::string id, std::vector<TwoDimensionalCoordinate*> vectors):Shape(id){
      _vectors = vectors;
      _edges = getEdges(_vectors);
      if(!isTriangle(_edges))
        throw triangleErrMsg;
  }
  Triangle(std::string id, std::vector<TwoDimensionalCoordinate*> vectors, std::string color):Shape(id, color){
      _vectors = vectors;
      _edges = getEdges(_vectors);
      if(!isTriangle(_edges))
        throw triangleErrMsg;
  }
  double area() const{
      double s = 0.5*perimeter();
      double a = _edges[0];
      double b = _edges[1];
      double c = _edges[2];
      double area = sqrt(s*(s-a)*(s-b)*(s-c));
      return round(area, 3);
  }

  double perimeter() const{
     double perimeter = 0.0;
     for(auto x: _edges){
         perimeter += x;
     }
     return round(perimeter, 3);
  }

  std::string info() const{
      std::stringstream x1;
      std::stringstream y1;
      std::stringstream x2;
      std::stringstream y2;
      std::stringstream x3;
      std::stringstream y3;

      x1 << std::fixed << std::setprecision(3) << _vectors[0] -> getX();
      y1 << std::fixed << std::setprecision(3) << _vectors[0] -> getY();
      x2 << std::fixed << std::setprecision(3) << _vectors[1] -> getX();
      y2 << std::fixed << std::setprecision(3) << _vectors[1] -> getY();
      x3 << std::fixed << std::setprecision(3) << _vectors[2] -> getX();
      y3 << std::fixed << std::setprecision(3) << _vectors[2] -> getY();
      
      return "Triangle (["+x1.str()+", "+y1.str()+"], ["+x2.str()+", "+y2.str()+"], ["+x3.str()+", "+y3.str()+"])";
  }

  std::string type() const{
    return "Triangle";
  }

  void accept(Visitor *v){
      v->visit(this);
  }
  
  std::vector<double> getEdges(std::vector<TwoDimensionalCoordinate*> v) {
      std::vector<double> e;
      for(int i = 0; i < v.size()-1; i++){
          for(int j = 1; j < v.size(); j++){
              if(i >= j)
                continue;
              e.push_back(calculateEdge(v[i], v[j]));
          }
      }
      return e;
  }

  std::vector<TwoDimensionalCoordinate*> getVectors(){
    return _vectors;
  }

private:
  std::vector<TwoDimensionalCoordinate*> _vectors;
  std::vector<double> _edges;
  const std::string triangleErrMsg = "This is not a triangle!";

  double calculateEdge(TwoDimensionalCoordinate* point1, TwoDimensionalCoordinate* point2) const{
      double x1 = point1 -> getX();
      double x2 = point2 -> getX();
      double y1 = point1 -> getY();
      double y2 = point2 -> getY();

      return sqrt((x1-x2)*(x1-x2) + (y1-y2)*(y1-y2));
  }

  double round(double x, int n) const{
      return floor(x*pow(10, n)+0.5)/pow(10, 3);
  }

  bool isTriangle(std::vector<double> edges){
      bool result = false;
      if(edges[0] + edges[1] > edges[2] && edges[0] + edges[2] > edges[1] && edges[1] + edges[2] > edges[0])
        result = true;
      if (edges.size()>3){
        result = false;
      }
      return result;
  }
};
#endif