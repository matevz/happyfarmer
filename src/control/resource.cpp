#include <fstream>
#include "control/resource.h"

#ifdef WINDOWS32
const char Resource::DELIMITER = '\\';
#else
const char Resource::DELIMITER = '/';
#endif

using namespace std;

/*!
	Finds the correct path of the given resource file.
	Resources are usually textures, sounds, models and other data files.

	Use forward slashes for directory delimiters.

	This function first searches in the following order:
	1) current working directory,
	2) src/ directory

	Function returns empty string, if none found.
*/
string Resource::locateResource( string relPath ) {
	string path = relPath;
	ifstream stream;

	stream.open((path=fixDelimiters(relPath)).c_str());
	if (stream.is_open()) {
		return path;
	}

	stream.open((path=fixDelimiters(string("src/")+relPath)).c_str());
	if (stream.is_open()) {
		return path;
	}

	return "";
}

/*!
	This function replaces any forward slash delimiters with the back-slashed
	delimiters;
 */
string Resource::fixDelimiters( string path ) {
#ifdef WINDOWS32
	for ( int i=0; (i=path.find('/',i)) != npos; i++ ) {
		path.replace( i, 1, DELIMITER );
	}
#endif

	return path;
}
