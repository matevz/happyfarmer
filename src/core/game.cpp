#include "core/game.h"

Game::Game(){
	world = new World;
	economy = new Economy;
	time = new Time;
}

Game::~Game(){
	delete world;
	delete economy;
	delete time;
}
