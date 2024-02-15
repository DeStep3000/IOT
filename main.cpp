#include <iostream>
#include <cfloat>//import machine epsilon for double
#include <vector>
#include "readfile.h"

struct Point {
    double x, y;
};

const double eps = DBL_EPSILON; //needed for comparing double

class Polygon{
private:
    std::vector<Point> vertices; // array of vertex
    int num_vertices = 0; // length of array
public:
    Polygon()= default; //using standart
    std::vector<Point> get_vertices(){
        return this->vertices;
    }
    int get_num_vertices(){
        return this->num_vertices;
    }
    void print_vertices(){
        for(Point p: this->vertices){
            std::cout << p.x << " " << p.y << "\t";
        }
        std::cout << "\n";
    }
    void input_vertex(Point point){
        this->vertices.push_back(point);
        this->num_vertices += 1;
    }
    void input_from_array(std::vector<double> coordinates){
        for(int i = 0; i < coordinates.size();){
            Point a{coordinates[i], coordinates[i+1]};
            this->input_vertex(a);
            i+=2;
        }
    }
    void input_from_file(const std::string path, std::size_t index=0){
        std::vector<double> coordinates = get_coords(path, index);
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

int sign(double a){
    return a < 0 ? -1 : 1;
}

double abs(double a){
    return a < 0 ? -1 * a : a;
}

bool is_intersected(Point a, Point b, Point c, Point d){
    bool first = (sign((b.x - a.x) * (c.y - a.y) - (b.y - a.y)*(c.x - a.x)) != sign((b.x - a.x) * (d.y - a.y) - (b.y - a.y)*(d.x - a.x)));
    bool second = (sign((c.x - d.x) * (a.y - d.y) - (c.y - d.y)*(a.x - d.x)) != sign((c.x - d.x) * (b.y - d.y) - (c.y - d.y)*(b.x - d.x)));
    return first and second;
}

Point intersection(Point a, Point b, Point c, Point d){
    Point res{0, 0};
    if(is_intersected(a, b, c, d)){
        double z1 = abs((b.x - a.x) * (c.y - a.y) - (b.y - a.y)*(c.x - a.x));
        double z2 = abs((b.x - a.x) * (d.y - a.y) - (b.y - a.y)*(d.x - a.x) - (b.x - a.x) * (c.y - a.y) + (b.y - a.y)*(c.x - a.x));
        res.x = c.x + (d.x - c.x) * (z1 / z2);
        res.y = c.y + (d.y - c.y) * (z1 / z2);
        return res;
    } else {
        return {};
    }
}

int mult_vector(Point a, Point b, Point c){
    double ax, ay, bx, by;
    ax = b.x - a.x;
    ay = b.y - a.y;
    bx = c.x - a.x;
    by = c.y - a.y;
    if (ax * by - ay * bx < 0) {
        return -1;
    } else if(ax * by - ay * bx == 0 && bx*bx + by*by > ax*ax + ay*ay){
        return 0;
    } else{
        return 1;
    }
}

std::vector<Point> convert_intersections(std::vector<Point> points) {
    Point p0 = points[0];
    Point t = p0;
    for (Point p : points){
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

Polygon intersect_polygons(Polygon p1, Polygon p2){ //future function for intersection
    Polygon result;
    bool check_p1_full_in = true;
    bool check_p1_full_out = false;
    bool check_p2_full_in = true;
    bool check_p2_full_out = false;
    std::vector<Point> intersection_points;
    std::vector<Point> p1_vertices = p1.get_vertices();
    std::vector<Point> p2_vertices = p2.get_vertices();
    int p1_length = p1.get_num_vertices();
    int p2_length = p2.get_num_vertices();
    std::vector<bool> p1_marks;
    std::vector<bool> p2_marks;
    for(Point p: p1_vertices){
        bool point_in = p2.is_point_in(p);
        if (point_in){
            intersection_points.push_back(p);
        }
        p1_marks.push_back(point_in);
        check_p1_full_in = check_p1_full_in && point_in;
        check_p1_full_out = check_p1_full_out || point_in;
    }
    if (check_p1_full_in){
        return p1;
    }
    for(Point p: p2_vertices){
        bool point_in = p1.is_point_in(p);
        if (point_in){
            intersection_points.push_back(p);
        }
        p2_marks.push_back(point_in);
        check_p2_full_in = check_p1_full_in && point_in;
        check_p2_full_out = check_p1_full_out || point_in;
    }
    if (check_p2_full_in){
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
    if (!check_p1_full_out && !check_p2_full_out && intersection_points.empty()){
        return result;
    }
    std::vector<Point> res_points = convert_intersections(intersection_points);
    for(Point p: intersection_points){
        result.input_vertex(p);
    }
    return result;
}

std::vector<Polygon> intersect_polygon_field(std::vector<Polygon> &field){
    std::vector<Polygon> new_field;
    std::size_t n = field.size();
    if (field.empty()){
        return{};
    }
    if (n == 1){
        return field;
    }
    Polygon intersected_pn;
    for(std::size_t i=0; i < n; i++){
        for(std::size_t j=0; j!=i && j < n; j++){
            intersected_pn = intersect_polygons(field[i], field[j]);
            if(intersected_pn.get_num_vertices() > 0){
                new_field.push_back(intersected_pn);
            }
        }
    }
    return new_field;
}
//think about realization class for Point and for Polygon Field
int main() {
    Polygon pn1;
    Polygon pn2;
    Polygon pn3;
    Polygon pn4;
    const std::string path = "C:\\Users\\dabho\\CLionProjects\\IOT\\input.txt";//полный путь к файлу
    pn1.input_from_file(path);
    std::size_t index = find_key(path, find_key(path)+3);//индекс первого вхождения 03 после предыдущего
    pn2.input_from_file(path, index);
    index = find_key(path, find_key(path, index)+3);
    pn3.input_from_file(path, index);
    index = find_key(path, find_key(path, index)+3);
    pn4.input_from_file(path, index);
    index = find_key(path, find_key(path, index)+3);
    std::vector<Polygon> pn_field{pn1, pn2, pn3, pn4};
    for(Polygon pn: pn_field){
        pn.print_vertices();
    }
    std::vector<Polygon> pn_field_2 = intersect_polygon_field(pn_field);
    std::cout << std::endl;
    for(Polygon pn: pn_field_2){
        pn.print_vertices();
    }
    return 0;
}
