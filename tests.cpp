#include <iostream>
#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "readfile.h"

TEST(edit_file_test,start_end_space) {
    std::string input ="475485";
    ASSERT_TRUE(edit_file(input)==" 475485 ");

    input ="475 48 5";
    ASSERT_TRUE(edit_file(input)==" 475 48 5 ");

    input =" 475485";
    ASSERT_TRUE(edit_file(input)==" 475485 ");

    input ="475485 ";
    ASSERT_TRUE(edit_file(input)==" 475485 ");

    input =" 475485 ";
    ASSERT_TRUE(edit_file(input)==" 475485 ");
}

TEST(edit_file_test,new_line){
    std::string input="48 \n fdif 34 5885 \n 31 \n 3983 \n 494";
    ASSERT_TRUE(edit_file(input)==" 48 fdif 34 5885 31 3983 494 ");

    input="48\n fdif 34 5885\n 31\n 3983\n 494";
    ASSERT_TRUE(edit_file(input)==" 48 fdif 34 5885 31 3983 494 ");

    input="48 \nfdif 34 5885 \n31 \n3983 \n494";
    ASSERT_TRUE(edit_file(input)==" 48 fdif 34 5885 31 3983 494 ");

    input="48\nfdif 34 5885\n31\n3983\n494";
    ASSERT_TRUE(edit_file(input)==" 48 fdif 34 5885 31 3983 494 ");

    input="\n48 fdif 34 5885 31 3983 494\n";
    ASSERT_TRUE(edit_file(input)==" 48 fdif 34 5885 31 3983 494 ");

    input="48 \n fdif 34 5885\n 31 \n3983\n494\n";
    ASSERT_TRUE(edit_file(input)==" 48 fdif 34 5885 31 3983 494 ");
}

TEST(edit_file_test,multiple_space) {
    std::string input ="            4754 85";
    ASSERT_TRUE(edit_file(input)==" 4754 85 ");

    input ="475              48 5";
    ASSERT_TRUE(edit_file(input)==" 475 48 5 ");

    input ="475 48 5             ";
    ASSERT_TRUE(edit_file(input)==" 475 48 5 ");

    input ="   475    48     5        ";
    ASSERT_TRUE(edit_file(input)==" 475 48 5 ");
}

TEST(edit_file_test,total_results) {
    std::string input="48 \n            fdi    5\n343       f 34 5885\n 31 \n3983 \n     494\n";
    ASSERT_TRUE(edit_file(input)==" 48 fdi 5 343 f 34 5885 31 3983 494 ");
}
// test: find_key,get_coords, input_polygons,intersect_polygon_field_final
// test: mult_vector,intersection, is_intersected,all class polygon functions
// test: operator overloading, length, sign, abs

/*TEST(find_min_key_test,different_inputs){
    ASSERT_TRUE(find_key("03 90494 20",0)==0);
}*/

int main(int argc, char **argv){
    ::testing::InitGoogleTest(&argc, argv);
    ::testing::InitGoogleMock(&argc, argv);

    return RUN_ALL_TESTS();
}