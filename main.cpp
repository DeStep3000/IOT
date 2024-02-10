#include <iostream>
#include <vector>

struct Point {
    double x, y;
};

class Polygon{
private:
    std::vector<Point> vertices;
public:
    Polygon(){} //using standart
    std::vector<Point> get_vertices(){
        return this->vertices;
    }
    void print_vertices(){
        for(Point p: this->vertices){
            std::cout << p.x << " " << p.y << "\t";
            std::cout << "\n";
        }
    }
    void add_vertex(Point point){
        this->vertices.push_back(point);
    }
};

int main() {
    Polygon pn1;
    Point a{2, 3};
    Point b{3, 4};
    pn1.add_vertex(a);
    pn1.add_vertex(b);
    pn1.print_vertices();
    std::cout << "Hello, World!" << std::endl;
    return 0;
}
