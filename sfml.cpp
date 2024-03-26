#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>

int main() {
    sf::RenderWindow window(sf::VideoMode(400, 200), "SFML File Manager");

    sf::Font font;
//    if (!font.loadFromFile("arial.ttf")) {
//        std::cerr << "Ошибка загрузки шрифта." << std::endl;
//        return 1;
//    }

    sf::Text openFileText("Открыть файл", font, 24);
    openFileText.setPosition(50, 50);

    sf::Text createFileText("Создать файл", font, 24);
    createFileText.setPosition(50, 100);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
                    if (openFileText.getGlobalBounds().contains(mousePos)) {
                        std::ifstream file("example.txt");
                        if (file.is_open()) {
                            std::string line;
                            while (std::getline(file, line)) {
                                std::cout << line << std::endl;
                            }
                            file.close();
                        } else {
                            std::cerr << "Ошибка при открытии файла." << std::endl;
                        }
                    } else if (createFileText.getGlobalBounds().contains(mousePos)) {
                        std::ofstream file("example.txt");
                        if (file.is_open()) {
                            std::cout << "Файл успешно создан." << std::endl;
                            file.close();
                        } else {
                            std::cerr << "Ошибка при создании файла." << std::endl;
                        }
                    }
                }
            }
        }

        window.clear();
        window.draw(openFileText);
        window.draw(createFileText);
        window.display();
    }

    return 0;
}
