#pragma once
#include "shape.h"
#include <list>

class Filter {
public:
    virtual Filter* setNext(Filter* filter) = 0;
    virtual std::list<Shape*> push(std::list<Shape*> shapes) = 0;
};