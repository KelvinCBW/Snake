#ifndef GAMESTATE_H
#define GAMESTATE_H


#include <SFML/Graphics.hpp>
#include <vector>
#include <utility>

using std::vector;
using std::pair;

enum Direction {UP, DOWN, LEFT, RIGHT};

enum Tile {EMPTY, HEAD, BODY, FOOD};

class GameState {
public:
	GameState();
	void update();
	void setDirection(Direction d);
	int getWidth();
	int getHeight();
	vector<vector<Tile>> getBoard();
	bool isOver();
private:
	vector<vector<Tile>> board;
	Direction dir;
	pair<int, int> head;
	vector<pair<int, int>> body;
	pair<int, int> food;
	bool over;
	
	void init();
	bool isCollision();
	bool isSelfCollision();
	bool isWallCollision();
	void updateBoard();
	pair<int, int> getNextLocation();
	void move();
	pair<int, int> spawnFood();
	bool isFoodInBody(int foodHeight, int foodWidth);
};

#endif

