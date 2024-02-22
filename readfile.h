#ifndef IOT_READFILE_H
#define IOT_READFILE_H
#include <string>
#include <fstream>
#include <iostream>
#include <vector>

const std::string KEY = "03";//word that used for cutting coords
const std::string NUMBERS = "0123456789";//numbers that used to find first number after key

std::string read_file(const std::string& path);
long int find_key(const std::string& path, long int index=0);// changed to long int
std::vector<double> get_coords(const std::string& path, std::size_t index=0);

#endif