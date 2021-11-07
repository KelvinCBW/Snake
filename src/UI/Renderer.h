#include <SFML/Graphics.hpp>
#include "../Logic/GameState.h"

class Renderer{
public:
	Renderer(sf::RenderWindow* window);
	void draw(GameState state);
	
private:
	sf::RenderWindow *mainWindow;
};