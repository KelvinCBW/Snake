#include <SFML/Graphics.hpp>
#include "Renderer.h"
#include <iostream>


Renderer::Renderer(sf::RenderWindow* mainWindow, int height, int width) {
	this->mainWindow = mainWindow;
	windowHeight = height;
	windowWidth = width;
}

void Renderer::draw(GameState state) {
	int xBlocks = state.getHeight();
	int yBlocks = state.getWidth();
	float blockWidth = (float)mainWindow->getSize().x / xBlocks;
	float blockHeight = (float)mainWindow->getSize().y / yBlocks;
	vector<vector<Tile>> board = state.getBoard();
	for (int i = 0; i < board.size(); i++) {
		for (int j = 0; j < board[i].size(); j++) {
			sf::RectangleShape rect = drawRect(board[i][j], blockWidth, blockHeight);
			rect.setPosition((float)j * blockWidth, (float)i * blockHeight);
			mainWindow->draw(rect);
		}
	}
}

sf::RectangleShape Renderer::drawRect(Tile t, float blockWidth, float blockHeight) {
	sf::RectangleShape rect(sf::Vector2f(blockWidth, blockHeight));
	switch (t) {
	case Tile::BODY:
		rect.setFillColor(sf::Color::Green);
		break;
	case Tile::HEAD:
		rect.setFillColor(sf::Color::Yellow);
		break;
	case Tile::FOOD:
		rect.setFillColor(sf::Color::Magenta);
		break;
	case Tile::EMPTY:
		rect.setFillColor(sf::Color::Black);
		break;
	}
	return rect;
}