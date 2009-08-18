#ifndef PLAYER_H_
#define PLAYER_H_

#include <string>

class Player {
public:
	Player( const std::string& name );
	virtual ~Player();

private:
	std::string _name;
};

#endif /* PLAYER_H_ */
