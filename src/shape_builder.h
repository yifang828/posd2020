#ifndef SHAPE_BUILDER_H
#define SHAPE_BUILDER_H
#include "shape.h"
#include "triangle.h"
#include "rectangle.h"
#include "ellipse.h"
#include "compound_shape.h"
#include <stack>
#include <deque>
#include <vector>
#include <list>
#include <string>

class ShapeBuilder{
public:
    ShapeBuilder(){}

    void buildRectangle(double length, double width){
        Shape * rectangle = new Rectangle(std::to_string(_pushdown.size()), length, width);
        _pushdown.push(rectangle);
    }

    void buildTriangle(double x1, double y1, double x2, double y2, double x3, double y3){
        std::vector<TwoDimensionalCoordinate *> triangleVector;
        triangleVector.push_back(new TwoDimensionalCoordinate(x1, y1));
        triangleVector.push_back(new TwoDimensionalCoordinate(x2, y2));
        triangleVector.push_back(new TwoDimensionalCoordinate(x3, y3));
        Shape * triangle= new Triangle(std::to_string(_pushdown.size()),triangleVector);
        _pushdown.push(triangle);
    }

    void buildEllipse(double semiMajorAxes, double semiMinorAxes){
        Shape * ellipse = new Ellipse(std::to_string(_pushdown.size()), semiMajorAxes, semiMinorAxes);
        _pushdown.push(ellipse);
    }

    void buildCompoundShapeBegin(){
        std::list<Shape*> shapes;
        Shape * cs = new CompoundShape(std::to_string(_pushdown.size()), shapes);
        _pushdown.push(cs);
        _state.push(false);
    }

    void buildCompoundShapeEnd(){
        std::deque<Shape*> deque;
        while (!dynamic_cast<CompoundShape*>(_pushdown.top()) || (dynamic_cast<CompoundShape*>(_pushdown.top()) && \
            _state.top())){
            deque.push_front(_pushdown.top());
            _pushdown.pop();
            if(dynamic_cast<CompoundShape*>(_pushdown.top())&&_state.top()){
                _state.pop();
            }
        }
        for(std::deque<Shape*>::iterator itr = deque.begin(); itr != deque.end(); itr++){
            _pushdown.top()->addShape(*itr);
        }
        _state.top()=true;
        
    }

    std::deque<Shape *> getResult(){
        std::deque<Shape *> result;
        while (!_pushdown.empty())
        {
            result.push_back(_pushdown.top());
            _pushdown.pop();
        }
        return std::deque<Shape*>(result.rbegin(), result.rend());
    }

private:
    std::stack<Shape *> _pushdown;
    // std::stack<Shape *> _emptyCS;
    std::stack<bool> _state;
};
#endif