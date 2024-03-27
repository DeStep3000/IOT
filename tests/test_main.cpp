#include <iostream>
#include <gtest/gtest.h>
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
TEST(intersect_polygon_field_final_test,one_point_test4){
    std::string input = "03 1 1 5 1 5 6 03 5 3 8 4 7 6";
    input= edit_file(input);
    PolygonField pn_field;
    pn_field.input_polygons(input);

    std::vector<Point> pn_points{{5,3}};
    EXPECT_EQ(pn_field.intersect_polygon_field_final().get_vertices(),pn_points);
}
TEST(intersect_polygon_field_final_test,two_points_test5){
    std::string input = "03 1 1 5 1 5 6 03 3 2 7 2 7 6";
    input= edit_file(input);
    PolygonField pn_field;
    pn_field.input_polygons(input);

    std::vector<Point> pn_points{{3,2},{5,2},{5,4}};
    EXPECT_EQ(pn_field.intersect_polygon_field_final().get_vertices(),pn_points);
}
TEST(intersect_polygon_field_final_test,one_line_test6){
    std::string input = "03 1 4 5 4 3 6 03 2 4 4 4 3 2";
    input= edit_file(input);
    PolygonField pn_field;
    pn_field.input_polygons(input);

    std::vector<Point> pn_points{{2,4},{4,4}};
    EXPECT_EQ(pn_field.intersect_polygon_field_final().get_vertices(),pn_points);
}
TEST(intersect_polygon_field_final_test,four_points_test7){
    std::string input = "03 2 1 5 1 5 5 03 2 2 6 2 2 5";
    input= edit_file(input);
    PolygonField pn_field;
    pn_field.input_polygons(input);

    std::vector<Point> pn_points{{2.75,2},{5,2},{5,2.75},{3.92,3.56}};
    EXPECT_EQ(pn_field.intersect_polygon_field_final().get_vertices(),pn_points);
}
TEST(intersect_polygon_field_final_test,three_points_test8){
    std::string input = "03 1 4 6 4 4 8 03 3 2 6 2 6 8";
    input= edit_file(input);
    PolygonField pn_field;
    pn_field.input_polygons(input);

    std::vector<Point> pn_points{{4,4},{6,4},{5,6}};
    EXPECT_EQ(pn_field.intersect_polygon_field_final().get_vertices(),pn_points);
}
TEST(intersect_polygon_field_final_test,no_intersection_test9){
    std::string input = "03 2 2 6 2 4 4 03 6 4 10 4 8 6";
    input= edit_file(input);
    PolygonField pn_field;
    pn_field.input_polygons(input);

    std::vector<Point> pn_points{{2, 2}, {6, 2}, {4, 4}};
    EXPECT_EQ(pn_field.intersect_polygon_field_final().get_vertices(),pn_points);
}
TEST(intersect_polygon_field_final_test,five_points_test10){
    std::string input = "03 6 3 6 6 9 3 03 5 5 9 1 9 5";
    input= edit_file(input);
    PolygonField pn_field;
    pn_field.input_polygons(input);

    std::vector<Point> pn_points{{6, 4},{7, 3}, {9, 3},{7, 5}, {6, 5}};
    EXPECT_EQ(pn_field.intersect_polygon_field_final().get_vertices(),pn_points);
}
TEST(intersect_polygon_field_final_test,six_points_test11){
    std::string input = "03 6 3 6 6 9 3 03 8 2 5 5 8 5";
    input= edit_file(input);
    PolygonField pn_field;
    pn_field.input_polygons(input);

    std::vector<Point> pn_points{{6, 4},{7, 3}, {8, 3}, {8, 4},{7, 5}, {6, 5}};
    EXPECT_EQ(pn_field.intersect_polygon_field_final().get_vertices(),pn_points);
}

//doesnt pass
TEST(intersect_polygon_field_final_test,many_triangles_test12){
    std::string input = "03 4 8 20 8 10 2 03 6 8 18 12 19 5 03 6 6 16 6 12 12 03 6 4 14 2 14 12 03 8 4 16 4 8 12";//неверно,должно быть{ 9.25 7.25, 13.8 6.2, 12 8, 10 8 }
    //input = "03 4 8 20 8 10 2 03 4 8 18 12 19 5 03 6 6 16 6 12 12 03 6 4 14 2 14 12 03 8 4 16 4 8 12";//вообще не считает,должно быть {{9, 7},{14, 6}, {12, 8},{10,8}};
    input= edit_file(input);
    PolygonField pn_field;
    pn_field.input_polygons(input);

    std::vector<Point> pn_points{{9, 7},{14, 6}, {12, 8},{10,8}};
    EXPECT_EQ(pn_field.intersect_polygon_field_final().get_vertices(),pn_points);
}

TEST(intersect_polygon_field_final_test,intersection_and_intersection3_test13){
    std::string input = "03 2 2 5 2 3 5 03 3 1 6 1 5 3 03 8 2 13 2 10 6 03 9 1 13 1 11 6 03 11 1 15 2 14 6";
    input= edit_file(input);
    PolygonField pn_field;
    pn_field.input_polygons(input);

    std::vector<Point> pn_points{{11.6, 2},{12.6, 2}, {12.2, 3}};
    EXPECT_EQ(pn_field.intersect_polygon_field_final().get_vertices(),pn_points);
}
TEST(intersect_polygon_field_final_test,equal_triangles_test14){
    std::string input = "03 1 1 6 2 3 6 03 1 1 6 2 3 6";
    input = edit_file(input);
    PolygonField pn_field;
    pn_field.input_polygons(input);

    std::vector<Point> pn_points{{1, 1},{6, 2},{3, 6}};
    EXPECT_EQ(pn_field.intersect_polygon_field_final().get_vertices(), pn_points);
}
TEST(intersect_polygon_field_final_test,triangle_and_intersection_test15){
    std::string input = "03 2 2 6 2 4 4 03 6 4 10 4 8 6 03 7 5 9 5 8 4";
    input= edit_file(input);
    PolygonField pn_field;
    pn_field.input_polygons(input);

    std::vector<Point> pn_points{{7, 5}, {8, 4}, {9, 5}};
    EXPECT_EQ(pn_field.intersect_polygon_field_final().get_vertices(),pn_points);
}

//issue
TEST(intersect_polygon_field_final_test,many_same_triangles_and_intersection_test16){
    std::string input = "03 1 1 3 1 2 3 03 1 1 3 1 2 3 03 1 1 3 1 2 3 03 5 2 8 2 6 4 03 6 1 8 1 6 3";
    input= edit_file(input);
    PolygonField pn_field;
    pn_field.input_polygons(input);

    std::vector<Point> pn_points{{6, 2},{7, 2}, {6, 3}};
    EXPECT_EQ(pn_field.intersect_polygon_field_final().get_vertices(),pn_points);
}

TEST(intersect_polygon_field_final_test,different_polygons_test17){
    std::string input = "04 9 2 17 2 17 6 9 6 06 10 2 12 2 13 4 12 6 10 6 9 4 05 11 2 14 2 14 4 13 6 11 4 03 8 2 12 2 8 10 ";
    input= edit_file(input);
    PolygonField pn_field;
    pn_field.input_polygons(input);

    std::vector<Point> pn_points{{11, 2},{12, 2}, {11, 4}};
    EXPECT_EQ(pn_field.intersect_polygon_field_final().get_vertices(),pn_points);
}

int main(int argc, char **argv){
    ::testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}