#ifndef IOT_READFILE_H
#define IOT_READFILE_H
#include <string>
#include <fstream>
#include <iostream>
#include <vector>

const std::string KEY = "03";
const std::string NUMBERS = "0123456789";

std::string read_file(const std::string& path);
std::size_t find_key(const std::string& path, std::size_t index=0);
std::vector<double> get_coords(const std::string& path, std::size_t index=0);

#endif