#include <SFML/Graphics.hpp>
#include <vector>
#include "sfml.h"
#include "polygon.h"

sf::Vector2f Picture::convertToPoint(const Point &p) {
    return sf::Vector2f(static_cast<float>(p.x), static_cast<float>(p.y));
}

float Picture::scale(int width, int height, std::vector<sf::Vector2f> arbitraryPoints) {
    // Находим масштабные коэффициенты для x и y
    float maxX = 0.0f, maxY = 0.0f;
    for (const auto &point: arbitraryPoints) {
        maxX = std::max(maxX, point.x);
        maxY = std::max(maxY, point.y);
    }

    // Выбираем минимальный масштабный коэффициент
    float scaleFactor = std::min(width / maxX, height / maxY);
    return scaleFactor;
}

sf::ConvexShape Picture::draw_polygon(int width, int height, std::vector<Point> vertices) {
    std::vector<sf::Vector2f> arbitraryPoints;

    for (const auto &point: vertices) {
        arbitraryPoints.push_back(Picture::convertToPoint(point));
    }

    // Размеры окна
    float windowWidth = static_cast<float>(width);
    float windowHeight = static_cast<float>(height);

    // Выбираем минимальный масштабный коэффициент
    float scaleFactor = Picture::scale(width, height, arbitraryPoints);

    // Создаем форму многоугольника
    sf::ConvexShape polygon;
    polygon.setPointCount(arbitraryPoints.size());
    for (size_t i = 0; i < arbitraryPoints.size(); ++i) {
        float scaledX = arbitraryPoints[i].x * scaleFactor;
        float scaledY = (windowHeight - arbitraryPoints[i].y) * scaleFactor;
        polygon.setPoint(i, sf::Vector2f(scaledX, scaledY));
    }
    polygon.setFillColor(sf::Color::Green); // Цвет многоугольника
    return polygon;
}


void Picture::draw_window(std::vector<Point> vertices, int x, int y) {
    sf::RenderWindow window(sf::VideoMode(x, y), "Scaled Polygon");

    int width = window.getSize().x;
    int height = window.getSize().y;

    sf::ConvexShape polygon = Picture::draw_polygon(width, height, vertices);
    // Основной цикл программы
    while (window.isOpen()) {
        // Обработка событий
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // Отрисовка
        window.clear();
        window.draw(polygon);
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
//};
