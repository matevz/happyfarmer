#include "core/game.h"

Game::Game(){
	world = new World;
	economy = new Economy;
	time = new Time;
	graphics = new Graphics;
}

Game::~Game(){
	delete world;
	delete economy;
	delete time;
	delete graphics;
}
