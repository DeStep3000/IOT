#include "readfile.h"
#include <iostream> // for mistakes

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

std::size_t find_key(const std::string& path, std::size_t index){
    std::string input = read_file(path);
    if (input.empty()) {
        // file cannot be openned, return -1
        return -1;
    }
    std::size_t new_index = input.find(KEY, index);
    return new_index == std::string::npos ? -1 : new_index;
}

std::vector<double> get_coords(const std::string& path, std::size_t index){
    std::vector<double> coords;
    std::string input = read_file(path);
    if (input.empty()) {
        // file cannot be openned, return blank vector
        return {};
    }
    std::size_t previous_index = input.find(KEY, index)+2;
    std::size_t new_index = input.find_first_of(NUMBERS, previous_index);
    previous_index = new_index;
    if (input.find(KEY, index) == std::string::npos){
        return{};
    } else {
        for(int i = 0; i < 6; i++){
            new_index = input.find_first_not_of(NUMBERS, previous_index);
            if (new_index == std::string::npos) {
                // If we could not find the next number, we end the loop
                break;
            }
            coords.push_back(stod(input.substr(previous_index, new_index)));
            previous_index = input.find_first_of(NUMBERS, new_index);
            if (previous_index == std::string::npos) {
                // If we could not find the next number, we end the loop
                break;
            }
        }
    }
    return coords;
}