#include <iostream>
#include <gtest/gtest.h>
//#include <gmock/gmock.h>
#include "../src/polygon.h"

// test: mult_vector,intersection, is_intersected,all class polygon functions
// test: operator overloading, length, sign, abs
//main test #14 intersect_polygon_field_final
TEST(input_polygons, test1) {
    std::string input = " 03 9 56 75259 259 25 27 03 10 567 4 23 75259 259 25 27 03 11 567 4 23 75259 259 67 47 47 57 05 12 567 4 23 75259 259 67 68 39 988 90 67 03 03 13 567 4 23 5 03 14 03 34 34 ";
    PolygonField pn_field;
    pn_field.input_polygons(input);
    EXPECT_EQ(pn_field.get_num_pn(), 6);

    std::vector<Point> pn_point{{9,     56},
                                {75259, 259},
                                {25,    27}};
    EXPECT_EQ(pn_field.get_field()[0].get_num_vertices(), 3);
    EXPECT_EQ(pn_field.get_field()[0].get_vertices(), pn_point);

    pn_point = {{10,    567},
                {4,     23},
                {75259, 259}};
    EXPECT_EQ(pn_field.get_field()[1].get_num_vertices(), 3);
    EXPECT_EQ(pn_field.get_field()[1].get_vertices(), pn_point);

    pn_point = {{11,    567},
                {4,     23},
                {75259, 259}};
    EXPECT_EQ(pn_field.get_field()[2].get_num_vertices(), 3);
    EXPECT_EQ(pn_field.get_field()[2].get_vertices(), pn_point);

    pn_point = {{12,    567},
                {4,     23},
                {75259, 259},
                {67,    68},
                {39,    988}};
    EXPECT_EQ(pn_field.get_field()[3].get_num_vertices(), 5);
    EXPECT_EQ(pn_field.get_field()[3].get_vertices(), pn_point);

    pn_point = {{13, 567},
                {4,  23}};
    EXPECT_EQ(pn_field.get_field()[4].get_num_vertices(), 2);
    EXPECT_EQ(pn_field.get_field()[4].get_vertices(), pn_point);

    pn_point = {{34, 34}};
    EXPECT_EQ(pn_field.get_field()[5].get_num_vertices(), 1);
    EXPECT_EQ(pn_field.get_field()[5].get_vertices(), pn_point);
}

TEST(intersect_polygon_field_final_test, void_space_test1) {
    std::string input = "";
    input = edit_file(input);
    PolygonField pn_field;
    pn_field.input_polygons(input);
    Polygon res = pn_field.intersect_polygon_field_final();
    Polygon void_res;
    EXPECT_EQ(res.get_vertices(), void_res.get_vertices());

    input = " ";
    input = edit_file(input);
    PolygonField pn_field1;
    pn_field1.input_polygons(input);
    Polygon res1 = pn_field1.intersect_polygon_field_final();
    EXPECT_EQ(res1.get_vertices(), void_res.get_vertices());

    input = " 48 4949 3483 0303 4848 38 ";
    input = edit_file(input);
    PolygonField pn_field2;
    pn_field2.input_polygons(input);
    Polygon res2 = pn_field2.intersect_polygon_field_final();
    EXPECT_EQ(res2.get_vertices(), void_res.get_vertices());
}

TEST(intersect_polygon_field_final_test, single_pn_test2) {
    std::string input = "03 1 1 2 3 3 2";
    input = edit_file(input);
    PolygonField pn_field;
    pn_field.input_polygons(input);
    Polygon res = pn_field.intersect_polygon_field_final();

    std::vector<Point> pn_points{{1, 1},
                                 {2, 3},
                                 {3, 2}};
    EXPECT_EQ(res.get_num_vertices(), 3);
    EXPECT_EQ(res.get_vertices(), pn_points);

    pn_points = {{1.0 + eps, 1},
                 {2,         3},
                 {3,         2}};
    for (size_t i = 0; i < pn_points.size(); i++) {
        EXPECT_TRUE(pn_points[i] == res.get_vertices()[i]);
    }
    EXPECT_EQ(res.get_vertices(), pn_points);

    pn_points = {{2, 3},
                 {1, 1},
                 {3, 2}};
    EXPECT_NE(res.get_vertices(), pn_points);
}

TEST(intersect_polygon_field_final_test, triangle_inside_test3) {
    std::string input = "03 1 1 6 2 3 6 03 2 2 4 3 3 4";
    input = edit_file(input);
    PolygonField pn_field;
    pn_field.input_polygons(input);

    std::vector<Point> pn_points{{2, 2},
                                 {4, 3},
                                 {3, 4}};
    EXPECT_EQ(pn_field.intersect_polygon_field_final().get_vertices(), pn_points);

}

TEST(intersect_polygon_field_final_test, one_point_test4) {
    std::string input = "03 1 1 5 1 5 6 03 5 3 8 4 7 6";
    input = edit_file(input);
    PolygonField pn_field;
    pn_field.input_polygons(input);

    std::vector<Point> pn_points{{5, 3}};
    EXPECT_EQ(pn_field.intersect_polygon_field_final().get_vertices(), pn_points);
}

TEST(intersect_polygon_field_final_test, two_points_test5) {
    std::string input = "03 1 1 5 1 5 6 03 3 2 7 2 7 6";
    input = edit_file(input);
    PolygonField pn_field;
    pn_field.input_polygons(input);

    std::vector<Point> pn_points{{3, 2},
                                 {5, 2},
                                 {5, 4}};
    EXPECT_EQ(pn_field.intersect_polygon_field_final().get_vertices(), pn_points);
}

TEST(intersect_polygon_field_final_test, one_line_test6) {
    std::string input = "03 1 4 5 4 3 6 03 2 4 4 4 3 2";
    input = edit_file(input);
    PolygonField pn_field;
    pn_field.input_polygons(input);

    std::vector<Point> pn_points{{2, 4},
                                 {4, 4}};
    EXPECT_EQ(pn_field.intersect_polygon_field_final().get_vertices(), pn_points);
}

TEST(intersect_polygon_field_final_test, four_points_test7) {
    std::string input = "03 2 1 5 1 5 5 03 2 2 6 2 2 5";
    input = edit_file(input);
    PolygonField pn_field;
    pn_field.input_polygons(input);

    std::vector<Point> pn_points{{2.75, 2},
                                 {5,    2},
                                 {5,    2.75},
                                 {3.92, 3.56}};
    EXPECT_EQ(pn_field.intersect_polygon_field_final().get_vertices(), pn_points);
}

TEST(intersect_polygon_field_final_test, three_points_test8) {
    std::string input = "03 1 4 6 4 4 8 03 3 2 6 2 6 8";
    input = edit_file(input);
    PolygonField pn_field;
    pn_field.input_polygons(input);

    std::vector<Point> pn_points{{4, 4},
                                 {6, 4},
                                 {5, 6}};
    EXPECT_EQ(pn_field.intersect_polygon_field_final().get_vertices(), pn_points);
}

TEST(intersect_polygon_field_final_test, no_intersection_test9) {
    std::string input = "03 2 2 6 2 4 4 03 6 4 10 4 8 6";
    input = edit_file(input);
    PolygonField pn_field;
    pn_field.input_polygons(input);

    std::vector<Point> pn_points{{2, 2},
                                 {6, 2},
                                 {4, 4}};
    EXPECT_EQ(pn_field.intersect_polygon_field_final().get_vertices(), pn_points);
}

TEST(intersect_polygon_field_final_test, five_points_test10) {
    std::string input = "03 6 3 6 6 9 3 03 5 5 9 1 9 5";
    input = edit_file(input);
    PolygonField pn_field;
    pn_field.input_polygons(input);

    std::vector<Point> pn_points{{6, 4},
                                 {7, 3},
                                 {9, 3},
                                 {7, 5},
                                 {6, 5}};
    EXPECT_EQ(pn_field.intersect_polygon_field_final().get_vertices(), pn_points);
}

TEST(intersect_polygon_field_final_test, six_points_test11) {
    std::string input = "03 6 3 6 6 9 3 03 8 2 5 5 8 5";
    input = edit_file(input);
    PolygonField pn_field;
    pn_field.input_polygons(input);

    std::vector<Point> pn_points{{6, 4},
                                 {7, 3},
                                 {8, 3},
                                 {8, 4},
                                 {7, 5},
                                 {6, 5}};
    EXPECT_EQ(pn_field.intersect_polygon_field_final().get_vertices(), pn_points);
}

TEST(intersect_polygon_field_final_test, many_triangles_test12) {
    std::string input = "03 4 8 20 8 10 2 03 4 8 18 12 19 5 03 6 6 16 6 12 12 03 6 4 14 2 14 12 03 8 4 16 4 8 12";
    input = edit_file(input);
    PolygonField pn_field;
    pn_field.input_polygons(input);

    std::vector<Point> pn_points{{9,  7},
                                 {14, 6},
                                 {12, 8},
                                 {10, 8}};
    EXPECT_EQ(pn_field.intersect_polygon_field_final().get_vertices(), pn_points);
}

TEST(intersect_polygon_field_final_test, many_triangles_test12_additional) {
    std::string input = "03 4 8 20 8 10 2 03 6 8 18 12 19 5 03 6 6 16 6 12 12 03 6 4 14 2 14 12 03 8 4 16 4 8 12";
    input = edit_file(input);
    PolygonField pn_field;
    pn_field.input_polygons(input);

    std::vector<Point> pn_points{{9.25, 7.25},
                                 {13.8, 6.2},
                                 {12,   8},
                                 {10,   8}};
    EXPECT_EQ(pn_field.intersect_polygon_field_final().get_vertices(), pn_points);
}

TEST(intersect_polygon_field_final_test, intersection_and_intersection3_test13) {
    std::string input = "03 2 2 5 2 3 5 03 3 1 6 1 5 3 03 8 2 13 2 10 6 03 9 1 13 1 11 6 03 11 1 15 2 14 6";
    input = edit_file(input);
    PolygonField pn_field;
    pn_field.input_polygons(input);

    std::vector<Point> pn_points{{11.6, 2},
                                 {12.6, 2},
                                 {12.2, 3}};
    EXPECT_EQ(pn_field.intersect_polygon_field_final().get_vertices(), pn_points);
}

TEST(intersect_polygon_field_final_test, equal_triangles_test14) {
    std::string input = "03 1 1 6 2 3 6 03 1 1 6 2 3 6";
    input = edit_file(input);
    PolygonField pn_field;
    pn_field.input_polygons(input);

    std::vector<Point> pn_points{{1, 1},
                                 {6, 2},
                                 {3, 6}};
    EXPECT_EQ(pn_field.intersect_polygon_field_final().get_vertices(), pn_points);
}

TEST(intersect_polygon_field_final_test, triangle_and_intersection_test15) {
    std::string input = "03 2 2 6 2 4 4 03 6 4 10 4 8 6 03 7 5 9 5 8 4";
    input = edit_file(input);
    PolygonField pn_field;
    pn_field.input_polygons(input);

    std::vector<Point> pn_points{{7, 5},
                                 {8, 4},
                                 {9, 5}};
    EXPECT_EQ(pn_field.intersect_polygon_field_final().get_vertices(), pn_points);
}

TEST(intersect_polygon_field_final_test, many_same_triangles_and_intersection_test16) {
    std::string input = "03 1 1 3 1 2 3 03 1 1 3 1 2 3 03 1 1 3 1 2 3 03 5 2 8 2 6 4 03 6 1 8 1 6 3";
    input = edit_file(input);
    PolygonField pn_field;
    pn_field.input_polygons(input);

    std::vector<Point> pn_points{{1, 1},
                                 {3, 1},
                                 {2, 3}};//{{6, 2},{7, 2}, {6, 3}} if we dont count same pns
    EXPECT_EQ(pn_field.intersect_polygon_field_final().get_vertices(), pn_points);
}

TEST(intersect_polygon_field_final_test, different_polygons_test17) {
    std::string input = "04 9 2 17 2 17 6 9 6 06 10 2 12 2 13 4 12 6 10 6 9 4 05 11 2 14 2 14 4 13 6 11 4 03 8 2 12 2 8 10 ";
    input = edit_file(input);
    PolygonField pn_field;
    pn_field.input_polygons(input);

    std::vector<Point> pn_points{{11, 2},
                                 {12, 2},
                                 {11, 4}};
    EXPECT_EQ(pn_field.intersect_polygon_field_final().get_vertices(), pn_points);
}

//infinite test
TEST(intersect_polygon_field_final_test, extra_test18) {
    std::string input = "03 9 56 75259 259 25 27 03 10 567 4 23 75259 259 25 27 03 11 567 4 23 75259 259 03 12 567 4 23 75259 259 67 68 39 988 90 67 03 03 13 567 4 23 5 6    03 14 8 567 678 567 103 480 444";
    input = edit_file(input);
    PolygonField pn_field;
    pn_field.input_polygons(input);

    std::vector<Point> pn_points{{11, 2},
                                 {12, 2},
                                 {11, 4}};
    EXPECT_EQ(pn_field.intersect_polygon_field_final().get_vertices(), pn_points);
}

TEST(overloading_for_points_tests, op_plus_test) {
    Point a{1, 2};
    Point b{3, 4};
    Point res{4, 6};
    EXPECT_EQ(a + b, res);
}

TEST(overloading_for_points_tests, op_plus_eq_test) {
    Point a{1, 2};
    Point b{3, 4};
    Point res{4, 6};
    EXPECT_EQ(a += b, res);
}

TEST(overloading_for_points_tests, op_minus_test) {
    Point a{1, 2};
    Point b{3, 4};
    Point res{-2, -2};
    EXPECT_EQ(a - b, res);
}

TEST(overloading_for_points_tests, op_mutiply_by_a_test) {
    double a = 2;
    Point b{3, 4};
    Point res{6, 8};
    EXPECT_EQ(a * b, res);
}

TEST(overloading_for_points_tests, op_points_multiply_test) {
    Point a{2, 5};
    Point b{3, 4};
    double res = 26;
    EXPECT_EQ(a * b, res);
}

TEST(overloading_for_points_tests, op_points_stepen_test) {
    Point a{2, 5};
    Point b{3, 4};
    double res = -7;
    EXPECT_EQ(a ^ b, res);
}

TEST(overloading_for_points_tests, minus_before_point_test) {
    Point a{2, -5};
    Point res{-2, 5};
    EXPECT_EQ(-a, res);
}

TEST(overloading_for_points_tests, equality_test) {
    Point a{2, -5};
    Point b{2, -5};
    Point c{2 + eps, -5 - eps};
    EXPECT_EQ(a, b);
    EXPECT_EQ(a, c);
}

TEST(overloading_for_points_tests, not_equal_test) {
    Point a{2, 5};
    Point b{3, 4};
    EXPECT_NE(a, b);
    Point c{2 + 2 * eps, -5 - eps};
    EXPECT_NE(a, c);
    Point d{2, 6};
    EXPECT_NE(a, d);
}

TEST(overloading_for_points_tests, greater_point_test) {
    Point a{2, 5};
    Point b{2, 4};
    EXPECT_EQ(a > b, true);
    Point c{1, 4};
    EXPECT_EQ(a > c, true);
    Point d{1, 5};
    EXPECT_EQ(a > d, true);
    Point e{1, 6};
    EXPECT_EQ(a > e, true);
    Point f{3, 4};
    EXPECT_EQ(a > f, false);
}

TEST(overloading_for_points_tests, less_point_test) {
    Point a{2, 4};
    Point b{2, 5};
    EXPECT_EQ(a < b, true);
    Point c{3, 6};
    EXPECT_EQ(a < c, true);
    Point d{3, 4};
    EXPECT_EQ(a < d, true);
    Point e{3, 6};
    EXPECT_EQ(a < e, true);
    Point f{1, 3};
    EXPECT_EQ(a < f, false);
}

TEST(overloading_for_points_tests, greater_eq_point_test) {
    Point a{2, 5};
    Point b{2, 4};
    EXPECT_EQ(a >= b, true);
    Point c{1, 4};
    EXPECT_EQ(a >= c, true);
    Point d{1, 5};
    EXPECT_EQ(a >= d, true);
    Point e{1, 6};
    EXPECT_EQ(a >= e, true);
    Point f{3, 4};
    EXPECT_EQ(a >= f, false);
    EXPECT_EQ(a >= a, true);

}

TEST(overloading_for_points_tests, less_eq_point_test) {
    Point a{2, 4};
    Point b{2, 5};
    EXPECT_EQ(a <= b, true);
    Point c{3, 6};
    EXPECT_EQ(a <= c, true);
    Point d{3, 4};
    EXPECT_EQ(a <= d, true);
    Point e{3, 6};
    EXPECT_EQ(a <= e, true);
    Point f{1, 3};
    EXPECT_EQ(a <= f, false);
    EXPECT_EQ(a <= a, true);
}


TEST(is_intersected_test, intersection_test) {
    PolygonField pn_field;
    Point a{1, 4}, b{6, 5}, c{2, 1}, d{4, 5};
    ASSERT_EQ(pn_field.is_intersected(a, b, c, d), true);
}

TEST(is_intersected_test, common_endpoint_test) {
    PolygonField pn_field;
    Point a{1, 4}, b{6, 4}, c{6, 2}, d{6, 6};
    ASSERT_EQ(pn_field.is_intersected(a, b, c, d), true);
}

TEST(is_intersected_test, non_intersection_test) {
    PolygonField pn_field;
    Point a{1, 4}, b{6, 5}, c{2, 1}, d{4, 3};
    ASSERT_EQ(pn_field.is_intersected(a, b, c, d), false);
}

TEST(is_intersected_test, parallel_test) {
    PolygonField pn_field;
    Point a{1, 4}, b{6, 4}, c{2, 3}, d{5, 3};
    ASSERT_EQ(pn_field.is_intersected(a, b, c, d), false);
}

TEST(is_intersected_test, horizontal_test) {
    PolygonField pn_field;
    Point a{1, 4}, b{6, 4}, c{3, 4}, d{3, 10};
    ASSERT_EQ(pn_field.is_intersected(a, b, c, d), false);
}

TEST(is_intersected_test, one_straight_line_test) {
    PolygonField pn_field;
    Point a{1, 4}, b{6, 4}, c{7, 4}, d{8, 4};
    ASSERT_EQ(pn_field.is_intersected(a, b, c, d), false);
}

TEST(is_intersected_test, lines_match_test) {
    PolygonField pn_field;
    Point a{1, 4}, b{6, 4}, c{1, 4}, d{6, 4};
    ASSERT_EQ(pn_field.is_intersected(a, b, c, d), false);
}

TEST(is_intersected_test, one_point_test) {
    PolygonField pn_field;
    Point a{1, 4}, b{6, 4}, c{2, 3}, d{2, 3};
    ASSERT_EQ(pn_field.is_intersected(a, b, c, d), false);
}

TEST(intersection_test, segments_intersect) {
    PolygonField pn_field;
    Point a{1, 4}, b{6, 4}, c{3, 2}, d{3, 7};
    std::vector<Point> result = pn_field.intersection(a, b, c, d);
    ASSERT_EQ(result.size(), 1);
    ASSERT_EQ(result[0].x, 3.0);
    ASSERT_EQ(result[0].y, 4.0);
}

TEST(intersection_test, non_segments_intersect) {
    PolygonField pn_field;
    Point a{3, 2}, b{4, 5}, c{6, 4}, d{4, 6};
    std::vector<Point> result = pn_field.intersection(a, b, c, d);
    ASSERT_EQ(result.size(), 0);
}

TEST(length_test, test1) {
    Point p{3.0, 4.0};
    EXPECT_EQ(length(p), 5.0);
}

TEST(sign_test, positive_number) {
    EXPECT_EQ(sign(10), 1);
}

TEST(SignTest, negative_number) {
    EXPECT_EQ(sign(-7), -1);
}

TEST(SignTest, zero) {
    EXPECT_EQ(sign(0.0), 1);
}


int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}