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
    void add_vertex(Point point){
        this->vertices.push_back(point);
        this->num_vertices += 1;
    }
    bool is_point_in(Point point){ //checking is point inside polygon
        bool result = false;
        int j = this->num_vertices - 1;
        for(int i = 0; i < this->num_vertices - 1; i++){
            if (-eps < this->vertices[i].y - this->vertices[j].y < eps && -eps < this->vertices[i].y - point.y < eps){
                return true;
            }
            bool is_between = this->vertices[i].y < point.y && this->vertices[j].y >= point.y || this->vertices[j].y < point.y && this->vertices[i].y >= point.y;
            bool check_intersection = is_between && this->vertices[i].x + (point.y - this->vertices[i].y) / (this->vertices[j].y - this->vertices[i].y) * (this->vertices[j].x - this->vertices[i].x) < point.x;
            if (check_intersection){
                result = !result;
            }
            j = i;
        }
        return result;
    }
};

Polygon intersect_polygons(Polygon p1, Polygon p2){ //future function for intersection
    Polygon result;
    bool check_p1_full_in = true;
    bool check_p1_full_out = false;
    bool check_p2_full_in = true;
    bool check_p2_full_out = false;
    std::vector<Point> p1_vertices = p1.get_vertices();
    std::vector<Point> p2_vertices = p2.get_vertices();
    std::vector<bool> p1_marks;
    std::vector<bool> p2_marks;
    for(Point p: p1_vertices){
        bool point_in = p2.is_point_in(p);
        p1_marks.push_back(point_in);
        check_p1_full_in = check_p1_full_in && point_in;
        check_p1_full_out = check_p1_full_out || point_in;
    }
    if (check_p1_full_in) {
        return p1;
    }
    for(Point p: p2_vertices){
        bool point_in = p1.is_point_in(p);
        p2_marks.push_back(point_in);
        check_p2_full_in = check_p1_full_in && point_in;
        check_p2_full_out = check_p1_full_out || point_in;
    }
    if (check_p2_full_in) {
        return p2;
    } else if (!check_p1_full_out && !check_p2_full_out){
        return {};
    }
    /*for(Point p: p1_vertices){
        int j = p1.get_num_vertices() - 1;
        for(int i = 0; i < p1.get_num_vertices() - 1; i++){
            if(p1_marks[i] && p1_marks[j]){
                result.add_vertex(p1_vertices[i]);
                result.add_vertex(p1_vertices[j]);
                j = i;
                continue;
            }
            int k = p2.get_num_vertices() - 1;
            for(int l = 0; l < p1.get_num_vertices() - 1; l++){
                if(p2_marks[i] && p2_marks[j]){
                    result.add_vertex(p2_vertices[i]);
                    result.add_vertex(p2_vertices[j]);
                    k = l;
                    continue;
                }
                k = l;
            }
            j = i;
        }
    }*/
    return p1;
};

int main() {
    Polygon pn1;
    Point a{1, 1};
    Point b{3, 5};
    Point c{9, 4};
    Point d{11, 3};
    Point e{6, 3};
    pn1.add_vertex(a);
    pn1.add_vertex(b);
    pn1.add_vertex(c);
    pn1.add_vertex(d);
    pn1.add_vertex(e);
    pn1.print_vertices();
    Point check_point{9, 3};
    std::cout << pn1.is_point_in(check_point) << std::endl;
    return 0;
}
