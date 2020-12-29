#pragma once
#include "filter.h"
#include "shape.h"
#include <list>

typedef bool (*FilterFunction)(Shape *);

class ShapeFilter : public Filter{
public:
    ShapeFilter(FilterFunction f):_f(f) {

    }

    Filter* setNext(Filter* filter) {
        _next = filter;
        return _next;
    }

    std::list<Shape*> push(std::list<Shape*> shapes) {
        std::list<Shape*> filtered = {};
        for(std::list<Shape*>::iterator it = shapes.begin(); it != shapes.end(); it++){
            if(_f(*it)){
                filtered.push_back(*it);
            }
        }
        if(_next){
            // return this->_next->push(filtered);
            return _next->push(filtered);
        }
        return filtered;
    }
private:
    FilterFunction _f;
    Filter * _next = nullptr;
    // std::list<Shape*> filtered = {};
};