#pragma once

//Direction left->up->right->down
enum Direction
{
	NOT_MOVE = 0, LEFT = 1, UP = 2, RIGHT = 3, DOWN = 4
};

Direction static getOppositionalDir(Direction direction)
{
	if (direction == LEFT) return RIGHT;
	if (direction == RIGHT) return LEFT;
	if (direction == UP) return DOWN;
	if (direction == DOWN) return UP;
}