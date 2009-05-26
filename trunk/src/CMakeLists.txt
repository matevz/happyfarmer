SET( Core
	core/point3d.cpp
	core/tile.cpp
	core/world.cpp
)

SET( Gui
	gui/mainwin.cpp
	gui/scene.cpp
	gui/screen.cpp
)

SET( LibObj
	libobj/obj.cpp
	libobj/obj_parser.cpp
)

SET( Control
	control/modelloader.cpp
	control/resource.cpp
)

ADD_EXECUTABLE( happyfarmer ${Core} ${Gui} ${LibObj} ${Control} main.cpp )
TARGET_LINK_LIBRARIES( happyfarmer "GL" "GLU" "m" "SDL" "SDL_image" "alut" "ogg" "vorbis" "vorbisfile" )
