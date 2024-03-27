#include <iostream>
#include <gtest/gtest.h>
//#include <gmock/gmock.h>
#include "../src/polygon.h"

// test: mult_vector,intersection, is_intersected,all class polygon functions
// test: operator overloading, length, sign, abs
//main test #14 intersect_polygon_field_final
TEST(input_polygons,test1){
    std::string input=" 03 9 56 75259 259 25 27 03 10 567 4 23 75259 259 25 27 03 11 567 4 23 75259 259 67 47 47 57 05 12 567 4 23 75259 259 67 68 39 988 90 67 03 03 13 567 4 23 5 03 14 03 34 34 ";
    PolygonField pn_field;
    pn_field.input_polygons(input);
    EXPECT_EQ(pn_field.get_num_pn(),6);

    std::vector<Point> pn_point{{9,56},{75259, 259},{25, 27}};
    EXPECT_EQ(pn_field.get_field()[0].get_num_vertices(),3);
    EXPECT_EQ(pn_field.get_field()[0].get_vertices(),pn_point);

    pn_point={{10, 567}, {4, 23}, {75259, 259}};
    EXPECT_EQ(pn_field.get_field()[1].get_num_vertices(),3);
    EXPECT_EQ(pn_field.get_field()[1].get_vertices(),pn_point);

    pn_point={{11, 567}, {4, 23}, {75259, 259}};
    EXPECT_EQ(pn_field.get_field()[2].get_num_vertices(),3);
    EXPECT_EQ(pn_field.get_field()[2].get_vertices(),pn_point);

    pn_point={{12, 567}, {4, 23} ,{75259, 259}, {67, 68}, {39, 988}};
    EXPECT_EQ(pn_field.get_field()[3].get_num_vertices(),5);
    EXPECT_EQ(pn_field.get_field()[3].get_vertices(),pn_point);

    pn_point={{13, 567}, {4, 23}};
    EXPECT_EQ(pn_field.get_field()[4].get_num_vertices(),2);
    EXPECT_EQ(pn_field.get_field()[4].get_vertices(),pn_point);

    pn_point={{34, 34}};
    EXPECT_EQ(pn_field.get_field()[5].get_num_vertices(),1);
    EXPECT_EQ(pn_field.get_field()[5].get_vertices(),pn_point);
}


int main(int argc, char **argv){
    ::testing::InitGoogleTest(&argc, argv);
    //::testing::InitGoogleMock(&argc, argv);

    return RUN_ALL_TESTS();
}