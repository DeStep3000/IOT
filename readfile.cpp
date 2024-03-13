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

std::size_t find_min_key(const std::string input,std::size_t index){//because now we have vector of string {"03","04","05","06","07","08","09"}
    if (index == std::string::npos || input.empty()) {
        return std::string::npos;
    }
    std::size_t min_index = input.find(KEY[0], index);
    std::size_t min_index_2 = input.find(KEY[1], index);
    min_index = min_index < min_index_2 ? min_index : min_index_2;

    return min_index == std::string::npos ? std::string::npos : min_index+1;//ссылка на 0 в _03_
}

std::size_t find_key(const std::string& input, std::size_t index){
    if (input.empty()) {
        // file cannot be openned, return std::string::npos
        return std::string::npos;
    }
    if (index == 0 && input.size() >= 3 && input.substr(0, 3) >= "03 " && input.substr(0, 3) <= "09 ") {
        return 0;
    }
    return find_min_key(input,index);
}


std::vector<double> fill_coords_from_input(const std::string& input,std::size_t previous_index){
    std::vector<double> coords;
    std::size_t new_index = input.find_first_of(NUMBERS, previous_index+2);
    std::size_t next_index= find_key(input,previous_index+2);//next 0* index
    previous_index = new_index;
    for(int i = 0; i < 20; i++){
        new_index = input.find_first_not_of(NUMBERS, previous_index);
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
        //std::size_t previous_index = find_key(input, index); _0*_ = 3
        coords = fill_coords_from_input(input, index);
    }
    if (coords.size() % 2 != 0){
        coords.pop_back();
    }
    if (coords.size() == 0) { //if some point have only one value
        return {};
    }
    return coords;
}