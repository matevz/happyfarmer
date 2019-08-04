INCLUDE(CheckLibraryExists)

# This module is used to resolve the file dependencies
# for QT files using an UI (User Interface) Qt file
# created with the Qt4 designer
# INCLUDE(AddFileDependencies)

IF(NOT CMAKE_BUILD_TYPE)
	SET(CMAKE_BUILD_TYPE Debug)
ENDIF(NOT CMAKE_BUILD_TYPE)

SET(CMAKE_C_FLAGS_DEBUG "-O0 -g")
SET(CMAKE_C_FLAGS_RELEASE "-O2")

SET(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -std=c++11")
SET(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} -std=c++11")

##############################
# List of Qt5-parsed sources #
##############################
# Define the UI source files used by Happy Farmer
SET(HF_UIs		# List of .ui forms drawn by qt-designer that need to be compiled
	ui/mainwin.ui
)

# Define the MOC source files used by Happy Farmer
SET(HF_Gui_MOCs	# List of classes which Qt needs to produce MOCs for them (in order for events, signals, slots and other macros to work)
	ui/mainwin.h

	control/drawablectl.h

	widget/gameview.h
)

SET(HF_Core_MOCs # MOCs compiled into scripting library as well
	model/gameloop.h
)

################
# Qt5 settings #
################
# Enable needed Qt modules for Happy Farmer
SET(QT_USE_QTXML True) # Save/Load
SET(QT_USE_QTSVG True) # Icons, Images etc.

QT5_WRAP_UI(HF_UIC_Srcs ${HF_UIs})
QT5_WRAP_CPP(HF_Gui_MOC_Srcs ${HF_Gui_MOCs})
QT5_WRAP_CPP(HF_Core_MOC_Srcs ${HF_Core_MOCs})

#########################
# List of other sources #
#########################
SET(HF_Core_Srcs		# Core sources
	model/game.cpp
	model/gameloop.cpp
	model/resource.cpp
	model/settings.cpp
	model/tile.cpp
	model/terrain/grass.cpp

	model/construction.cpp
	model/construction/asphalt_road.cpp
	model/construction/dirt_road.cpp

	model/object.cpp
	model/animal/sheep.cpp
)

SET(HF_Ctl_Srcs		# Control sources
	control/constructctl.cpp
	control/objectctl.cpp
	control/drawablectl.cpp
)

SET(HF_Widget_Srcs  	# Sources for all custom widgets present in Happy Farmer
	widget/gameview.cpp
)

SET(HF_Ui_Srcs		# Implementations of widgets that have their own .ui qt-designer files
	ui/mainwin.cpp
)

SET(HF_Drawable_Srcs	# Drawable instances of the data
	drawable/drawable.cpp
	
	drawable/terrain/grass.cpp

	drawable/construction/asphalt_road.cpp
	drawable/construction/dirt_road.cpp

	drawable/animal/sheep.cpp

	drawable/helper/tile.cpp
	drawable/helper/dot.cpp
)

SET(HF_Srcs
	main.cpp
	
	${HF_Core_Srcs}
	${HF_Ui_Srcs}
	${HF_Widget_Srcs}
	${HF_Ctl_Srcs}
	${HF_Drawable_Srcs}
)

SET(HF_Data
       ../data
)

# Set translation files
FILE(GLOB HF_Translation_Srcs "lang/*.ts") # lang/*.ts -> HF_Translation_Srcs
STRING(REGEX REPLACE "\\.ts" ".qm" HF_Translation_Bins "${HF_Translation_Srcs}") # Set HF_Translation_Bins to same values as HF_Translation_Srcs with different extensions

SET(HF_Fonts	# Fonts needed by Happy Farmer
	../data/fonts/FreeSans.ttf		# main font
)

#########################
# Compiler Define flags #
#########################
# RtMidi cross-platform definitions
IF("${CMAKE_SYSTEM_NAME}" MATCHES "Linux") #IF(LINUX) isn't supported by CMake yet
	ADD_DEFINITIONS(-D__LINUX_ALSASEQ__)
ENDIF("${CMAKE_SYSTEM_NAME}" MATCHES "Linux")

# Define default data dir, if under POSIX systems.
IF (NOT DEFAULT_DATA_DIR)
	ADD_DEFINITIONS(-DDEFAULT_DATA_DIR=\"${CMAKE_INSTALL_PREFIX}/${HF_INSTALL_DATA_DIR}\")
ELSE (NOT DEFAULT_DATA_DIR)
	ADD_DEFINITIONS(-DDEFAULT_DATA_DIR=\"${DEFAULT_DATA_DIR}\")
ENDIF (NOT DEFAULT_DATA_DIR)

# Define Canorus version
ADD_DEFINITIONS(-DHF_VERSION=\"${HF_VERSION}\")

####################################
# Include paths and set up targets #
####################################
# This needs to be added in order for #include to work inside .cpp files - it adds src/ to include path
INCLUDE_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR})
INCLUDE_DIRECTORIES("${CMAKE_CURRENT_SOURCE_DIR}/ui")
INCLUDE_DIRECTORIES("${CMAKE_CURRENT_SOURCE_DIR}/control")
INCLUDE_DIRECTORIES("${CMAKE_CURRENT_SOURCE_DIR}/widget")
INCLUDE_DIRECTORIES("${CMAKE_CURRENT_SOURCE_DIR}/drawable")

# This line adds the include path of the Qt
# directory to the compiler include path
INCLUDE_DIRECTORIES(${Qt5Core_INCLUDE_DIRS})
INCLUDE_DIRECTORIES(${Qt5Gui_INCLUDE_DIRS})
INCLUDE_DIRECTORIES(${Qt5Svg_INCLUDE_DIRS})
INCLUDE_DIRECTORIES(${Qt5Widgets_INCLUDE_DIRS})
INCLUDE_DIRECTORIES(${Qt5Xml_INCLUDE_DIRS})

# This line tells cmake to create the Happy Farmer executable.
# Attention: In contrast to Makefiles don't add "\" to separate lines
ADD_EXECUTABLE(happyfarmer ${HF_UIC_Srcs}  ${HF_Srcs}
                       ${HF_Core_MOC_Srcs} ${HF_Gui_MOC_Srcs}
)

TARGET_LINK_LIBRARIES(happyfarmer Qt5::Widgets Qt5::Core Qt5::Gui Qt5::Svg Qt5::Xml z pthread )

###############
# Translation #
###############
ADD_CUSTOM_TARGET(tr
        WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}/src
	DEPENDS ${HF_UIC_Srcs}
	COMMAND ${Qt5_LUPDATE_EXECUTABLE} -noobsolete ${HF_UIC_Srcs} ${HF_Srcs} -ts ${HF_Translation_Srcs} lang/template.ts
)

qt5_add_translation(HF_Translation_Bins ${HF_Translation_Srcs})
ADD_CUSTOM_TARGET(happyfarmer_qm DEPENDS ${HF_Translation_Bins})
ADD_DEPENDENCIES(happyfarmer happyfarmer_qm)

################
# Installation #
################
# Install canorus exe and CanorusRuby lib
INSTALL(TARGETS happyfarmer
  RUNTIME DESTINATION ${CMAKE_INSTALL_PREFIX}/${HF_INSTALL_BIN_DIR}
)

# Install data - icons, images, sounds, fonts
INSTALL( DIRECTORY ${HF_Data} DESTINATION "${CMAKE_INSTALL_PREFIX}/${HF_INSTALL_DATA_DIR}" )
# Install translations
INSTALL(FILES ${HF_Translation_Bins} DESTINATION "${CMAKE_INSTALL_PREFIX}/${HF_INSTALL_DATA_DIR}/lang")
