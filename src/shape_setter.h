#pragma once
#include "filter.h"
#include "shape.h"
#include <list>

typedef void (*SetterFunction)(Shape *);

class ShapeSetter : public Filter {
public:

    ShapeSetter(SetterFunction f):_f(f) {

    }

    Filter* setNext(Filter* filter) {
        _next = filter;
        return _next;
    }

    std::list<Shape*> push(std::list<Shape*> shapes) {
        for(std::list<Shape*>::iterator it = shapes.begin(); it != shapes.end(); ++it){
                _f(*it);
                filtered.push_back(*it);
        }
        if(_next){
            return _next->push(filtered);
        }
        return filtered;
    }
private:
    SetterFunction _f;
    Filter * _next = nullptr;
    std::list<Shape*> filtered;
};
