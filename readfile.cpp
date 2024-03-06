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
    std::size_t min_index = input.find(KEY[0], index);
    for (size_t i=1;i<KEY.size();i++){
        std::size_t new_index = input.find(KEY[i], index);
        if (new_index<min_index){
            min_index=new_index;
        }
    }
    return min_index == std::string::npos ? std::string::npos : min_index;
}

std::size_t find_key(const std::string& input, std::size_t index){
    if (input.empty()) {
        // file cannot be openned, return std::string::npos
        return std::string::npos;
    }
    return find_min_key(input,index);
}

std::vector<double> get_coords(const std::string& input, std::size_t index){
    std::vector<double> coords;
    if (input.empty()) {
        // file cannot be openned, return blank vector
        return {};
    }
    if (find_min_key(input, index) == std::string::npos){
        return{};
    } else {
        std::size_t previous_index = find_key(input, index)+4;// _0*_ = 4
        std::size_t new_index = input.find_first_of(NUMBERS, previous_index);
        std::size_t next_index= find_key(input,previous_index);//next 0* index
        previous_index = new_index;
        for(int i = 0; i < 20; i++){
            new_index = input.find_first_not_of(NUMBERS, previous_index);
            if (new_index == std::string::npos) {
                // If we could not find the next number, we end the loop
                break;
            }
            coords.push_back(static_cast<double>(stod(input.substr(previous_index, new_index))));
            previous_index = input.find_first_of(NUMBERS, new_index);
            if (previous_index == std::string::npos or previous_index-1==next_index) {
                // If we could not find the next number, we end the loop
                break;
            }
        }
    }
    if (coords.size()%2!=0 or coords.size()==0){ //if some point have only one value
        return {};
    }
    return coords;
}