#include <iostream>
#include "readfile.h"
#include "polygon.h"


int main() {
    const std::string path = "E:\\clion\\IOT4\\test2.txt";//Absolute file path
    std::string input = read_file(path);
    input= edit_file(input);

    PolygonField pn_field;
    pn_field.input_polygons(input);
    pn_field.print_field();
    Polygon res = pn_field.intersect_polygon_field_final();
    res.print_vertices();
    return 0;
}