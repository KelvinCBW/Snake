#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "GameState.h"
#include <iostream>
#include <stdlib.h>
#include <utility>
#include <time.h>

const int HEIGHT = 20;
const int WIDTH = 20;

using std::vector;
using std::pair;
using std::make_pair;
using namespace std;
GameState::GameState() {
	init();
}

void GameState::init() {
	board = vector<vector<Tile>>(HEIGHT, vector<Tile>(WIDTH, Tile::EMPTY));
	srand(time(NULL));
	int startHeight = rand() % HEIGHT;
	int startWidth = rand() % WIDTH;
	head = pair<int, int>(startHeight, startWidth);
	body.clear();
	body.push_back(head);
	food = spawnFood();
	updateBoard();
	dir = Direction(rand() % 4);
	over = false;
}

void GameState::update() {
	if (isCollision()) {
		init();
	} 
	else {
		move();
	}
}

void GameState::setDirection(Direction d) {
	switch (d) {
	case Direction::DOWN:
		if (dir != Direction::UP) dir = d;
		break;
	case Direction::LEFT:
		if (dir != Direction::RIGHT) dir = d;
		break;
	case Direction::RIGHT:
		if (dir != Direction::LEFT) dir = d;
		break;
	case Direction::UP:
		if (dir != Direction::DOWN) dir = d;
		break;
	}
}

bool GameState::isCollision() {
	return isWallCollision() || isSelfCollision();
}

bool GameState::isSelfCollision() {
	pair<int, int> nextLocation = getNextLocation();
	return board[nextLocation.first][nextLocation.second] == Tile::BODY;
}

bool GameState::isWallCollision() {
	switch (dir) {
	case Direction::UP:
		return head.first == 0;
		break;
	case Direction::DOWN:
		return head.first == HEIGHT - 1;
		break;
	case Direction::LEFT:
		return head.second == 0;
		break;
	case Direction::RIGHT:
		return head.second == WIDTH - 1;
		break;
	}
}

pair<int, int> GameState::getNextLocation() {
	pair<int, int> nextLocation;
	switch (dir) {
	case Direction::UP:
		nextLocation = make_pair(head.first - 1, head.second);
		break;
	case Direction::DOWN:
		nextLocation = make_pair(head.first + 1, head.second);
		break;
	case Direction::LEFT:
		nextLocation = make_pair(head.first, head.second - 1);
		break;
	case Direction::RIGHT:
		nextLocation = make_pair(head.first, head.second + 1);
		break;
	}
	return nextLocation;
}

void GameState::move() {
	// The head of the snake is at the back of the body ARRAY
	// Whenever we advance the snake, the head advances
	// The first element of the list will take the value of the next element
	// The last element of the list, will take the value of the new head
	// If the snake has eaten, we don't do that and simply push back the head location
	head = getNextLocation();
	if (board[head.first][head.second] == Tile::FOOD) {
		body.push_back(head);
		 food = spawnFood();
		updateBoard();
	}
	else {
		for (int i = 0; i < body.size() - 1; i++) {
			body[i] = body[i + 1];
		}
		body[body.size() - 1] = head;
		updateBoard();
	}
}

void GameState::updateBoard() {
	for (int i = 0; i < board.size(); i++) {
		for (int j = 0; j < board[i].size(); j++) {
			board[i][j] = Tile::EMPTY;
		}
	}
	for (pair<int, int> b : body) {
		board[b.first][b.second] = Tile::BODY;
	}
	board[head.first][head.second] = Tile::HEAD;
	board[food.first][food.second] = Tile::FOOD;
}

pair<int, int> GameState::spawnFood() {
	int foodHeight;
	int foodWidth;
	do {
		foodHeight = rand() % HEIGHT;
		foodWidth = rand() % WIDTH;
	} while (isFoodInBody(foodHeight, foodWidth));
	return make_pair(foodHeight, foodWidth);
}

bool GameState::isFoodInBody(int foodHeight, int foodWidth) {
	for (pair<int, int> b : body) {
		if (b.first == foodHeight && b.second == foodWidth) {
			return true;
		}
	}
	return false;
}

int GameState::getWidth() {
	return WIDTH;
}

int GameState::getHeight() {
	return HEIGHT;
}

vector<vector<Tile>> GameState::getBoard() {
	return board;
}

bool GameState::isOver() {
	return over;
}