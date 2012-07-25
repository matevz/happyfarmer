INCLUDE(CheckLibraryExists)

FIND_PACKAGE(Qt4)

# This module is used to resolve the file dependencies
# for QT files using an UI (User Interface) Qt file
# created with the Qt4 designer
# INCLUDE(AddFileDependencies)

IF(NOT CMAKE_BUILD_TYPE)
	SET(CMAKE_BUILD_TYPE Debug)
ENDIF(NOT CMAKE_BUILD_TYPE)

SET(CMAKE_C_FLAGS_DEBUG "-O0 -g")
SET(CMAKE_C_FLAGS_RELEASE "-O2")

SET(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -std=c++0x")
SET(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} -std=c++0x")

# Build universal binaries on Mac
IF(APPLE)
	SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -arch ppc -arch i386")
	SET(DEFAULT_DATA_DIR "HappyFarmer.app/Contents/Resources")
ENDIF(APPLE)

##############################
# List of Qt4-parsed sources #
##############################
# Define the UI source files used by Happy Farmer
SET(HF_UIs		# List of .ui forms drawn by qt-designer that need to be compiled
	ui/mainwin.ui
)

# Define the MOC source files used by Canorus
SET(HF_Gui_MOCs	# List of classes which Qt needs to produce MOCs for them (in order for events, signals, slots and other macros to work)
	ui/mainwin.h

	widget/gameview.h
)

SET(HF_Core_MOCs # MOCs compiled into scripting library as well
	
)

################
# Qt4 settings #
################
# Enable needed Qt modules for Happy Farmer
SET(QT_USE_QTXML True) # Save/Load
SET(QT_USE_QTSVG True) # Icons, Images etc.

QT4_WRAP_UI(HF_UIC_Srcs ${HF_UIs})
QT4_WRAP_CPP(HF_Gui_MOC_Srcs ${HF_Gui_MOCs})
QT4_WRAP_CPP(HF_Core_MOC_Srcs ${HF_Core_MOCs})

#########################
# List of other sources #
#########################
SET(HF_Core_Srcs		# Core sources
	model/game.cpp
	model/resource.cpp
	model/settings.cpp
	model/tile.cpp
	model/terrain/grass.cpp
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
)

SET(HF_Srcs
	main.cpp
	
	${HF_Core_Srcs}
	${HF_Ui_Srcs}
	${HF_Widget_Srcs}
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

IF(APPLE)
	SET(HF_OSX_Icon ${HF_OSX_DIR}/files/happyfarmer.icns)
	SET(HF_OSX_Info ${HF_OSX_DIR}/files/Info.plist)

	SET(HF_OSX_Qt_libs
		${QT_QTCORE_LIBRARY}/Versions/4/QtCore
		${QT_QTGUI_LIBRARY}/Versions/4/QtGui
		${QT_QTXML_LIBRARY}/Versions/4/QtXml
		${QT_QTSVG_LIBRARY}/Versions/4/QtSvg
		)
ENDIF(APPLE)

#########################
# Compiler Define flags #
#########################
# RtMidi cross-platform definitions
IF("${CMAKE_SYSTEM_NAME}" MATCHES "Linux") #IF(LINUX) isn't supported by CMake yet
	ADD_DEFINITIONS(-D__LINUX_ALSASEQ__)
ENDIF("${CMAKE_SYSTEM_NAME}" MATCHES "Linux")
IF(APPLE)
	ADD_DEFINITIONS(-D__MACOSX_CORE__)
ENDIF(APPLE)
IF(MINGW)
	ADD_DEFINITIONS(-D__WINDOWS_MM__)
ENDIF(MINGW)

# Define default data dir, if under POSIX systems.
IF(NOT MINGW)
	IF (NOT DEFAULT_DATA_DIR)
		ADD_DEFINITIONS(-DDEFAULT_DATA_DIR=\"${CMAKE_INSTALL_PREFIX}/${HF_INSTALL_DATA_DIR}\")
	ELSE (NOT DEFAULT_DATA_DIR)
		ADD_DEFINITIONS(-DDEFAULT_DATA_DIR=\"${DEFAULT_DATA_DIR}\")
	ENDIF (NOT DEFAULT_DATA_DIR)
ENDIF(NOT MINGW)

IF(APPLE)
	SET(MACOSX_BUNDLE_INFO_STRING "Happy Farmer")
	SET(MACOSX_BUNDLE_ICON_FILE happyfarmer.icns) # \todo Copy this file to Applications/happyfarmer.app/Resources when the package is created
ENDIF(APPLE)

# Define Canorus version
ADD_DEFINITIONS(-DHF_VERSION=\"${HF_VERSION}\")

####################################
# Include paths and set up targets #
####################################
# This needs to be added in order for #include to work inside .cpp files - it adds src/ to include path
INCLUDE_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR})

# This line adds the include path of the Qt
# directory to the compiler include path
INCLUDE(${QT_USE_FILE})

# Adds Canorus resource file under Windows (Canorus icon etc.).
IF(MINGW)
	# CMake currently doesn't support windres yet. Add command manually
	FIND_PROGRAM(
		WINDRES_PROGRAM windres.exe PATHS
		"[HKEY_LOCAL_MACHINE\\SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Uninstall\\MinGW;InstallLocation]/bin"
		c:/MinGW/bin /MinGW/bin
	)
	ADD_CUSTOM_COMMAND(
		OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/happyfarmerrc.obj
		COMMAND ${WINDRES_PROGRAM}
		-i happyfarmerrc.rc
		-o happyfarmerrc.obj
	)
	SET(HF_Srcs ${HF_Srcs} happyfarmerrc.obj)
ENDIF(MINGW)
	
# This line tells cmake to create the Happy Farmer executable.
# Attention: In contrast to Makefiles don't add "\" to separate lines
ADD_EXECUTABLE(happyfarmer ${HF_UIC_Srcs}  ${HF_Srcs}
                       ${HF_Core_MOC_Srcs} ${HF_Gui_MOC_Srcs}
                       ${MACOSX_BUNDLE}	# Works only under Apple - adds the application description, icon etc.
)

TARGET_LINK_LIBRARIES(happyfarmer ${QT_LIBRARIES} )

###############
# Translation #
###############
ADD_CUSTOM_COMMAND(
	TARGET happyfarmer
	PRE_BUILD
	COMMAND ${QT_BINARY_DIR}/lupdate
	ARGS -noobsolete ${HF_UIC_Srcs} ${HF_Srcs} -ts ${HF_Translation_Srcs} lang/template.ts
)
ADD_CUSTOM_COMMAND(
	TARGET happyfarmer
	PRE_BUILD
	COMMAND ${QT_BINARY_DIR}/lrelease
	ARGS ${HF_Translation_Srcs}
)

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

IF(MINGW)
	# Install Qt libs
	INSTALL( FILES ${QT_BIN_DIR}/QtCore4.dll ${QT_BIN_DIR}/QtGui4.dll ${QT_BIN_DIR}/QtSvg4.dll ${QT_BIN_DIR}/QtXml4.dll ${QT_BIN_DIR}/QtHelp4.dll ${QT_BIN_DIR}/QtSql4.dll ${QT_BIN_DIR}/QtNetwork4.dll ${QT_BIN_DIR}/QtCLucene4.dll DESTINATION ${CMAKE_INSTALL_PREFIX}/${HF_INSTALL_BIN_DIR} )
	
	# Install qsvg plugin for rendering SVG icons etc.
	INSTALL( FILES ${QT_PLUGINS_DIR}/iconengines/qsvgicon4.dll DESTINATION "${CMAKE_INSTALL_PREFIX}/${HF_INSTALL_BIN_DIR}/iconengines" )
	
	# Install mingwm10.dll
	INSTALL( FILES ${MINGW_BIN_DIR}/mingwm10.dll DESTINATION ${CMAKE_INSTALL_PREFIX}/${HF_INSTALL_BIN_DIR} )
ENDIF(MINGW)

IF(APPLE)
	# Install icon & Info.plist
	INSTALL(FILES ${HF_OSX_Icon} DESTINATION ${CMAKE_INSTALL_PREFIX}/${HF_INSTALL_DATA_DIR})
	INSTALL(FILES ${HF_OSX_Info} DESTINATION ${CMAKE_INSTALL_PREFIX}/${HF_OSX_APP_DIR})
ENDIF(APPLE)
