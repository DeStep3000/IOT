#include <iostream>
#include <vector>

struct Point {
    double x, y;
};

class Polygon{
private:
    std::vector<Point> vertices; // array of vertex
    int num_vertices = 0; // lengt of array
public:
    Polygon(){} //using standart
    std::vector<Point> get_vertices(){
        return this->vertices;
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
    bool is_point_in(Point point){ //checking is point in polygon (rewrite because of points on edge
        bool result = false;
        int j = this->num_vertices - 1;
        for(int i = 0; i < this->num_vertices - 1; i++){
            if ( (this->vertices[i].y < point.y && this->vertices[j].y >= point.y || this->vertices[j].y < point.y && this->vertices[i].y >= point.y) &&
                 (this->vertices[i].x + (point.y - this->vertices[i].y) / (this->vertices[j].y - this->vertices[i].y) * (this->vertices[j].x - this->vertices[i].x) < point.x) )
                result = !result;
            j = i;
        }
        return result;
    }
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
    Point check_point{9, 4};
    std::cout << pn1.is_point_in(check_point) << std::endl;
    return 0;
}
