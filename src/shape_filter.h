#pragma once
#include "shape.h"
#include "filter.h"
#include <list>

typedef bool (*FilterFunction)(Shape *);
class ShapeFilter : public Filter {
public:
    ShapeFilter(FilterFunction pred): _pred(pred) {}
        // Predicate is a template name for lambda,
        //  you may use your own name.
    Filter* setNext(Filter* filter) {
        // seeting next filter.
        _next = filter;
        return _next;
    }

    std::list<Shape*> push(std::list<Shape*> shapes) {
        // push down filtered data and return result.
      std::list<Shape *> _shapes = {};
      for(std::list<Shape *>::iterator it= shapes.begin(); it != shapes.end(); it++){
        if(_pred(*it)){
          // std::cout << "pass: " << (*it)->id() <<std::endl;
          _shapes.push_back((*it));
        }
      }

      if(_next){
        // std::cout<< "get next" << std::endl;
        return _next->push(_shapes);
      }
      // std::cout << _shapes.size() << std::endl;
      return _shapes;
      // for(auto i: _shapes){
      //   std::cout << i->area() << std::endl;
      // }
  }

private:
  FilterFunction _pred;
  Filter * _next = nullptr;
};