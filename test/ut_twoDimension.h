#include "../src/two_dimensional_coordinate.h"

TEST(Shapes, GetCoordinate){
    TwoDimensionalCoordinate coordinate(3.56, 4);
    ASSERT_EQ(3.56, coordinate.getX());
    ASSERT_EQ(4, coordinate.getY());
}