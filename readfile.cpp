#include "readfile.h"

std::string read_file(const std::string& path){
    std::string output;
    std::string line;
    std::ifstream in;
    in.open(path);
    if (in.is_open())
    {
        getline ( in, output, '\0' );
    }
    in.close();
    return output;
}