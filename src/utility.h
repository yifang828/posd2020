#include "shape.h"
#include <deque>

Shape * getShapeById(Shape* shape, std::string id){
    Iterator* itr = shape->createIterator();
    if(itr->isDone()){
        throw (std::string) "Only compound shape can get shape!";
    }
    for(itr->first(); !itr->isDone(); itr->next()){
        Shape* s = itr->currentItem();
        if(s->id()==id){
            return s;
        }
        Iterator* innerItr = s->createIterator();
        if(!innerItr->isDone()){
            //!!
            Shape* result = getShapeById(s, id);
            if(result)
                return result;
        }
    }
    if(itr->isDone()){
        throw (std::string) "Expected get shape but shape not found";
    }
    return nullptr;
}

template<class Filter>
std::deque<Shape*> filterShape(Shape* shape, Filter filter){
    Iterator* itr = shape->createIterator();
    if(itr->isDone()){
        throw(std::string)"Only compound shape can filter shape!";
    }
    std::deque<Shape*> result = {};
    for(itr->first(); !itr->isDone(); itr->next()){
        Shape * s = itr->currentItem();
        std::deque<Shape*> recurResult;
        if(filter(s)){
            result.push_back(s);
        }
        Iterator * innerItr = s->createIterator();
        if(!innerItr->isDone()){
            std::deque<Shape*> r_s =filterShape(s, filter);
            if(r_s.size()!=0){
                for(std::deque<Shape*>::iterator i = r_s.begin(); i!= r_s.end(); ++i){
                    result.push_back((*i));
                }
            }
            return result;
            // filterInnerShape(innerItr, filter, &result);
        }
    }
    return result;
}

// template<class Filter>
// void filterInnerShape(Iterator * itr, Filter filter, std::deque<Shape*> *result){
//     for(itr->first(); !itr->isDone(); itr->next()){
//         Shape * s = itr->currentItem();
//         if(filter(s)){
//             result->push_back(s);
//         }
//         Iterator * innerItr = s->createIterator();
//         if(!innerItr->isDone()){
//             filterInnerShape(innerItr, filter, result);
//         }
//     }
// }

class AreaFilter {
public:
    AreaFilter(double upperBound, double lowerBound):_upperBound(upperBound), _lowerBound(lowerBound){}
    bool operator()(Shape* shape) const {
        return (shape->area() <= _upperBound && shape->area() >= _lowerBound);
    }
private:
    double _upperBound=0.0, _lowerBound=0.0;
};

class PerimeterFilter{
public:
    PerimeterFilter(double upperBound, double lowerBound):_upperBound(upperBound), _lowerBound(lowerBound){}
    bool operator()(Shape* shape) const {
        return (shape->perimeter() <= _upperBound && shape->perimeter() >= _lowerBound);
    }
private:
    double _upperBound=0.0, _lowerBound=0.0;
};

class ColorFilter{
public:
    ColorFilter(std::string color):_color(color){}
    bool operator()(Shape* shape) const{
        return (shape->color() == _color);
    }
private:
    std::string _color;
};

class TypeFilter{
public:
    TypeFilter(std::string t):_t(t){}
    bool operator()(Shape* shape)const{
        return (shape->type() == _t);
    }
private:
    std::string _t;
};