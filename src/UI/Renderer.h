#ifndef RENDERER_H
#define RENDERER_H

#include <SFML/Graphics.hpp>
#include "../Logic/GameState.h"

class Renderer{
public:
	Renderer(sf::RenderWindow* window, int height, int width);
	void draw(GameState state);
	
private:
	sf::RenderWindow *mainWindow;
	int windowHeight;
	int windowWidth;

	sf::RectangleShape drawRect(Tile t, float blockWidth, float blockHeight);
	sf::Text drawText();
};

#endif