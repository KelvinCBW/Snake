#include <SFML/Graphics.hpp>
#include "Renderer.h"
#include <iostream>


const int WINDOW_WIDTH = 500;
const int WINDOW_HEIGHT = 500;

Renderer::Renderer(sf::RenderWindow* mainWindow) {
	this->mainWindow = mainWindow;
}

void Renderer::draw(GameState state) {

}