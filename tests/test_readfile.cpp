#include <iostream>
#include <gtest/gtest.h>
#include "../src/readfile.h"

TEST(edit_file_test, start_end_space) {
    std::string input = "475485";
    ASSERT_EQ(edit_file(input), " 475485 ");

    input = "475 48 5";
    ASSERT_EQ(edit_file(input), " 475 48 5 ");

    input = " 475485";
    ASSERT_EQ(edit_file(input), " 475485 ");

    input = "475485 ";
    ASSERT_EQ(edit_file(input), " 475485 ");

    input = " 475485 ";
    ASSERT_EQ(edit_file(input), " 475485 ");

    input = " 411111 ";
    ASSERT_EQ(edit_file(input), " 411111 ");

    input = "-1 -5 5";
    ASSERT_EQ(edit_file(input), " -1 -5 5 ");
}

TEST(edit_file_test, new_line) {
    std::string input = "48 \n fdif 34 5885 \n 31 \n 3983 \n 494";
    ASSERT_TRUE(edit_file(input) == " 48 fdif 34 5885 31 3983 494 ");

    input = "48\n fdif 34 5885\n 31\n 3983\n 494";
    ASSERT_TRUE(edit_file(input) == " 48 fdif 34 5885 31 3983 494 ");

    input = "48 \nfdif 34 5885 \n31 \n3983 \n494";
    ASSERT_TRUE(edit_file(input) == " 48 fdif 34 5885 31 3983 494 ");

    input = "48\nfdif 34 5885\n31\n3983\n494";
    ASSERT_TRUE(edit_file(input) == " 48 fdif 34 5885 31 3983 494 ");

    input = "\n48 fdif 34 5885 31 3983 494\n";
    ASSERT_TRUE(edit_file(input) == " 48 fdif 34 5885 31 3983 494 ");

    input = "48 \n fdif 34 5885\n 31 \n3983\n494\n";
    ASSERT_TRUE(edit_file(input) == " 48 fdif 34 5885 31 3983 494 ");
}

TEST(edit_file_test, multiple_space) {
    std::string input = "            4754 85";
    ASSERT_EQ(edit_file(input), " 4754 85 ");

    input = "475              48 5";
    ASSERT_EQ(edit_file(input), " 475 48 5 ");

    input = "475 48 5             ";
    ASSERT_EQ(edit_file(input), " 475 48 5 ");

    input = "   475    48     5        ";
    ASSERT_EQ(edit_file(input), " 475 48 5 ");
}

TEST(edit_file_test, total_results) {
    std::string input = "48 \n            fdi    5\n343       f 34 5885\n 31 \n3983 \n     494\n";
    ASSERT_TRUE(edit_file(input) == " 48 fdi 5 343 f 34 5885 31 3983 494 ");
}

TEST(find_key_test, different_keys) {
    std::string input = " 03 9405 03 94";
    ASSERT_EQ(find_key(input, 0), 0);
    input = " 04 9405 03 94";
    ASSERT_EQ(find_key(input, 0), 0);
    input = " 05 9405 03 94";
    ASSERT_EQ(find_key(input, 0), 0);
    input = " 06 9405 03 94";
    ASSERT_EQ(find_key(input, 0), 0);
    input = " 07 9405 03 94";
    ASSERT_EQ(find_key(input, 0), 0);
    input = " 08 9405 03 94";
    ASSERT_EQ(find_key(input, 0), 0);
    input = " 09 9405 03 94";
    ASSERT_EQ(find_key(input, 0), 0);
}

TEST(find_key_test, different_indeces) {
    std::string input = " 03 9405 03 94 479539 05 3i9734 03 8484 09 4884 06 ";
    ASSERT_EQ(find_key(input, 0), 0);
    ASSERT_EQ(find_key(input, 1), 8);
    ASSERT_EQ(find_key(input, 2), 8);
    ASSERT_EQ(find_key(input, 7), 8);
    ASSERT_EQ(find_key(input, 8), 8);
    ASSERT_EQ(find_key(input, 9), 21);
    ASSERT_EQ(find_key(input, 22), 31);
    ASSERT_EQ(find_key(input, 32), 39);
    ASSERT_EQ(find_key(input, 45), 47);
}

TEST(find_key_test, some_extreme_cases) {
    std::string input = " 03 9405 03 94";
    ASSERT_EQ(find_key(input, 0), 0);
    input = " 13 94 03 ";
    ASSERT_EQ(find_key(input, 0), 6);
    input = " 13 94 13";
    ASSERT_EQ(find_key(input, 0), std::string::npos);
    input = "";
    ASSERT_EQ(find_key(input, 0), std::string::npos);
    input = " ";
    ASSERT_EQ(find_key(input, 0), std::string::npos);
}

TEST(get_coords_test, different_keys) {
    std::string input = " 38 03 11 12 21 22 31 32 41 42 51 52 61 62 71 72 81 82 91 92 47 38 37 37 03 ";
    std::vector<double> result{11, 12, 21, 22, 31, 32};
    EXPECT_EQ(get_coords(input, 3), result);

    input = " 38 04 11 12 21 22 31 32 41 42 51 52 61 62 71 72 81 82 91 92 47 38 37 37 03 ";
    result = {11, 12, 21, 22, 31, 32, 41, 42};
    EXPECT_EQ(get_coords(input, 3), result);

    input = " 38 05 11 12 21 22 31 32 41 42 51 52 61 62 71 72 81 82 91 92 47 38 37 37 03 ";
    result = {11, 12, 21, 22, 31, 32, 41, 42, 51, 52};
    EXPECT_EQ(get_coords(input, 3), result);

    input = " 38 06 11 12 21 22 31 32 41 42 51 52 61 62 71 72 81 82 91 92 47 38 37 37 03 ";
    result = {11, 12, 21, 22, 31, 32, 41, 42, 51, 52, 61, 62};
    EXPECT_EQ(get_coords(input, 3), result);

    input = " 38 07 11 12 21 22 31 32 41 42 51 52 61 62 71 72 81 82 91 92 47 38 37 37 03 ";
    result = {11, 12, 21, 22, 31, 32, 41, 42, 51, 52, 61, 62, 71, 72};
    EXPECT_EQ(get_coords(input, 3), result);

    input = " 38 08 11 12 21 22 31 32 41 42 51 52 61 62 71 72 81 82 91 92 47 38 37 37 03 ";
    result = {11, 12, 21, 22, 31, 32, 41, 42, 51, 52, 61, 62, 71, 72, 81, 82};
    EXPECT_EQ(get_coords(input, 3), result);

    input = " 38 09 11 12 21 22 31 32 41 42 51 52 61 62 71 72 81 82 91 92 47 38 37 37 03 ";
    result = {11, 12, 21, 22, 31, 32, 41, 42, 51, 52, 61, 62, 71, 72, 81, 82, 91, 92};
    EXPECT_EQ(get_coords(input, 3), result);

}

TEST(get_coords_test, different_indeces) {
    std::string input = " 38 03 11 12 21 22 31 32 03 41 42 51 52 61 62 03 71 72 81 82 91 92 03 47 38 37 37 03 ";
    std::vector<double> result{11, 12, 21, 22, 31, 32};
    EXPECT_EQ(get_coords(input, 3), result);

    result = {41, 42, 51, 52, 61, 62};
    EXPECT_EQ(get_coords(input, 24), result);

    result = {71, 72, 81, 82, 91, 92};
    EXPECT_EQ(get_coords(input, 45), result);

    result = {47, 38, 37, 37};
    EXPECT_EQ(get_coords(input, 66), result);

    result = {};
    EXPECT_EQ(get_coords(input, 81), result);
}

TEST(get_coords_test, some_extreme_cases) {
    std::string input = "";
    std::vector<double> result{};
    EXPECT_EQ(get_coords(input, 0), result);

    input = " ";
    result = {};
    EXPECT_EQ(get_coords(input, 3), result);

    input = " 26 38 46 2";
    result = {};
    EXPECT_EQ(get_coords(input, 3), result);

    input = " 38 04 11 12 21 22 31 32 41 42 51 52 61 62 71 72 81 82 91 92 47 38 37 37 03 ";
    result = {11, 12, 21, 22, 31, 32, 41, 42};
    EXPECT_EQ(get_coords(input, 3), result);

    input = " 38 04 11 12 21 22 31 32 03 ";
    result = {11, 12, 21, 22, 31, 32};
    EXPECT_EQ(get_coords(input, 3), result);

    input = " 38 04 11 12 21 22 31 03 ";
    result = {11, 12, 21, 22};
    EXPECT_EQ(get_coords(input, 3), result);

    input = " 38 04 11 ";
    result = {};
    EXPECT_EQ(get_coords(input, 3), result);

    input = " 38 04 ";
    result = {};
    EXPECT_EQ(get_coords(input, 3), result);

    input = " 38 04 -1 12 -1 22 31 32 41 -2 51 52 61 62 71 72 81 82 91 92 47 38 37 37 03 ";
    result = {-1, 12, -1, 22, 31, 32, 41, -2};
    EXPECT_NE(get_coords(input, 3), result);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}