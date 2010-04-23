SET( Core
	core/tile.cpp
	core/terrain.cpp
	core/object.cpp
	core/stationaryobject.cpp
	core/movingobject.cpp
	core/player.cpp
	core/engine.cpp
	core/game.cpp
)

SET( Gui
	gui/graphics.cpp
	gui/sound.cpp
	gui/eventhandler.cpp
)

SET( Models
	models/objparser.cpp
	models/modelloader.cpp
	models/modelloaderparser.cpp
)

SET( Control
	control/resource.cpp
)

SET( Objects
	objects/tractor.cpp
	objects/grass.cpp
	objects/fence.cpp
	objects/road.cpp
	objects/house.cpp
	objects/cow.cpp
	objects/plant.cpp
)

ADD_EXECUTABLE( happyfarmer ${Core} ${Gui} ${Models} ${Control} ${Objects} main.cpp )
TARGET_LINK_LIBRARIES( happyfarmer "GL" "GLU" "m" "SDL" "SDL_image" "alut" "ogg" "vorbis" "vorbisfile" )
