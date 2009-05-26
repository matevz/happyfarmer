#ifndef RESOURCE_H_
#define RESOURCE_H_
#include <string>

class Resource {
public:
	static std::string locateResource( std::string relPath );
private:
	static const char DELIMITER;
	static std::string fixDelimiters( std::string path );
};

#endif /* RESOURCE_H_ */
