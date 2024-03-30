#include "polygon.h"
#include "sfml.h"
#include "file_manager.h"

int main() {
    // Open a file dialog to select a file path
    const std::string path = FileManager::OpenFile();

    // Check if a file path was selected
    if (!path.empty()) {
        std::cout << "Selected file path: " << path << std::endl;
    } else {
        std::cout << "File selection canceled." << std::endl;
    }

    // Read and edit the content of the selected file
    std::string input = read_file(path);
    input = edit_file(input);

    // Create a PolygonField object and input polygons from the edited file content
    PolygonField pn_field;
    pn_field.input_polygons(input);

    // Print the polygon field
    pn_field.print_field();

    // Get the initial vertices from the polygon field
    std::vector<Polygon> start_vertices = pn_field.get_field();

    // Find the intersection of all polygons in the field and print the result
    Polygon res = pn_field.intersect_polygon_field_final();
    res.print_vertices();

    // Define window dimensions
    int width = 800;
    int height = 600;

    // Create a Picture object with the specified dimensions
    Picture picture(width, height);

    // Get the final vertices of the resulting polygon
    std::vector<Point> final_vertices = res.get_vertices();

    // Draw the window displaying the initial and final polygons
    picture.draw_window(start_vertices, final_vertices);

    return 0;
}