#ifndef COMPOUNDSHAPE_H
#define COMPOUNDSHAPE_H
#include <list>
#include "shape.h"
#include "iterator.h"
#include "shape_iterator.h"

class CompoundShape : public Shape {
public:
    CompoundShape(std::string id, std::list<Shape*> shapes):Shape(id, "transparent") {
        _shape = shapes;
    }

    double area() const {
        double result = 0.0;
        for(std::list<Shape *>::const_iterator i = _shape.begin(); i != _shape.end(); ++i){
            result += (*i)->area();
        }
        return result;
    }

    double perimeter() const { 
        double result = 0.0;
        for(std::list<Shape *>::const_iterator i = _shape.begin(); i != _shape.end(); ++i){
            result += (*i)->perimeter();
        }
        return result;
    }

    void addShape(Shape* shape) {
        _shape.push_back(shape);
    }
    
    void deleteShapeById(std::string id) {
        try{
            Shape * shapePtr = getShapeById(id);
            for(std::list<Shape *>::iterator i = _shape.begin(); i != _shape.end(); ++i){
                try{
                    if((*i)->id()==id){
                        _shape.erase(i);
                        break;
                    }
                    else if((*i)->id()!=id){
                        (*i)->deleteShapeById(id);
                    }
                }catch(std::string e){
                }
            }
        }catch(std::string e){
            throw(std::string)"Expected delete shape but shape not found";
        }
    }

    std::string info() const {
        std::string result;
        for(std::list<Shape *>::const_iterator i = _shape.begin(); i != _shape.end(); ++i){
            if(i==_shape.begin()){
                result += (*i) ->info();
            }else{
                result += ", "+ (*i)->info();
            }
        }
        return "Compound Shape {" + result + "}";
    }
    
    std::string type() const{
        return "Compound Shape";
    }
    
    Shape* getShapeById(std::string id) const{
        Shape * result;
        for(std::list<Shape *>::const_iterator i = _shape.begin(); i != _shape.end(); ++i){
            try{
                if((*i)->id()!=id){
                    result = (*i)->getShapeById(id);
                    return result;
                }else{
                    if((*i)->id()==id){
                        return result = (*i);
                    }
                }
            }catch(std::string e){

            }
        }
        throw(std::string)"Expected get shape but shape not found";
    }

    Iterator * createIterator() const {
        return new ShapeIterator<std::list<Shape*>::const_iterator>(_shape.begin(), _shape.end());
    }

    void accept(Visitor *v){
        v->visit(this);
    }

    std::list<Shape*> getShapes(){
        return _shape;
    }

private:
    std::list<Shape*> _shape;
};
#endif