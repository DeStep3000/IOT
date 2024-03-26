#include <iostream>
#include <gtest/gtest.h>
//#include <gmock/gmock.h>
#include "../main.h"

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

TEST(intersect_polygon_field_final_test,void_space_test1){
    std::string input = "";
    input= edit_file(input);
    PolygonField pn_field;
    pn_field.input_polygons(input);
    Polygon res = pn_field.intersect_polygon_field_final();
    Polygon void_res;
    EXPECT_EQ(res.get_vertices(),void_res.get_vertices());

    input = " ";
    input= edit_file(input);
    PolygonField pn_field1;
    pn_field1.input_polygons(input);
    Polygon res1 = pn_field1.intersect_polygon_field_final();
    EXPECT_EQ(res1.get_vertices(),void_res.get_vertices());

    input = " 48 4949 3483 0303 4848 38 ";
    input= edit_file(input);
    PolygonField pn_field2;
    pn_field2.input_polygons(input);
    Polygon res2 = pn_field2.intersect_polygon_field_final();
    EXPECT_EQ(res2.get_vertices(),void_res.get_vertices());
}
TEST(intersect_polygon_field_final_test,single_pn_test2){
    std::string input = "03 1 1 2 3 3 2";
    input= edit_file(input);
    PolygonField pn_field;
    pn_field.input_polygons(input);
    Polygon res = pn_field.intersect_polygon_field_final();

    std::vector<Point> pn_points{{1,1},{2,3},{3,2}};
    EXPECT_EQ(res.get_num_vertices(),3);
    EXPECT_EQ(res.get_vertices(),pn_points);

    pn_points={{1.0+eps,1},{2,3},{3,2}};
    for (size_t i=0;i<pn_points.size();i++){
        EXPECT_TRUE(pn_points[i]==res.get_vertices()[i]);
    }
    EXPECT_EQ(res.get_vertices(),pn_points);

    pn_points={{2,3},{1,1},{3,2}};
    EXPECT_NE(res.get_vertices(),pn_points);
}
TEST(intersect_polygon_field_final_test,triangle_inside_test3){
    std::string input = "03 1 1 6 2 3 6 03 2 2 4 3 3 4";
    input= edit_file(input);
    PolygonField pn_field;
    pn_field.input_polygons(input);

    std::vector<Point> pn_points{{2,2},{4,3},{3,4}};
    EXPECT_EQ(pn_field.intersect_polygon_field_final().get_vertices(),pn_points);

}


int main(int argc, char **argv){
    ::testing::InitGoogleTest(&argc, argv);
    //::testing::InitGoogleMock(&argc, argv);

    return RUN_ALL_TESTS();
}