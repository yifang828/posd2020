#ifndef SHAPE_ITERATOR_H
#define SHAPE_ITERATOR_H

#include "shape.h"
#include "iterator.h"

template<class ForwardIterator>
class ShapeIterator: public Iterator{
public:
    ShapeIterator(ForwardIterator begin, ForwardIterator end){
        _begin = begin;
        _end = end;
        first();
    }
    void first(){
        _current = _begin;
    }
    void next(){
        if(isDone()){
            throw(std::string)"Moving past the end!";
        }else{
            _current ++;
        }
    }
    bool isDone() const {
        return _current == _end;
    }
    Shape * currentItem() const{
        return * _current;
    }

private:
    ForwardIterator _begin, _end, _current;
};
#endif