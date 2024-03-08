#ifndef IOT_READFILE_H
#define IOT_READFILE_H
#include <string>
#include <fstream>
#include <iostream>
#include <vector>

const std::vector<std::string> KEY = {" 03 "," 04 "," 05 "," 06 "," 07 "," 08 "," 09 ", "\n03 ","\n04 ","\n05 ","\n06 ","\n07 ","\n08 ","\n09 "};//word that used for cutting coords
const std::string NUMBERS = "0123456789";//numbers that used to find first number after key

std::string read_file(const std::string& path);
std::size_t find_min_key(const std::string input,std::size_t index);
std::size_t find_key(const std::string& path, std::size_t index=0);
std::vector<double> fill_coords_from_input(const std::string& input,std::size_t previous_index);
std::vector<double> get_coords(const std::string& path, std::size_t index=0);

#endif