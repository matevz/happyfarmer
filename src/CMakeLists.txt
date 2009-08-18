SET( Core
	core/point3d.cpp
	core/tile.cpp
	core/terrain.cpp
	core/object.cpp
	core/player.cpp
)

SET( Gui
	gui/mainwin.cpp
	gui/scene.cpp
	gui/screen.cpp
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
)

ADD_EXECUTABLE( happyfarmer ${Core} ${Gui} ${Models} ${Control} ${Objects} main.cpp )
TARGET_LINK_LIBRARIES( happyfarmer "GL" "GLU" "m" "SDL" "SDL_image" "alut" "ogg" "vorbis" "vorbisfile" )
