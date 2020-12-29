# include <gtest/gtest.h>
# include "../src/shape_filter.h"
# include "../src/filter.h"
#include "../src/ellipse.h"
#include "../src/rectangle.h"
#include "../src/triangle.h"
#include "../src/compound_shape.h"
#include "../src/shape.h"
#include "../src/shape_setter.h"
#include <string>

class FilterTestSuite: public testing::Test {
    protected:
    virtual void SetUp() {
        // std::vector<TwoDimensionalCoordinate*> coordinates_1;
        // coordinates_1.push_back(new TwoDimensionalCoordinate(0, 0));
        // coordinates_1.push_back(new TwoDimensionalCoordinate(3, 0));
        // coordinates_1.push_back(new TwoDimensionalCoordinate(0, 4));

        // ellipse_1 = new Ellipse("1", 4, 3);
        rectangle_2 = new Rectangle("2", 3, 4);
        // triangle_3 = new Triangle("3", coordinates_1);

        // shapes.push_back(ellipse_1);
        // shapes.push_back(rectangle_2);
        // shapes.push_back(triangle_3);
        // compoundShape_7 = new CompoundShape("7", shapes);

        // std::vector<TwoDimensionalCoordinate*> coordinates_2;
        // coordinates_2.push_back(new TwoDimensionalCoordinate(0, 0));
        // coordinates_2.push_back(new TwoDimensionalCoordinate(3, 0));
        // coordinates_2.push_back(new TwoDimensionalCoordinate(0, 4));

        // ellipse_4 = new Ellipse("4", 4.2, 3.7);
        rectangle_5 = new Rectangle("5", 3.7, 4.2);
        // triangle_6 = new Triangle("6", coordinates_2);
    }

    virtual void TearDown() {}

    std::list<Shape*> shapes = {};
    // Shape* ellipse_1;
    Shape* rectangle_2;
    // Shape* triangle_3;
    // Shape* ellipse_4;
    Shape* rectangle_5;
    // Shape* triangle_6;
    // Shape* compoundShape_7;
};

TEST_F(FilterTestSuite, customized_filter){
    Filter* areaFilter = new ShapeFilter([](Shape* shape) {return shape->area() <= 30;});
    Filter* perimeterFilter = new ShapeFilter([](Shape* shape) {return shape->perimeter() >= 15;});
    Filter* colorFilter = new ShapeFilter([](Shape* shape) {return shape->color() == "black";});
    areaFilter->setNext(perimeterFilter)->setNext(colorFilter);
    std::list<Shape*> results = areaFilter->push(shapes);
    
    ASSERT_EQ(0, results.size());
}

TEST_F(FilterTestSuite, shape_setter_filter){
    Filter* areaFilter = new ShapeFilter([](Shape* shape) {return shape->area() < 30;});
    Filter* perimeterFilter = new ShapeFilter([](Shape* shape) {return shape->perimeter() > 150;});
    Filter* colorSetter = new ShapeSetter([](Shape* shape) {shape->setColor("black");});

    areaFilter->setNext(perimeterFilter)->setNext(colorSetter);
    std::list<Shape*> results = areaFilter->push(shapes);
    // std::cout<<std::to_string(results.size())<<std::endl;
    ASSERT_EQ(0, results.size());

}