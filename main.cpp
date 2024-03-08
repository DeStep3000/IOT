#include <iostream>
#include <cfloat>//import machine epsilon for double
#include <vector>
#include "readfile.h"

struct Point {
    double x, y;
};//struct for points in format x and y

// Данил тут работает
const double eps = 0.000000001; //needed for comparing double

class Polygon{//class for Polygons
private:
    std::vector<Point> vertices; // array of vertices, all points must be in traversal order
    int num_vertices = 0; // length of array
public:
    Polygon()= default; //using standart
    std::vector<Point> get_vertices(){//func to get array of vertices
        return this->vertices;
    }
    int get_num_vertices(){//func to get length of array
        return this->num_vertices;
    }
    bool is_empty(){//func to check emptiness of Polygon
        return this->num_vertices == 0;
    }
    void print_vertices(){//print in console all vertices
        for(Point p: this->vertices){
            std::cout << p.x << " " << p.y << "\t";
        }
        std::cout << std::endl;
    }
    void input_vertex(Point point){//func to add vertex in Polygon
        if (!is_point_vertex(point)){
            this->vertices.push_back(point);
            this->num_vertices += 1;
        }
    }
    bool is_point_vertex(Point point){//func to check if Point is already in Polygon
        for(Point p: this->get_vertices()){
            if(-eps < p.x - point.x && p.x - point.x < eps && -eps < p.y - point.y && p.y - point.y < eps){
                return true;
            }
        }
        return false;
    }
    bool is_equal_polygon(Polygon pn){//func to check same Polygons or not
        if(pn.get_num_vertices() != this->num_vertices){
            return false;
        }
        for(size_t i=0; i < this->num_vertices; i++){
            if(!pn.is_point_vertex(this->vertices[i])){
                return false;
            }
        }
        return true;
    }
    void input_from_array(std::vector<double> coordinates){//add vertices in Polygon from array
        for(int i = 0; i < coordinates.size();){
            Point a{coordinates[i], coordinates[i+1]};
            this->input_vertex(a);
            i+=2;
        }
    }
    void input_from_file(const std::string input, std::size_t index=0){//add vertices in Polygon from file using input_from_array
        std::vector<double> coordinates = get_coords(input, index);
        this->input_from_array(coordinates);
    }
    bool is_point_in(Point point){ //checking is point inside polygon
        bool result = false;
        int j = this->num_vertices - 1;
        for(int i = 0; i < this->num_vertices; i++){
            /*if (-eps < this->vertices[i].y - this->vertices[j].y < eps && -eps < this->vertices[i].y - point.y < eps){
                return true;
            }*/
            bool is_between = this->vertices[i].y < point.y && this->vertices[j].y > point.y || this->vertices[j].y < point.y && this->vertices[i].y > point.y;
            bool check_intersection = is_between && (this->vertices[i].x + (point.y - this->vertices[i].y) / (this->vertices[j].y - this->vertices[i].y) * (this->vertices[j].x - this->vertices[i].x) < point.x);
            if (check_intersection){
                result = !result;
            }
            j = i;
        }
        return result;
    }
};

class PolygonField{//class for group of Polygons
private:
    std::vector<Polygon> field;//array of Polygons
    int num_pn = 0;//length of array
public:
    std::vector<Polygon> get_field(){//return array of Polygon
        return this->field;
    }
    int get_num_pn(){//return length of array
        return this->num_pn;
    }
    bool is_empty(){//check field for emptiness
        return num_pn == 0;
    }
    void print_field(){//print in console all Polygons by printing all of their points
        for(Polygon pn: this->field){
            pn.print_vertices();
        }
        std::cout << std::endl;
    };
    void input_polygon(Polygon pn){//add polygon in field
        this->field.push_back(pn);
        this->num_pn += 1;
    }
    bool is_polygon_in_field(Polygon polygon){//check if Polygon is already in field
        for(Polygon pn: this->field){
            if(pn.is_equal_polygon(polygon)){
                return true;
            }
        }
        return false;
    }
};

int sign(double a){//func for sign of int
    return a < 0 ? -1 : 1;
}

double abs(double a){//func for absolute value
    return a < 0 ? -1 * a : a;
}

bool is_intersected(Point a, Point b, Point c, Point d){//check if AB and CD is intersected? using vector multiplication for checking
    bool first = (sign((b.x - a.x) * (c.y - a.y) - (b.y - a.y)*(c.x - a.x)) != sign((b.x - a.x) * (d.y - a.y) - (b.y - a.y)*(d.x - a.x)));
    bool second = (sign((c.x - d.x) * (a.y - d.y) - (c.y - d.y)*(a.x - d.x)) != sign((c.x - d.x) * (b.y - d.y) - (c.y - d.y)*(b.x - d.x)));
    return first and second;
}

Point intersection(Point a, Point b, Point c, Point d){//func to find point of intersection of AB and CD
    Point res{0, 0};
    if(is_intersected(a, b, c, d)){
        double z1 = abs((b.x - a.x) * (c.y - a.y) - (b.y - a.y)*(c.x - a.x));
        double z2 = abs((b.x - a.x) * (d.y - a.y) - (b.y - a.y)*(d.x - a.x) - (b.x - a.x) * (c.y - a.y) + (b.y - a.y)*(c.x - a.x));
        res.x = c.x + (d.x - c.x) * (z1 / z2);
        res.y = c.y + (d.y - c.y) * (z1 / z2);
        return res;
    } else {
        return {};//return blank point if not intersection
    }
}

int mult_vector(Point a, Point b, Point c){//checks the position of a point relative to A, using vector multiplication
    double ax, ay, bx, by;
    ax = b.x - a.x;
    ay = b.y - a.y;
    bx = c.x - a.x;
    by = c.y - a.y;
    if (ax * by - ay * bx < 0) {//more to left
        return -1;
    } else if(ax * by - ay * bx == 0 && bx*bx + by*by > ax*ax + ay*ay){//on one line
        return 0;
    } else{//more to right
        return 1;
    }
}

std::vector<Point> convert_intersections(std::vector<Point> points) {//convert final intersections to convex hull (for keeping traversal order)
    Point p0 = points[0];
    Point t = p0;
    for (Point p : points){//find starting point and next point
        if (p.x < p0.x || (p.x == p0.x && p.y < p0.y)){
            p0 = p;
        }
        if (p.x > t.x || (p.x == t.x && p.y > t.y)){
            t = p;
        }
    }
    std::vector<Point> hull;
    hull.push_back(p0);
    while (true) {
        for (Point p : points){
            if (mult_vector(p0, t, p) <= 0){
                t = p;
            }
        }
        if (t.x == hull[0].x and t.y == hull[0].y)
            break;
        else {
            p0 = t;
            hull.push_back(t);
        }
        t = p0;
    }
    return hull;
}

Polygon intersect_polygons(Polygon p1, Polygon p2){ //intersection of 2 Polygons
    Polygon result;
    bool check_p1_full_in = true;//parameter checking if polygon inside another
    bool check_p1_full_out = false;//parameter checking if polygon outside fully
    bool check_p2_full_in = true;//parameter checking if polygon inside another
    bool check_p2_full_out = false;//parameter checking if polygon outside fully
    std::vector<Point> intersection_points;
    std::vector<Point> p1_vertices = p1.get_vertices();
    std::vector<Point> p2_vertices = p2.get_vertices();
    int p1_length = p1.get_num_vertices();
    int p2_length = p2.get_num_vertices();
    if (p1_length==0){ // for blank polygons
        return p2;
    }
    if (p2_length==0){
        return p1;
    }
    if(p1.is_equal_polygon(p2)){//if polygons same
        return p1;
    }

    for(Point p: p1_vertices){//check points for their position
        bool point_in = p2.is_point_in(p) or p2.is_point_vertex(p);
        if (point_in){
            intersection_points.push_back(p);
        }
        check_p1_full_in = check_p1_full_in && point_in;
        check_p1_full_out = check_p1_full_out || point_in;
    }
    if (check_p1_full_in){//return first polygon if it fully in
        return p1;
    }
    for(Point p: p2_vertices){//check points for their position
        bool point_in = p1.is_point_in(p) or p1.is_point_vertex(p);
        if (point_in){
            intersection_points.push_back(p);
        }
        check_p2_full_in = check_p1_full_in && point_in;
        check_p2_full_out = check_p1_full_out || point_in;
    }
    if (check_p2_full_in){//return second polygon if it fully in
        return p2;
    }
    int b = p1_length - 1;
    for(int a = 0; a < p1_length; a++){
        int d = p2_length - 1;
        for(int c = 0; c < p2_length; c++){
            if(is_intersected(p1_vertices[a], p1_vertices[b], p2_vertices[c], p2_vertices[d])) {
                intersection_points.push_back(intersection(p1_vertices[a], p1_vertices[b], p2_vertices[c], p2_vertices[d]));
            }
            d = c;
        }
        b = a;
    }
    if (!check_p1_full_out && !check_p2_full_out && intersection_points.empty()){//return blank in case of no intersection
        return {};
    }
    std::vector<Point> res_points = convert_intersections(intersection_points);
    for(Point p: res_points){
        if(!result.is_point_vertex(p)){
            result.input_vertex(p);
        }
    }
    return result;
}

std::vector<Polygon> intersect_polygon_field(std::vector<Polygon> field){//intersecting polygons
    std::vector<Polygon> new_field;
    std::size_t n = field.size();
    if (n <= 1){//return 1 polygon in case if it only one
        return field;
    }
    Polygon intersected_pn;
    for(std::size_t i=0; i < n; i++){
        for(std::size_t j=i+1; j < n; j++){
            intersected_pn = intersect_polygons(field[i], field[j]);
            bool check = true;
            for(Polygon pn: new_field){
                check = check & !pn.is_equal_polygon(intersected_pn);
            }
            if(intersected_pn.get_num_vertices() > 0 && check){
                new_field.push_back(intersected_pn);
            }
        }
    }
    return new_field;
}
Polygon intersect_polygon_field_final(std::vector<Polygon> &field){//intersect until there is only one polygon left
    std::vector<Polygon> old_field;
    std::vector<Polygon> new_field = field;
    while(new_field.size() > 1){ // earlier I was checking on emptyness what a mess I am dumb heheha
        old_field = new_field;
        new_field = intersect_polygon_field(old_field);
    }
    return new_field[0];// old_field -> new_field ??
}

std::vector<Polygon> input_polygons(const std::string input){
    std::vector<Polygon> pn_field;
    std::size_t index=0;
    while(index != std::string::npos){
        Polygon pn;
        pn.input_from_file(input,index);
        if (pn.get_num_vertices() > 0){
            pn_field.push_back(pn);
        }
        index = find_key(input, find_key(input, index)+1);
    }
    return pn_field;
}
//think about realization class for Point
int main() {
    const std::string path = "";//полный путь к файлу
    std::string input = read_file(path)+" ";//switched here to open file only once
    std::vector<Polygon> pn_field = input_polygons(input);
    std::cout << "Starting Polygons:" << std::endl;
    for(Polygon pn: pn_field){
        pn.print_vertices();
    }
    std::cout << "Ended Polygons" << std::endl;
    Polygon pn_f = intersect_polygon_field_final(pn_field);
    std::cout << std::endl;
    std::cout << "Result Polygon:" << std::endl;
    pn_f.print_vertices();
    return 0;
}