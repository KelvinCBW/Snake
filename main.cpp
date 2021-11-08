#include <SFML/Graphics.hpp>
#include "src/UI/Renderer.cpp"
#include "src/UI/Renderer.h"
#include "src/Logic/GameState.cpp"
#include "src/Logic/GameState.h"
#include <windows.h>
#include <iostream>

const int windowWidth = 800;
const int windowHeight = 600;
int main() {
    sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "My window");
    Renderer render(&window, windowHeight, windowWidth);
    GameState state;
    sf::Clock clock;
    float accumulatedTime = 0.f;
    float frameTime = 1.f / 3.f;
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) window.close();
            if (event.type == sf::Event::KeyPressed) {
                switch (event.key.code) {
                    case sf::Keyboard::Up:
                        state.setDirection(Direction::UP);
                        break;
                    case sf::Keyboard::Down:
                        state.setDirection(Direction::DOWN);
                        break;
                    case sf::Keyboard::Left:
                        state.setDirection(Direction::LEFT);
                        break;
                    case sf::Keyboard::Right:
                        state.setDirection(Direction::RIGHT);
                        break;
                }
            }
        }
        window.clear();
        sf::Time time = clock.getElapsedTime();
        if (time.asSeconds() - accumulatedTime > frameTime) {
            accumulatedTime += frameTime;
            state.update();
        }
        render.draw(state);
        window.display();
    }

    return 0;
}