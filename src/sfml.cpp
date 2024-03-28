#include <SFML/Graphics.hpp>

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML");

    // Создание линии для оси X
    sf::VertexArray xAxis(sf::Lines, 2);
    xAxis[0].position = sf::Vector2f(0, window.getSize().y);
    xAxis[1].position = sf::Vector2f(window.getSize().x, window.getSize().y);
    xAxis[0].color = sf::Color::Black;
    xAxis[1].color = sf::Color::Black;

    // Создание линии для оси Y
    sf::VertexArray yAxis(sf::Lines, 2);
    yAxis[0].position = sf::Vector2f(0, window.getSize().y);
    yAxis[1].position = sf::Vector2f(0, 0);
    yAxis[0].color = sf::Color::Black;
    yAxis[1].color = sf::Color::Black;

    // Создание линий для координатной сетки
    sf::VertexArray gridLines(sf::Lines);
    const int step = 50; // Шаг сетки
    for (int i = step; i <= window.getSize().x; i += step) {
        gridLines.append(sf::Vertex(sf::Vector2f(i, 0), sf::Color(200, 200, 200)));
        gridLines.append(sf::Vertex(sf::Vector2f(i, window.getSize().y), sf::Color(200, 200, 200)));
    }
    for (int i = step; i <= window.getSize().y; i += step) {
        gridLines.append(sf::Vertex(sf::Vector2f(0, i), sf::Color(200, 200, 200)));
        gridLines.append(sf::Vertex(sf::Vector2f(window.getSize().x, i), sf::Color(200, 200, 200)));
    }
// Создание первого треугольника
    sf::ConvexShape triangle1;
    triangle1.setPointCount(3);
    triangle1.setPoint(0, sf::Vector2f(200, 100));
    triangle1.setPoint(1, sf::Vector2f(100, 300));
    triangle1.setPoint(2, sf::Vector2f(300, 300));
    triangle1.setFillColor(sf::Color::Red);

    // Создание второго треугольника
    sf::ConvexShape triangle2;
    triangle2.setPointCount(3);
    triangle2.setPoint(0, sf::Vector2f(400, 400));
    triangle2.setPoint(1, sf::Vector2f(600, 400));
    triangle2.setPoint(2, sf::Vector2f(600, 200));
    triangle2.setFillColor(sf::Color::Blue);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear(sf::Color::White);

        window.draw(gridLines);

        window.draw(xAxis);

        window.draw(yAxis);
        window.draw(triangle1);
        window.draw(triangle2);
        window.display();
    }

    return 0;
}
