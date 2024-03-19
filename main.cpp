#include <iostream>
#include <cfloat>//import machine epsilon for double
#include <cmath>
#include <vector>
#include "readfile.h"

// Daniel works here
const double eps = 1000*DBL_EPSILON; //needed for comparing double about 2,2204460492503131e-013

// Point and operators
struct Point {
    double x, y;
};//struct for points in format x and y
Point operator + (const Point& p1, const Point& p2){
    return Point{p1.x + p2.x, p1.y + p2.y};
}
Point& operator += (Point& p1, const Point& p2){
    p1 = Point{p1.x + p2.x, p1.y + p2.y};
    return p1;
}
Point operator - (const Point& p1, const Point& p2){
    return Point{p1.x - p2.x, p1.y - p2.y};
}
Point operator * (const double a, const Point& p2){
    return Point{a * p2.x, a * p2.y};
}
double operator * (const Point& p1, const Point& p2){
    return p1.x * p2.x + p1.y * p2.y;
}
double operator ^ (const Point& p1, const Point& p2){
    return p1.x * p2.y - p1.y * p2.x;
}
Point operator - (Point p1){
    return Point{-p1.x, -p1.y};
}
bool operator == (const Point& p1, const Point& p2){
    return -eps < (p1-p2).x && (p1-p2).x < eps && -eps < (p1-p2).y && (p1-p2).y < eps;
}
bool operator != (const Point& p1, const Point& p2){
    return !(p1 == p2);
}
bool operator > (const Point& p1, const Point& p2){ // first by x then by y
    return (p1.x > p2.x) || (-eps < (p1-p2).x && (p1-p2).x < eps) && (p1.y > p2.y);
}
bool operator < (const Point& p1, const Point& p2){ // first by x then by y
    return (p1.x < p2.x) || (-eps < (p1-p2).x && (p1-p2).x < eps) && (p1.y < p2.y);
}
bool operator <= (const Point& p1, const Point& p2){ // first by x then by y
    return !(p1 > p2);
}
bool operator >= (const Point& p1, const Point& p2){ // first by x then by y
    return !(p1 < p2);
}
std::ostream& operator << (std::ostream& stream, const Point& p){
    stream << p.x << " " << p.y;
    return stream;
}
double length (Point a){//func for length
    return sqrt(pow(a.x, 2)+pow(a.y, 2));
}
int sign(double a){//func for sign of int
    return a < 0 ? -1 : 1;
}

double abs(double a){//func for absolute value
    return a < 0 ? -1 * a : a;
}

//Polygon CLASS
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
            std::cout << p << "\t";
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
        for(Point p: this->vertices){
            if(p == point){
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
    void input_from_file(const std::string &input, std::size_t index){//add vertices in Polygon from file using input_from_array
        std::vector<double> coordinates = get_coords(input, index);
        this->input_from_array(coordinates);
    }
    bool is_point_in(Point point){ //checking is point inside polygon
        bool result = false;
        int j = this->num_vertices - 1;
        for(int i = 0; i < this->num_vertices; i++){
            /*if (-eps < this->vertices[i].y - this->vertices[j].y && this->vertices[i].y - this->vertices[j].y < eps && -eps < this->vertices[i].y - point.y && this->vertices[i].y - point.y < eps){
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

    bool is_point_in_f(Point p){ //checking is point inside polygon
        return is_point_in(Point{p.x, p.y-eps}) || is_point_in(Point{p.x, p.y+eps});
    }

    bool is_point_in_2(Point p){//this method use angle sum
        double result = 0;
        int j = this->num_vertices - 1;
        for(int i = 0; i < this->num_vertices; i++){
            double vec_mult = (this->vertices[i] - p) ^ (this->vertices[j] - p);
            if(vec_mult > 0){
                result += acos(((this->vertices[i] - p) * (this->vertices[j] - p)) / length(this->vertices[i] - p) / length(this->vertices[j] - p));
            } else if(vec_mult < 0) {
                result -= acos(((this->vertices[i] - p) * (this->vertices[j] - p)) / length(this->vertices[i] - p) / length(this->vertices[j] - p));
            }
        }
        /*if(!(-eps < result / M_PI && result / M_PI < eps)){
            return true;
        }*/
        result = round(result / 2);
        if (-eps < result && result < eps){
            return false;
        }
        return true;
    }
};


//PolygonField class
class PolygonField{//class for group of Polygons
private:
    std::vector<Polygon> field;//array of Polygons
    std::size_t num_pn = 0;//length of array
public:
    std::vector<Polygon> get_field(){//return array of Polygon
        return this->field;
    }
    std::size_t get_num_pn(){//return length of array
        return this->num_pn;
    }
    bool is_empty(){//check field for emptiness
        return num_pn == 0;
    }
    void print_field(){//print in console all Polygons by printing all of their points
        std::cout << "Polygon field(" << this->num_pn << "):" << std::endl;
        for(Polygon pn: this->field){
            pn.print_vertices();
        }
        std::cout << std::endl;
    };
    void input_polygon(const Polygon pn){//add polygon in field
        this->field.push_back(pn);
        this->num_pn += 1;
    }
    bool is_polygon_in_field(const Polygon& polygon){//check if Polygon is already in field
        for(Polygon pn: this->field){
            if(pn.is_equal_polygon(polygon)){
                return true;
            }
        }
        return false;
    }
    bool is_intersected(Point a, Point b, Point c, Point d){//check if AB and CD is intersected? using vector multiplication for checking
        double mult1 = (b - a) ^ (c - a);
        double mult2 = (b - a) ^ (d - a);
        bool first = (sign(mult1) != sign(mult2));
        mult1 = (c - d) ^ (a - d);
        mult2 = (c - d) ^ (b - d);
        bool second = (sign(mult1) != sign(mult2));
        return first && second;
    }

    std::vector<Point> intersection(Point a, Point b, Point c, Point d){//func to find point of intersection of AB and CD ПЕРЕПИСАТЬ
        Point res{0, 0};
        std::vector<Point> result;
        if(is_intersected(a, b, c, d)){
            double z1 = abs((b - a) ^ (c - a));
            double z2 = abs(((b - a) ^ (d - a)) - ((b - a) ^ (c - a)));
            res = c + (z1 / z2) * (d - c);
            result.push_back(res);
            return result;
        }
        return result;
    }

    int mult_vector(Point a, Point b, Point c){//checks the position of a point relative to A, using vector multiplication
        if (((b - a) ^ (c - a)) < 0) {//more to left
            return -1;
        } else if(((b - a) ^ (c - a)) == 0 && (c - a) * (c - a) > (b - a) * (b - a)){//on one line
            return 0;
        } else{//more to right
            return 1;
        }
    }

    std::vector<Point> convert_intersections(std::vector<Point> points) {//convert final intersections to convex hull (for keeping traversal order)
        Point p0 = points[0];
        Point t = p0;
        for (Point p : points){//find starting point and next point
            if (p < p0){
                p0 = p;
            }
            if (p > t){
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
            if (t == hull[0])
                break;
            else {
                p0 = t;
                hull.push_back(t);
            }
            t = p0;
        }
        return hull;
    }

    Polygon intersect_polygons(Polygon& p1, Polygon& p2){ //intersection of 2 Polygons
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
            bool point_in = p2.is_point_in_f(p) || p2.is_point_vertex(p);
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
            bool point_in = p1.is_point_in_f(p) || p1.is_point_vertex(p);
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
                for(Point p: intersection(p1_vertices[a], p1_vertices[b], p2_vertices[c], p2_vertices[d])) {
                    intersection_points.push_back(p);
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

    void intersect_polygon_field(){//intersecting polygons
        std::vector<Polygon> new_field;
        std::size_t n = this->num_pn;
        Polygon intersected_pn;
        if (n >= 2){
            for(std::size_t i=0; i < n; i++){
                for(std::size_t j=i+1; j < n; j++){
                    intersected_pn = intersect_polygons(this->field[i], this->field[j]);
                    bool check = true;
                    if(!intersected_pn.is_empty()){
                        for(Polygon pn: new_field){
                            check = check & !pn.is_equal_polygon(intersected_pn);
                        }
                        if(check){
                            new_field.push_back(intersected_pn);
                        }
                    }
                }
            }
            this->field = new_field;
            this->num_pn = new_field.size();
        }
    }
    Polygon intersect_polygon_field_final(){//intersect until there is only one polygon left
        if(this->num_pn == 0){
            return {};
        }
        std::vector<Polygon> old_field;
        while(this->num_pn > 1){
            old_field = this->field;
            this->intersect_polygon_field();
        }
        if(this->num_pn == 0){
            return old_field[0];
        }
        return this->field[0];
    }


    void input_polygons(const std::string &input){
        std::size_t index=find_key(input,0);
        while(index != std::string::npos){
            Polygon pn;
            pn.input_from_file(input,index);
            if (!pn.is_empty()){
                this->input_polygon(pn);
            }
            index = find_key(input, find_key(input,index)+3);
        }
    }
};


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