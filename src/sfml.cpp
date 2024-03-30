#include <SFML/Graphics.hpp>
#include <filesystem>
#include <vector>
#include "sfml.h"
#include "polygon.h"

// Convert Point object to sf::Vector2f
sf::Vector2f Picture::convertToPoint(const Point &p) {
    return sf::Vector2f(static_cast<float>(p.x), static_cast<float>(p.y));
}

// Calculate scaling factor based on initial and final vertices
float Picture::scale(std::vector<Polygon> start_vertices, std::vector<Point> final_vertices) {
    // Find maximum x and y coordinates
    double maxX = 0.0f, maxY = 0.0f;
    for (Polygon pol: start_vertices) {
        std::vector<Point> points = pol.get_vertices();
        for (const auto &point: points) {
            maxX = std::max(point.x, maxX);
            maxY = std::max(point.y, maxY);
        }
    }
    for (const auto &point: final_vertices) {
        maxX = std::max(point.x, maxX);
        maxY = std::max(point.y, maxY);
    }

    // Choose the minimum scaling factor
    double scaleFactor = std::min(width / maxX, height / maxY);
    return scaleFactor;
}

// Draw a polygon with specified vertices, color, and outline color
sf::ConvexShape Picture::draw_polygon(std::vector<Point> vertices, sf::Color color, sf::Color tick) {
    std::vector<sf::Vector2f> arbitraryPoints;

    // Convert points to sf::Vector2f
    for (const auto &point: vertices) {
        arbitraryPoints.push_back(Picture::convertToPoint(point));
    }

    // Window dimensions
    double windowWidth = static_cast<double>(width);
    double windowHeight = static_cast<double>(height);

    // Create the polygon shape
    sf::ConvexShape polygon;
    polygon.setPointCount(arbitraryPoints.size());
    for (size_t i = 0; i < arbitraryPoints.size(); ++i) {
        float scaledX = arbitraryPoints[i].x * all_scale - ScaleMove;
        float scaledY = windowHeight - arbitraryPoints[i].y * all_scale - ScaleMove;
        polygon.setPoint(i, sf::Vector2f(scaledX, scaledY));
    }
    polygon.setFillColor(color);  // Polygon color
    polygon.setOutlineThickness(2);
    polygon.setOutlineColor(tick);  // Outline color
    return polygon;
}

// Draw gridlines with specified step size
sf::VertexArray Picture::draw_gridlines(int step) {
    sf::VertexArray gridLines(sf::Lines);
    for (int i = step; i <= width; i += step) {
        gridLines.append(sf::Vertex(sf::Vector2f(i, 0), sf::Color(200, 200, 200)));
        gridLines.append(sf::Vertex(sf::Vector2f(i, height), sf::Color(200, 200, 200)));
    }
    for (int i = step; i <= height; i += step) {
        gridLines.append(sf::Vertex(sf::Vector2f(0, i), sf::Color(200, 200, 200)));
        gridLines.append(sf::Vertex(sf::Vector2f(width, i), sf::Color(200, 200, 200)));
    }
    return gridLines;
}

// Draw the window with initial and final vertices
void Picture::draw_window(std::vector<Polygon> start_vertices, std::vector<Point> final_vertices) {
    sf::RenderWindow window(sf::VideoMode(width, height), "Scaled Polygon");

    // Get the path to the executable
    std::string executablePath = std::filesystem::path(__FILE__).parent_path().string();
    std::string imagePath = executablePath + "/icon.png";

    // Load image for window icon
    sf::Image icon;
    if (!icon.loadFromFile(imagePath)) {}
    window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());

    int step = 50;

    this->all_scale = Picture::scale(start_vertices, final_vertices);

    std::vector<sf::ConvexShape> start_poligons;
    for (Polygon pol: start_vertices) {
        start_poligons.push_back(draw_polygon(pol.get_vertices(), sf::Color(172, 225, 175), sf::Color::Blue));
    }

    sf::ConvexShape final_polygon = Picture::draw_polygon(final_vertices, sf::Color(255, 165, 0), sf::Color::Black);
    sf::VertexArray gridlines = Picture::draw_gridlines(step);

    // Main program loop
    while (window.isOpen()) {
        // Event handling
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // Rendering
        window.clear(sf::Color::White);
        window.draw(gridlines);
        for (sf::ConvexShape polygon: start_poligons) {
            window.draw(polygon);
        }
        window.draw(final_polygon);
        window.display();
    }
}
