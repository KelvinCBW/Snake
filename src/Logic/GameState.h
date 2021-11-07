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
	bool over;
	
	bool isCollision();
	bool isSelfCollision();
	bool isWallCollision();
	pair<int, int> getNextLocation();
	void move();
};



