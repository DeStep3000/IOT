#include <SFML/Graphics.hpp>
#include <iostream>

class CoordinateSystem {
private:
    sf::RenderWindow window;
    sf::View view;
    sf::Font font;
    float scale;
    sf::Vector2f offset;
public:
    CoordinateSystem() : window(sf::VideoMode(800, 600), "SFML Coordinate System"), scale(20.0f), offset(0.0f, 0.0f) {
        font.loadFromFile("arial.ttf");
        view = window.getDefaultView();
    }

    void drawAxes() {
        sf::VertexArray x_axis(sf::Lines, 2);
        x_axis[0].position = sf::Vector2f(-view.getSize().x / 2, 0);
        x_axis[1].position = sf::Vector2f(view.getSize().x / 2, 0);
        x_axis[0].color = sf::Color::Black;
        x_axis[1].color = sf::Color::Black;
        window.draw(x_axis);

        sf::VertexArray y_axis(sf::Lines, 2);
        y_axis[0].position = sf::Vector2f(0, -view.getSize().y / 2);
        y_axis[1].position = sf::Vector2f(0, view.getSize().y / 2);
        y_axis[0].color = sf::Color::Black;
        y_axis[1].color = sf::Color::Black;
        window.draw(y_axis);

        drawAxisLabels();
    }

    void drawAxisLabels() {
        sf::Text zero("0", font, 12);
        zero.setPosition(-view.getSize().x / 2 + 5, view.getSize().y / 2 - 15);
        window.draw(zero);

        for (int i = -view.getSize().x / 2 + scale; i < view.getSize().x / 2; i += scale) {
            sf::Text label(std::to_string(i / scale), font, 12);
            label.setPosition(i + 5, view.getSize().y / 2 - 15);
            window.draw(label);
        }

        for (int i = -view.getSize().y / 2 + scale; i < view.getSize().y / 2; i += scale) {
            if (i != 0) {
                sf::Text label(std::to_string(-i / scale), font, 12);
                label.setPosition(-view.getSize().x / 2 + 5, i - 15);
                window.draw(label);
            }
        }
    }

    void handleEvents() {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
            else if (event.type == sf::Event::MouseWheelScrolled) {
                if (event.mouseWheelScroll.delta > 0)
                    scale *= 1.1f;
                else if (event.mouseWheelScroll.delta < 0)
                    scale *= 0.9f;
            }
        }
    }

    void update() {
        view.setCenter(offset);
        view.setSize(sf::Vector2f(window.getSize().x * scale, window.getSize().y * scale));
        window.setView(view);
    }

    void run() {
        while (window.isOpen()) {
            window.clear(sf::Color::White);

            handleEvents();
            update();
            drawAxes();

            window.display();
        }
    }
};

int main() {
    CoordinateSystem cs;
    cs.run();

    return 0;
}
