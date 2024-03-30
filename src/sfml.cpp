#include <SFML/Graphics.hpp>
#include <filesystem>
#include <vector>
#include "sfml.h"
#include "polygon.h"


sf::Vector2f Picture::convertToPoint(const Point &p) {
    return sf::Vector2f(static_cast<float>(p.x), static_cast<float>(p.y));
}

float Picture::scale(std::vector<Polygon> start_vertices, std::vector<Point> final_vertices) {
    // Находим масштабные коэффициенты для x и y
    double maxX = 0.0f, maxY = 0.0f;
    for (Polygon pol: start_vertices){
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

    // Выбираем минимальный масштабный коэффициент
    double scaleFactor = std::min(width / maxX, height / maxY);
    return scaleFactor;
}

sf::ConvexShape Picture::draw_polygon(std::vector<Point> vertices, sf::Color color) {
    std::vector<sf::Vector2f> arbitraryPoints;

    for (const auto &point: vertices) {
        arbitraryPoints.push_back(Picture::convertToPoint(point));
    }

    // Размеры окна
    double windowWidth = static_cast<double>(width);
    double windowHeight = static_cast<double>(height);


    // Создаем форму многоугольника
    sf::ConvexShape polygon;
    polygon.setPointCount(arbitraryPoints.size());
    for (size_t i = 0; i < arbitraryPoints.size(); ++i) {
        float scaledX = arbitraryPoints[i].x * all_scale - ScaleMove;
        float scaledY = windowHeight - arbitraryPoints[i].y * all_scale - ScaleMove;
        polygon.setPoint(i, sf::Vector2f(scaledX, scaledY));
    }
    polygon.setFillColor(color); // Цвет многоугольника
    return polygon;
}

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


void Picture::draw_window(std::vector<Polygon> start_vertices, std::vector<Point> final_vertices) {
    sf::RenderWindow window(sf::VideoMode(width, height), "Scaled Polygon");

    // Получение пути к исполняемому файлу
    std::string executablePath = std::filesystem::path(__FILE__).parent_path().string();
    std::string imagePath = executablePath + "/icon.png";

    // Загрузка изображения из файла по относительному пути
    sf::Image icon;
    if (!icon.loadFromFile(imagePath)) {}
    window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());

    int step = 50;

    this->all_scale = Picture::scale(start_vertices, final_vertices);

    std::vector<sf::ConvexShape> start_poligons;
    for (Polygon pol: start_vertices) {
        start_poligons.push_back(draw_polygon(pol.get_vertices(), sf::Color(172, 225, 175)));
    }

    sf::ConvexShape final_polygon = Picture::draw_polygon(final_vertices, sf::Color(255, 165, 0));
    final_polygon.setOutlineThickness(2);
    final_polygon.setOutlineColor(sf::Color::Black);
    sf::VertexArray gridlines = Picture::draw_gridlines(step);
    // Основной цикл программы
    while (window.isOpen()) {
        // Обработка событий
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // Отрисовка
        window.clear(sf::Color::White);
        window.draw(gridlines);
        for (sf::ConvexShape polygon: start_poligons) {
            window.draw(polygon);
        }
        window.draw(final_polygon);
        window.display();
    }
}


//int main() {
//    // Произвольные координаты точек
//    std::vector<Point> Points = {
//            {0,      0},
//            {100.5f, 200.7f},
//            {300.3f, 100.9f},
//            {500.1f, 400.8f},
//            {700.4f, 300.6f},
//            {800,    600}
//    };
//    Picture picture;
//    picture.draw_window(Points, 800, 600);
//}
