#include <iostream>
#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "../main.h"

TEST(input_polygons,test1){
    std::string input=" 03 9 56 75259 259 25 27 03 10 567 4 23 75259 259 25 27 03 11 567 4 23 75259 259 67 47 47 57 05 12 567 4 23 75259 259 67 68 39 988 90 67 03 03 13 567 4 23 5 03 14 03 34 34 ";
    PolygonField pn_field;
    pn_field.input_polygons(input);
    EXPECT_EQ(pn_field.get_num_pn(),6);

    //EXPECT_EQ(pn_field.get_field()[0].get_vertices(),{9,56,75259,295,25,27});
}

int main(int argc, char **argv){
    ::testing::InitGoogleTest(&argc, argv);
    ::testing::InitGoogleMock(&argc, argv);

    return RUN_ALL_TESTS();
}