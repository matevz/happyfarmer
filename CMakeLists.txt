PROJECT("Happy Farmer")

# Don't build anything unless the version of CMake is high enough.
cmake_minimum_required(VERSION 3.22)

# Set MingW bin dir, if MingW present
IF(MINGW)
	STRING(REGEX REPLACE "([^ ]+)[/\\].*" "\\1" MINGW_BIN_DIR "${CMAKE_CXX_COMPILER}")
	STRING(REGEX REPLACE "\\\\" "/" MINGW_BIN_DIR "${MINGW_BIN_DIR}") # Replace back slashes to slashes
ENDIF(MINGW)

# Set Qt5 bin dir to find QtCore5.dll and other libs to install
STRING(REGEX REPLACE "([^ ]+)[/\\].*" "\\1" QT_BIN_DIR "${QT_QMAKE_EXECUTABLE}")
STRING(REGEX REPLACE "\\\\" "/" QT_BIN_DIR "${QT_BIN_DIR}")  # Replace back slashes to slashes

#-----------------------------------------------------------------------------
# Happy Farmer version number.
FILE(READ VERSION HF_VERSION)
STRING(REGEX REPLACE "\n" "" HF_VERSION "${HF_VERSION}") # get rid of the newline at the end

#-----------------------------------------------------------------------------
# Search for Qt4. We need the latest version of Qt
SET(QT_MIN_VERSION "5.2.0")

# this line includes FindQt4.cmake, which searches the Qt library and headers
FIND_PACKAGE(Qt5Core REQUIRED)
FIND_PACKAGE(Qt5Gui REQUIRED)
FIND_PACKAGE(Qt5Svg REQUIRED)
FIND_PACKAGE(Qt5Widgets REQUIRED)
FIND_PACKAGE(Qt5LinguistTools REQUIRED)
FIND_PACKAGE(Qt5Xml REQUIRED)

# in the following lines all the requires include directories are added
INCLUDE_DIRECTORIES(src)

# Recurse into the "src" and "doc" subdirectories.  This does not actually
# cause another cmake executable to run.  The same process will walk through
# the project's entire directory structure.
ADD_SUBDIRECTORY(src)

# Install README, VERSION, COPYING and other raw txt files
INSTALL(FILES AUTHORS DEVELOPERS COPYING NEWS README VERSION DESTINATION "${CMAKE_INSTALL_PREFIX}/${HF_INSTALL_DATA_DIR}")

