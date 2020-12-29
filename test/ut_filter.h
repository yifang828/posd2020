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
        rectangle_2 = new Rectangle("2", 3, 4);
        shapes.push_back(rectangle_2);
        rectangle_5 = new Rectangle("5", 5, 4);
        shapes.push_back(rectangle_5);
    }

    virtual void TearDown() {}

    std::list<Shape*> shapes = {};
    Shape* rectangle_2;
    Shape* rectangle_5;
};

TEST_F(FilterTestSuite, customized_filter){
    Filter* areaFilter = new ShapeFilter([](Shape* shape) {return shape->area() <= 30;});
    Filter* perimeterFilter = new ShapeFilter([](Shape* shape) {return shape->perimeter() >= 15;});
    Filter* colorFilter = new ShapeFilter([](Shape* shape) {return shape->color() == "white";});
    areaFilter->setNext(perimeterFilter)->setNext(colorFilter);
    areaFilter;
    std::list<Shape*> results = areaFilter->push(shapes);
    for(auto s:shapes){
        std::cout<<s->area()<<std::endl;
    }
    
    ASSERT_EQ(1, results.size());
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