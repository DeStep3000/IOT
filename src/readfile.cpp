#include "readfile.h"
#include <iostream>
#include <regex>

std::string read_file(const std::string& path){
    std::string output;
    std::ifstream in;
    in.open(path);
    if (!in.is_open()) { // if file cannot be openned
        std::cerr << "Unable to open file: " << path << std::endl;
        return ""; //return blank in that case
    }
    getline ( in, output, '\0' );
    in.close();
    return output;
}

std::string edit_file(std::string input){
    std::regex newlineRegex("\\n");
    input = std::regex_replace(input, newlineRegex, " ");
    input = " " + input + " ";
    std::regex spaceRegex("\\s+");
    input = std::regex_replace(input, spaceRegex, " ");
    return input;
}

std::size_t find_key(const std::string& input, std::size_t index){
    if (index == std::string::npos || input.empty()) {
        return std::string::npos;
    }
    std::size_t min_index = input.find(KEY[0], index);
    for (int i=1;i<7;i++){
        std::size_t new_index=input.find(KEY[i], index);
        if (new_index<min_index){
            min_index=new_index;
        }
    }
    return  min_index == std::string::npos ? std::string::npos : min_index;
}

std::vector<double> fill_coords_from_input(const std::string& input,std::size_t previous_index){
    if (input.empty() || previous_index == std::string::npos) {
        return {};
    }
    std::vector<double> coords;
    std::size_t new_index = input.find_first_of(NUMBERS, previous_index+3);
    if (new_index==std::string::npos){
        return {};
    }
    std::size_t next_index= find_key(input,previous_index+3);//next 0* index
    int s = std::stoi(input.substr(previous_index, 4));
    previous_index = new_index;

    for(int i = 0; i < 2*s; i++){
        new_index = input.find_first_not_of(NUMBERS, previous_index+1);
        if (new_index == std::string::npos) {
        // If we could not find the next number, we end the loop
            break;
        }
        coords.push_back(std::stod(input.substr(previous_index, new_index - previous_index)));
        previous_index = input.find_first_of(NUMBERS, new_index+1);
        if (previous_index == std::string::npos || previous_index>=next_index) {
            // If we could not find the next number, we end the loop
            break;
        }
    }
    return coords;
}

std::vector<double> get_coords(const std::string& input, std::size_t index){
    std::vector<double> coords;
    if (input.empty() || index == std::string::npos) {
        return {};
    } else {
        index = find_key(input,index);
        coords = fill_coords_from_input(input, index);
    }
    if (coords.size() % 2 != 0){
        coords.pop_back();
    }
    if (coords.empty()) {
        return {};
    }
    return coords;
}