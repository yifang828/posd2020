#define ABS 0.001

#include <gtest/gtest.h>
#include "../src/shape_builder.h"

class Shape;

TEST(ShapeBuilderTest, build_rectangle) {
    ShapeBuilder sb;
    sb.buildRectangle(3, 4);
    std::deque<Shape*> results = sb.getResult();

    ASSERT_EQ(1, results.size());
    ASSERT_EQ("Rectangle (3.000, 4.000)", results[0]->info());
}

TEST(ShapeBuilderTest, build_ellipse) {
    ShapeBuilder sb;
    sb.buildEllipse(4.2, 3.7);
    std::deque<Shape*> results = sb.getResult();

    ASSERT_EQ(1, results.size());
    ASSERT_EQ("Ellipse (4.200, 3.700)", results[0]->info());
}

TEST(ShapeBuilderTest, build_triangle) {
    ShapeBuilder sb;
    sb.buildTriangle(0, 0, 0, -3, -4, 0);
    std::deque<Shape*> results = sb.getResult();

    ASSERT_EQ(1, results.size());
    ASSERT_EQ("Triangle ([0.000, 0.000], [0.000, -3.000], [-4.000, 0.000])", results[0]->info());
}

TEST(ShapeBuilderTest, build_multi_simple_shapes) {
    ShapeBuilder sb;
    sb.buildRectangle(3, 4);
    sb.buildRectangle(3, 4);
    sb.buildEllipse(4.2, 3.7);
    sb.buildTriangle(0, 0, 0, -3, -4, 0);

    std::deque<Shape*> results = sb.getResult();

    ASSERT_EQ(4, results.size());

    EXPECT_EQ("Rectangle (3.000, 4.000)", results[0]->info());
    EXPECT_EQ("Rectangle (3.000, 4.000)", results[1]->info());
    EXPECT_EQ("Ellipse (4.200, 3.700)", results[2]->info());
    EXPECT_EQ("Triangle ([0.000, 0.000], [0.000, -3.000], [-4.000, 0.000])", results[3]->info());

    EXPECT_NE(results[0]->id(), results[1]->id());
    EXPECT_NE(results[1]->id(), results[2]->id());
    EXPECT_NE(results[2]->id(), results[3]->id());
    EXPECT_NE(results[3]->id(), results[0]->id());
}

TEST(ShapeBuilderTest, build_empty_compoundShape) {
    ShapeBuilder sb;
    sb.buildCompoundShapeBegin();
    sb.buildCompoundShapeEnd();

    std::deque<Shape*> results = sb.getResult();

    ASSERT_EQ(1, results.size());
    EXPECT_EQ("Compound Shape {}", results[0]->info());
}

TEST(ShapeBuilderTest, build_compoundShape_that_contains_rectangle) {
    ShapeBuilder sb;
    sb.buildCompoundShapeBegin();
    sb.buildRectangle(3, 4);
    sb.buildCompoundShapeEnd();

    std::deque<Shape*> results = sb.getResult();

    ASSERT_EQ(1, results.size());
    EXPECT_EQ("Compound Shape {Rectangle (3.000, 4.000)}", results[0]->info());
}

TEST(ShapeBuilderTest, build_compoundShape_that_contains_ellipse) {
    ShapeBuilder sb;
    sb.buildCompoundShapeBegin();
    sb.buildEllipse(4.2, 3.7);
    sb.buildCompoundShapeEnd();

    std::deque<Shape*> results = sb.getResult();

    ASSERT_EQ(1, results.size());
    ASSERT_EQ("Compound Shape {Ellipse (4.200, 3.700)}", results[0]->info());
}

TEST(ShapeBuilderTest, build_compoundShape_that_contains_trinalge) {
    ShapeBuilder sb;
    sb.buildCompoundShapeBegin();
    sb.buildTriangle(0, 0, 0, -3, -4, 0);
    sb.buildCompoundShapeEnd();

    std::deque<Shape*> results = sb.getResult();

    ASSERT_EQ(1, results.size());
    ASSERT_EQ("Compound Shape {Triangle ([0.000, 0.000], [0.000, -3.000], [-4.000, 0.000])}", results[0]->info());
}

TEST(ShapeBuilderTest, build_compoundShape_that_contains_multi_simple_shapes) {
    ShapeBuilder sb;
    sb.buildCompoundShapeBegin();
    sb.buildRectangle(3, 4);
    sb.buildEllipse(4.2, 3.7);
    sb.buildTriangle(0, 0, 0, -3, -4, 0);
    sb.buildCompoundShapeEnd();

    std::deque<Shape*> results = sb.getResult();

    ASSERT_EQ(1, results.size());
    ASSERT_EQ("Compound Shape {Rectangle (3.000, 4.000), Ellipse (4.200, 3.700), Triangle ([0.000, 0.000], [0.000, -3.000], [-4.000, 0.000])}", results[0]->info());
}

TEST(ShapeBuilderTest, build_compoundShape_that_contains_a_empty_compoundShape) {
    ShapeBuilder sb;
    sb.buildCompoundShapeBegin();
    sb.buildCompoundShapeBegin();
    sb.buildCompoundShapeEnd();
    sb.buildCompoundShapeEnd();

    std::deque<Shape*> results = sb.getResult();

    ASSERT_EQ(1, results.size());
    ASSERT_EQ("Compound Shape {Compound Shape {}}", results[0]->info());
}

TEST(ShapeBuilderTest, build_compoundShape_that_contains_multi_simple_shapes_and_a_empty_compoundShape) {
    ShapeBuilder sb;
    sb.buildCompoundShapeBegin();
    sb.buildRectangle(3, 4);
    sb.buildEllipse(4.2, 3.7);
    sb.buildTriangle(0, 0, 0, -3, -4, 0);
    sb.buildCompoundShapeBegin();
    sb.buildCompoundShapeEnd();
    sb.buildCompoundShapeEnd();

    std::deque<Shape*> results = sb.getResult();

    ASSERT_EQ(1, results.size());
    ASSERT_EQ("Compound Shape {Rectangle (3.000, 4.000), Ellipse (4.200, 3.700), Triangle ([0.000, 0.000], [0.000, -3.000], [-4.000, 0.000]), Compound Shape {}}", results[0]->info());
}

TEST(ShapeBuilderTest, build_compoundShape_and_multi_shapes_at_same_time) {
    ShapeBuilder sb;

    sb.buildTriangle(0, 0, 0, -3, -4, 0);
    sb.buildTriangle(0, 0, 0, -3, -4, 0);

    sb.buildCompoundShapeBegin();
    sb.buildRectangle(3, 4);
    sb.buildEllipse(4.2, 3.7);
    sb.buildTriangle(0, 0, 0, -3, -4, 0);
    sb.buildCompoundShapeEnd();

    sb.buildRectangle(3, 4);

    sb.buildCompoundShapeBegin();
    sb.buildCompoundShapeEnd();

    sb.buildEllipse(4.2, 3.7);

    std::deque<Shape*> results = sb.getResult();

    ASSERT_EQ(6, results.size());

    EXPECT_EQ("Triangle ([0.000, 0.000], [0.000, -3.000], [-4.000, 0.000])", results[0]->info());
    EXPECT_EQ("Triangle ([0.000, 0.000], [0.000, -3.000], [-4.000, 0.000])", results[1]->info());
    EXPECT_EQ("Compound Shape {Rectangle (3.000, 4.000), Ellipse (4.200, 3.700), Triangle ([0.000, 0.000], [0.000, -3.000], [-4.000, 0.000])}", results[2]->info());
    EXPECT_EQ("Rectangle (3.000, 4.000)", results[3]->info());
    EXPECT_EQ("Compound Shape {}", results[4]->info());
    EXPECT_EQ("Ellipse (4.200, 3.700)", results[5]->info());

    EXPECT_NE(results[0]->id(), results[1]->id());
    EXPECT_NE(results[1]->id(), results[2]->id());
    EXPECT_NE(results[2]->id(), results[3]->id());
    EXPECT_NE(results[3]->id(), results[4]->id());
    EXPECT_NE(results[4]->id(), results[5]->id());
    EXPECT_NE(results[5]->id(), results[0]->id());
}

TEST(ShapeBuilderTest, build_level_3_compoundShape_and_multi_shapes_at_same_time) {
    ShapeBuilder sb;

    sb.buildTriangle(0, 0, 0, -3, -4, 0);

    sb.buildCompoundShapeBegin();
    sb.buildRectangle(3, 4);
    sb.buildEllipse(4.2, 3.7);
    sb.buildTriangle(0, 0, 0, -3, -4, 0);
    sb.buildCompoundShapeBegin();
    sb.buildEllipse(4.2, 3.7);
    sb.buildTriangle(0, 0, 0, -3, -4, 0);
    sb.buildCompoundShapeEnd();
    sb.buildCompoundShapeEnd();

    sb.buildRectangle(3, 4);

    sb.buildCompoundShapeBegin();
    sb.buildCompoundShapeEnd();

    sb.buildEllipse(4.2, 3.7);
    sb.buildEllipse(4.2, 3.7);

    std::deque<Shape*> results = sb.getResult();

    ASSERT_EQ(6, results.size());

    EXPECT_EQ("Triangle ([0.000, 0.000], [0.000, -3.000], [-4.000, 0.000])", results[0]->info());
    EXPECT_EQ("Compound Shape {Rectangle (3.000, 4.000), Ellipse (4.200, 3.700), Triangle ([0.000, 0.000], [0.000, -3.000], [-4.000, 0.000]), Compound Shape {Ellipse (4.200, 3.700), Triangle ([0.000, 0.000], [0.000, -3.000], [-4.000, 0.000])}}", results[1]->info());
    EXPECT_EQ("Rectangle (3.000, 4.000)", results[2]->info());
    EXPECT_EQ("Compound Shape {}", results[3]->info());
    EXPECT_EQ("Ellipse (4.200, 3.700)", results[4]->info());
    EXPECT_EQ("Ellipse (4.200, 3.700)", results[5]->info());

    EXPECT_NE(results[0]->id(), results[1]->id());
    EXPECT_NE(results[1]->id(), results[2]->id());
    EXPECT_NE(results[2]->id(), results[3]->id());
    EXPECT_NE(results[3]->id(), results[4]->id());
    EXPECT_NE(results[4]->id(), results[5]->id());
    EXPECT_NE(results[5]->id(), results[0]->id());
}
