#ifndef AREA_VISITOR_H
#define AREA_VISITOR_H
#include "ellipse.h"
#include "triangle.h"
#include "rectangle.h"
#include "compound_shape.h"
#include "two_dimensional_coordinate.h"
#include "area_visitor.h"
#include <vector>

class AreaVisitor : public Visitor{
public:
    void visit(Ellipse* ellipse) {
        double _semiMajorAxes = ellipse->getSemiMajorAxes();
        double _semiMinorAxes = ellipse->getSemiMinorAxes();
        _area = M_PI * _semiMajorAxes * _semiMinorAxes;
    }

    void visit(Triangle* triangle) {
        std::vector<TwoDimensionalCoordinate*> _vectors = triangle->getVectors();
        std::vector<double> _edges = triangle->getEdges(_vectors);

        double s = 0.5*(triangle->perimeter());
        double a = _edges[0];
        double b = _edges[1];
        double c = _edges[2];
        _area = sqrt(s*(s-a)*(s-b)*(s-c));
    }

    void visit(Rectangle* rectangle) {
        double _length = rectangle->getLength();
        double _width = rectangle->getWidth();
        _area = _length * _width;
    }

    void visit(CompoundShape* compoundShape) {
        std::list<Shape*> _shapes = compoundShape->getShapes();
        for(std::list<Shape *>::const_iterator i = _shapes.begin(); i != _shapes.end(); ++i){
            AreaVisitor * areaVstr = new AreaVisitor();
            (*i)->accept(areaVstr);
            _area += areaVstr->area();
        }
    }

    double area() const {
        return _area;
    }
private:
    double _area = 0.0;
};
#endif