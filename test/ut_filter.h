#define ABS 0.001

#include <gtest/gtest.h>
#include "../src/ellipse.h"
#include "../src/rectangle.h"
#include "../src/triangle.h"
#include "../src/compound_shape.h"
#include "../src/shape_filter.h"
#include "../src/shape_setter.h"

class FilterTestSuite: public testing::Test {
    protected:
    virtual void SetUp() {

        ellipse_1 = new Ellipse("1", 4.2, 3.7, "red");
        rectangle_2 = new Rectangle("2", 2, 2, "blue");

        std::vector<TwoDimensionalCoordinate*> triangle_3_coordinates;
        triangle_3_coordinates.push_back(new TwoDimensionalCoordinate(0, 0));
        triangle_3_coordinates.push_back(new TwoDimensionalCoordinate(0, -3));
        triangle_3_coordinates.push_back(new TwoDimensionalCoordinate(-4, 0));
        triangle_3 = new Triangle("3", triangle_3_coordinates, "yellow");

        ellipse_4 = new Ellipse("4", 4.2, 3.7, "yellow");
        rectangle_5 = new Rectangle("5", 2, 2, "blue");

        std::vector<TwoDimensionalCoordinate*> triangle_6_coordinates;
        triangle_6_coordinates.push_back(new TwoDimensionalCoordinate(0, 0));
        triangle_6_coordinates.push_back(new TwoDimensionalCoordinate(0, -3));
        triangle_6_coordinates.push_back(new TwoDimensionalCoordinate(-4, 0));
        triangle_6 = new Triangle("6", triangle_6_coordinates, "red");

        std::list<Shape*> shapes = {};
        shapes.push_back(ellipse_1);
        shapes.push_back(rectangle_2);
        shapes.push_back(triangle_3);
        compoundShape_7 = new CompoundShape("7", shapes);

        shapes.clear();
        shapes.push_back(ellipse_4);
        compoundShape_8 = new CompoundShape("8", shapes);

        shapes.clear();
        shapes.push_back(rectangle_5);
        shapes.push_back(triangle_6);
        compoundShape_9 = new CompoundShape("9", shapes);

        compoundShape_8->addShape(compoundShape_9);
        compoundShape_7->addShape(compoundShape_8);

        data = {ellipse_1, rectangle_2, triangle_3, ellipse_4, rectangle_5, triangle_6, compoundShape_7, compoundShape_8, compoundShape_9};
    }

    virtual void TearDown() {}

    Shape* ellipse_1;
    Shape* rectangle_2;
    Shape* triangle_3;
    Shape* ellipse_4;
    Shape* rectangle_5;
    Shape* triangle_6;
    Shape* compoundShape_7;
    Shape* compoundShape_8;
    Shape* compoundShape_9;
    std::list<Shape*> data;
};

TEST_F(FilterTestSuite, filter_by_area) {
    Filter* areaFilter_1 = new ShapeFilter([](Shape* shape) {return shape->area() <= 20;});
    Filter* areaFilter_2 = new ShapeFilter([](Shape* shape) {return shape->area() >= 5;});
    
    areaFilter_1->setNext(areaFilter_2);
    std::list<Shape*> results = areaFilter_1->push(data);

    ASSERT_EQ(3, results.size());
    
    EXPECT_EQ("3", results.front()->id());
    EXPECT_EQ("Triangle ([0.000, 0.000], [0.000, -3.000], [-4.000, 0.000])", results.front()->info());
    EXPECT_NEAR(6, results.front()->area(), ABS);

    results.pop_front();

    EXPECT_EQ("6", results.front()->id());
    EXPECT_EQ("Triangle ([0.000, 0.000], [0.000, -3.000], [-4.000, 0.000])", results.front()->info());
    EXPECT_NEAR(6, results.front()->area(), ABS);

    results.pop_front();

    EXPECT_EQ("9", results.front()->id());
    EXPECT_EQ("Compound Shape {Rectangle (2.000, 2.000), Triangle ([0.000, 0.000], [0.000, -3.000], [-4.000, 0.000])}", results.front()->info());
    EXPECT_NEAR(10, results.front()->area(), ABS);
}

TEST_F(FilterTestSuite, filter_by_perimeter) {
    Filter* perimeterFilter_1 = new ShapeFilter([](Shape* shape) {return shape->perimeter() <= 30;});
    Filter* perimeterFilter_2 = new ShapeFilter([](Shape* shape) {return shape->perimeter() >= 15;});
    
    perimeterFilter_1->setNext(perimeterFilter_2);
    std::list<Shape*> results = perimeterFilter_1->push(data);

    ASSERT_EQ(3, results.size());

    EXPECT_EQ("1", results.front()->id());
    EXPECT_EQ("Ellipse (4.200, 3.700)", results.front()->info());
    EXPECT_NEAR(25.247, results.front()->perimeter(), ABS);

    results.pop_front();

    EXPECT_EQ("4", results.front()->id());
    EXPECT_EQ("Ellipse (4.200, 3.700)", results.front()->info());
    EXPECT_NEAR(25.247, results.front()->perimeter(), ABS);

    results.pop_front();

    EXPECT_EQ("9", results.front()->id());
    EXPECT_EQ("Compound Shape {Rectangle (2.000, 2.000), Triangle ([0.000, 0.000], [0.000, -3.000], [-4.000, 0.000])}", results.front()->info());
    EXPECT_NEAR(20, results.front()->perimeter(), ABS);
}

TEST_F(FilterTestSuite, filter_by_area_perimeter) {
    Filter* areaFilter_1 = new ShapeFilter([](Shape* shape) {return shape->area() <= 20;});
    Filter* areaFilter_2 = new ShapeFilter([](Shape* shape) {return shape->area() >= 5;});
    Filter* perimeterFilter_1 = new ShapeFilter([](Shape* shape) {return shape->perimeter() <= 30;});
    Filter* perimeterFilter_2 = new ShapeFilter([](Shape* shape) {return shape->perimeter() >= 15;});
    
    areaFilter_1->setNext(areaFilter_2)->setNext(perimeterFilter_1)->setNext(perimeterFilter_2);
    std::list<Shape*> results = areaFilter_1->push(data);

    ASSERT_EQ(1, results.size());

    EXPECT_EQ("9", results.front()->id());
    EXPECT_EQ("Compound Shape {Rectangle (2.000, 2.000), Triangle ([0.000, 0.000], [0.000, -3.000], [-4.000, 0.000])}", results.front()->info());
    EXPECT_NEAR(10, results.front()->area(), ABS);
}

TEST_F(FilterTestSuite, filter_by_area_perimeter_color) {
    Filter* areaFilter = new ShapeFilter([](Shape* shape) {return shape->perimeter() < 20;});
    Filter* perimeterilter = new ShapeFilter([](Shape* shape) {return shape->perimeter() > 5;});
    Filter* colorFilter = new ShapeFilter([](Shape* shape) {return shape->color() == "red";});

    areaFilter->setNext(perimeterilter)->setNext(colorFilter);
    std::list<Shape*> results = areaFilter->push(data);

    ASSERT_EQ(1, results.size());

    EXPECT_EQ("6", results.front()->id());
    EXPECT_EQ("Triangle ([0.000, 0.000], [0.000, -3.000], [-4.000, 0.000])", results.front()->info());
    EXPECT_NEAR(6, results.front()->area(), ABS);
    EXPECT_NEAR(12, results.front()->perimeter(), ABS);
    EXPECT_EQ("red", results.front()->color());
}

TEST_F(FilterTestSuite, change_color) {
    Filter* areaFilter_1 = new ShapeFilter([](Shape* shape) {return shape->perimeter() <= 30;});
    Filter* areaFilter_2 = new ShapeFilter([](Shape* shape) {return shape->perimeter() >= 15;});
    Filter* changeColor = new ShapeSetter([](Shape* shape) {shape->setColor("blue");});

    areaFilter_1->setNext(areaFilter_2)->setNext(changeColor);
    std::list<Shape*> results = areaFilter_1->push(data);

    ASSERT_EQ(3, results.size());

    EXPECT_EQ("1", results.front()->id());
    EXPECT_EQ("Ellipse (4.200, 3.700)", results.front()->info());
    EXPECT_NEAR(25.247, results.front()->perimeter(), ABS);
    EXPECT_EQ("blue", results.front()->color());

    results.pop_front();

    EXPECT_EQ("4", results.front()->id());
    EXPECT_EQ("Ellipse (4.200, 3.700)", results.front()->info());
    EXPECT_NEAR(25.247, results.front()->perimeter(), ABS);
    EXPECT_EQ("blue", results.front()->color());

    results.pop_front();

    EXPECT_EQ("9", results.front()->id());
    EXPECT_EQ("Compound Shape {Rectangle (2.000, 2.000), Triangle ([0.000, 0.000], [0.000, -3.000], [-4.000, 0.000])}", results.front()->info());
    EXPECT_NEAR(20, results.front()->perimeter(), ABS);
    EXPECT_EQ("blue", results.front()->color());
}

TEST_F(FilterTestSuite, filter_when_no_result) {
    Filter* areaFilter = new ShapeFilter([](Shape* shape) {return shape->area() < 300;});
    Filter* perimeterilter = new ShapeFilter([](Shape* shape) {return shape->perimeter() > 150;});
    Filter* colorFilter = new ShapeFilter([](Shape* shape) {return shape->color() == "red";});

    areaFilter->setNext(perimeterilter)->setNext(colorFilter);
    std::list<Shape*> results = areaFilter->push(data);

    ASSERT_EQ(0, results.size());

}