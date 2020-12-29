#ifndef INFO_VISITOR_H
#define INFO_VISITOR_H

#include "ellipse.h"
#include "triangle.h"
#include "rectangle.h"
#include "compound_shape.h"
#include "two_dimensional_coordinate.h"
#include "info_visitor.h"
#include <vector>
#include <sstream>

class InfoVisitor: public Visitor{
public:
    void visit(Ellipse* ellipse) {
        std::stringstream semiMjStream;
        semiMjStream<<std::fixed<<std::setprecision(3)<<ellipse->getSemiMajorAxes();
        std::stringstream semiMnStream;
        semiMnStream<<std::fixed<<std::setprecision(3)<<ellipse->getSemiMinorAxes();
        _info = "Ellipse ("+ semiMjStream.str() + ", " + semiMnStream.str()+")";
    }

    void visit(Triangle* triangle) {
        std::vector<TwoDimensionalCoordinate*> _vectors = triangle->getVectors();
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
        
        _info = "Triangle (["+x1.str()+", "+y1.str()+"], ["+x2.str()+", "+y2.str()+"], ["+x3.str()+", "+y3.str()+"])";
    }

    void visit(Rectangle* rectangle) {
        double _length = rectangle->getLength();
        double _width = rectangle->getWidth();

        std::stringstream lengthSS;
        std::stringstream widthSS;

        lengthSS<<std::fixed<<std::setprecision(3)<<_length;
        widthSS<<std::fixed<<std::setprecision(3)<<_width;
        _info = "Rectangle (" + lengthSS.str() + ", " + widthSS.str() + ")";
    }

    void visit(CompoundShape* compoundShape) {
        std::string result;
        std::list<Shape*> _shapes = compoundShape->getShapes();
        for(std::list<Shape *>::const_iterator i = _shapes.begin(); i != _shapes.end(); ++i){
            InfoVisitor * iVstr = new InfoVisitor();
            (*i)->accept(iVstr);
            if(i==_shapes.begin()){
                result += iVstr ->info();
            }else{
                result += ", "+ iVstr->info();
            }
        }
        _info = "Compound Shape {" + result + "}";
    }

    std::string info() const {
        return _info;
    }

private:
    std::string _info;
};
#endif