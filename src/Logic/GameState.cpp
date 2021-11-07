#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "GameState.h"
#include <iostream>
#include <stdlib.h>
#include <utility>

const int HEIGHT = 10;
const int WIDTH = 10;

using std::vector;
using std::pair;
using std::make_pair;

GameState::GameState() {
	board = vector<vector<Tile>>(HEIGHT, vector<Tile>(WIDTH, Tile::EMPTY));
	int startHeight = rand() % HEIGHT;
	int startWidth = rand() % WIDTH;
	board[startHeight][startWidth] = Tile::HEAD;
	head = pair<int, int>(startHeight, startWidth);
	body.push_back(head);
	dir = Direction(rand() % 4);
	over = false;
}

void GameState::update() {
	if (isCollision()) {
		over = true;
	} 
	else {
		move();
	}
}

void GameState::setDirection(Direction d) {
	dir = d;
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
	}
	else {
		for (int i = 0; i < body.size() - 1; i++) {
			body[i] = body[i + 1];
		}
		body[body.size() - 1] = head;
	}
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