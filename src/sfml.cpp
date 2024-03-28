#include <SFML/Graphics.hpp>
#include <vector>

int main()
{
    // Создаем окно размером 800x600
    sf::RenderWindow window(sf::VideoMode(800, 600), "Scaled Polygon in First Quadrant");

    // Произвольные координаты точек
    std::vector<sf::Vector2f> arbitraryPoints = {
            {0, 0},
            {100.5f, 200.7f}, // Пример дробных координат точек
            {300.3f, 100.9f},
            {500.1f, 400.8f},
            {700.4f, 300.6f},
            {800, 600}
    };

    // Размеры окна
    float windowWidth = static_cast<float>(window.getSize().x);
    float windowHeight = static_cast<float>(window.getSize().y);

    // Находим масштабные коэффициенты для x и y
    float maxX = 0.0f, maxY = 0.0f;
    for (const auto &point : arbitraryPoints)
    {
        maxX = std::max(maxX, point.x);
        maxY = std::max(maxY, point.y);
    }

    // Выбираем минимальный масштабный коэффициент
    float scaleFactor = std::min(windowWidth / maxX, windowHeight / maxY);

    // Создаем форму многоугольника
    sf::ConvexShape polygon;
    polygon.setPointCount(arbitraryPoints.size());
    for (size_t i = 0; i < arbitraryPoints.size(); ++i)
    {
        float scaledX = arbitraryPoints[i].x * scaleFactor;
        float scaledY = (windowHeight - arbitraryPoints[i].y) * scaleFactor;
        polygon.setPoint(i, sf::Vector2f(scaledX, scaledY));
    }
    polygon.setFillColor(sf::Color::Green); // Цвет многоугольника

    // Основной цикл программы
    while (window.isOpen())
    {
        // Обработка событий
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // Отрисовка
        window.clear();
        window.draw(polygon);
        window.display();
    }

    return 0;
}
