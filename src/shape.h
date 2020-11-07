#ifndef SHAPE_H
#define SHAPE_H
#include <string>
#include "iterator.h"
#include "visitor.h"

class Shape{
    public:
        Shape(std::string id); 
        Shape(std::string id, std::string color); 
        std::string id() const; 
        std::string color() const; 
        virtual double area()const = 0;
        virtual double perimeter()const = 0;
        virtual std::string info() const = 0;
        virtual std::string type() const = 0;//hw5
        virtual void accept(Visitor* visitor) = 0;
        virtual void addShape(Shape *shape); 
        virtual void deleteShapeById(std::string id); 
        virtual Shape* getShapeById(std::string id) const; 
        virtual Iterator * createIterator() const;//hw5
        virtual ~Shape(){};
    private:
        std::string _id, _color;
};

#endif