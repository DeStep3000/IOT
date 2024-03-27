#ifndef IOT_POLYGON_H
#define IOT_POLYGON_H

#include <iostream>
#include <cfloat>//import machine epsilon for double
#include <cmath>//use only for second method (is_point_in2), that is not used right now
#include <vector>
#include "readfile.h"

const double eps = 1000*DBL_EPSILON; //needed for comparing double about 2,2204460492503131e-013

// Point and operators
struct Point {
    double x, y;
};//struct for points in format x and y
Point operator + (const Point& p1, const Point& p2);
Point& operator += (Point& p1, const Point& p2);
Point operator - (const Point& p1, const Point& p2);
Point operator * (const double a, const Point& p2);
double operator * (const Point& p1, const Point& p2);
double operator ^ (const Point& p1, const Point& p2);
Point operator - (Point p1);
bool operator == (const Point& p1, const Point& p2);
bool operator != (const Point& p1, const Point& p2);
bool operator > (const Point& p1, const Point& p2); // first by x then by y
bool operator < (const Point& p1, const Point& p2);
bool operator <= (const Point& p1, const Point& p2);
bool operator >= (const Point& p1, const Point& p2);
std::ostream& operator << (std::ostream& stream, const Point& p);
double length (Point a);
int sign(double a);


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
    void print_vertices();//print in console all vertices
    void input_vertex(Point point);//func to add vertex in Polygon
    bool is_point_vertex(Point point);//func to check if Point is already in Polygon
    bool classify(Point p0, Point p1, Point p2);
    bool is_point_on_edge(Point p);
    bool is_equal_polygon(Polygon pn);//func to check same Polygons or not
    void input_from_array(std::vector<double> coordinates);//add vertices in Polygon from array
    void input_from_file(const std::string &input, std::size_t index);//add vertices in Polygon from file using input_from_array
    bool is_point_in(Point point); //checking is point inside polygon
    bool is_point_in_f(Point p); //checking is point inside polygon
    bool is_point_in_2(Point p);//this method use angle sum
};

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
    void print_field();//print in console all Polygons by printing all of their points
    void input_polygon(const Polygon pn);//add polygon in field
    bool is_polygon_in_field(const Polygon& polygon);//check if Polygon is already in field
    bool is_intersected(Point a, Point b, Point c, Point d);//check if AB and CD is intersected? using vector multiplication for checking
    std::vector<Point> intersection(Point a, Point b, Point c, Point d);//func to find point of intersection of AB and CD
    int mult_vector(Point a, Point b, Point c);//checks the position of a point relative to A, using vector multiplication
    std::vector<Point> convert_intersections(std::vector<Point> points);//convert final intersections to convex hull (for keeping traversal order)
    Polygon intersect_polygons(Polygon& p1, Polygon& p2);//intersection of 2 Polygons
    void intersect_polygon_field();//intersecting polygons
    Polygon intersect_polygon_field_final();//intersect until there is only one polygon left
    void input_polygons(const std::string &input);
};

#endif
