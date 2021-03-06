#include <set>
#include <algorithm>
#include <utility>

extern "C" {
	#include <game_of_life.h>
}

#include "game.hh"

GameOfLife::Game::Game()
{
	game = Game_New();
	currentCoordinates = new GameOfLife::Coors();
	previousCoordinates = new GameOfLife::Coors();
}

long int GameOfLife::Game::cellCount() const
{
	return Game_Cell_Count(game);
}

GameOfLife::Game GameOfLife::Game::addCellAt(long int x, long int y)
{
	Game_Add_Cell_At(game, x, y);
	syncGenerations();
	return *this;
}

bool GameOfLife::Game::hasCellAt(long int x, long int y) const
{
	return Game_Has_Cell_At(game, x, y) == 1 ? true : false;
}

GameOfLife::Game GameOfLife::Game::tick()
{
	Game_Tick(game);
	syncGenerations();
	return *this;
}

GameOfLife::Game GameOfLife::Game::read(const std::string filename)
{
	game = Game_Create_From_File(filename.c_str());
	return *this;
}

GameOfLife::Coors GameOfLife::Game::currentGeneration() const
{
	return *currentCoordinates;
}

GameOfLife::Coors GameOfLife::Game::previousGeneration() const
{
	return *previousCoordinates;
}

GameOfLife::Coors GameOfLife::Game::cellsToRemove() const
{
	return differencesBetween(previousCoordinates, currentCoordinates);
}

GameOfLife::Coors GameOfLife::Game::cellsToAdd() const
{
	return differencesBetween(currentCoordinates, previousCoordinates);
}

void GameOfLife::Game::accumulationVisitor(::Cell cell, void* data)
{
	GameOfLife::Coors *allCoordinates = (GameOfLife::Coors*)(data);
	allCoordinates->insert(std::make_pair(cell.coordinates.x, cell.coordinates.y));
}

GameOfLife::Coors GameOfLife::Game::differencesBetween(const GameOfLife::Coors *first, const GameOfLife::Coors *second)
{
	GameOfLife::Coors result;
	std::set_difference(first->begin(), first->end(),
	                    second->begin(), second->end(),
	                    std::inserter(result, result.end()));
	return result;
}

void GameOfLife::Game::syncGenerations()
{
	currentCoordinates->clear();
	previousCoordinates->clear();
	Game_At_Each_Cell(game, accumulationVisitor, (void*)currentCoordinates);
	Game_At_Each_Old_Cell(game, accumulationVisitor, (void*)previousCoordinates);
}
