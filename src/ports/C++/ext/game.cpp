#include <set>
#include <algorithm>
#include <utility>

extern "C" {
	#include <game_of_life.h>
}

#include "include/game.h"

void GameOfLife::Game::syncGenerations()
{
	currentCoordinates->clear();
	previousCoordinates->clear();
	Game_At_Each_Cell(game, accumulationVisitor, (void*)currentCoordinates);
	Game_At_Each_Old_Cell(game, accumulationVisitor, (void*)previousCoordinates);
}

void GameOfLife::Game::accumulationVisitor(::Coordinates coordinates_, void* data_)
{
	Cors *allCoordinates = (Cors*)(data_);
	std::pair <long int, long int>coordinates = std::make_pair(Coordinates_X(coordinates_), Coordinates_Y(coordinates_));
	allCoordinates->insert(coordinates);
}

Cors GameOfLife::Game::differencesBetween(Cors *first, Cors *second)
{
	Cors result;
	std::set_difference(first->begin(), first->end(),
	                    second->begin(), second->end(),
	                    std::inserter(result, result.end()));
	return result;
}

GameOfLife::Game::Game()
{
	game = Game_New();
	currentCoordinates = new Cors();
	previousCoordinates = new Cors();
}

long int GameOfLife::Game::cellCount()
{
	return Game_Cell_Count(game);
}

GameOfLife::Game GameOfLife::Game::addCellAt(long int x, long int y)
{
	Game_Add_Cell_At(game, x, y);
	syncGenerations();
	return *this;
}

bool GameOfLife::Game::hasCellAt(long int x, long int y)
{
	return Game_Has_Cell_At(game, x, y) == 1 ? true : false;
}

GameOfLife::Game GameOfLife::Game::tick()
{
	Game_Tick(game);
	syncGenerations();
	return *this;
}

Cors GameOfLife::Game::currentGeneration()
{
	return *currentCoordinates;
}

Cors GameOfLife::Game::previousGeneration()
{
	return *previousCoordinates;
}

Cors GameOfLife::Game::cellsToRemove()
{
	return differencesBetween(previousCoordinates, currentCoordinates);
}

Cors GameOfLife::Game::cellsToAdd()
{
	return differencesBetween(currentCoordinates, previousCoordinates);
}
