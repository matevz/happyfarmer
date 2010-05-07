#ifndef ENGINE_H_
#define ENGINE_H_

class Game;
class Graphics;
class EventHandler;

class Engine {
public:
	Engine();
	~Engine();

	int start();
	static Engine* getInstance() { return Engine::_instance; }

private:
	static Engine* _instance;

	bool _loop;
	Game *_game;
	Graphics *_graphics;
	EventHandler *_eventHandler;

	int _mouseX, _mouseY;
};

#endif /* ENGINE_H_ */
