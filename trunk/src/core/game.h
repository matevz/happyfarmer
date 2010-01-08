/*Contains everything needed for the game to be played.*/

#ifndef GAME_H_
#define GAME_H_

#include "core/time.h"
#include "core/economy.h"
#include "core/world.h"
#include "gui/graphics.h"

class Game {
public:
	Game();
	~Game();


private:
	World *world;
	Economy *economy;
	Time *time;
	Graphics *graphics;
};

#endif /* GAME_H_ */
