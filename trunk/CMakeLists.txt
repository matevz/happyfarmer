PROJECT("Happy Farmer")

# Don't build anything unless the version of CMake is high enough.
cmake_minimum_required(VERSION 2.6)

# Enable make uninstall rule
CONFIGURE_FILE(
  "${CMAKE_CURRENT_SOURCE_DIR}/cmake_uninstall.cmake.in"
  "${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake"
  IMMEDIATE @ONLY)

ADD_CUSTOM_TARGET(uninstall
  "${CMAKE_COMMAND}" -P "${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake")

# Set MingW bin dir, if MingW present
IF(MINGW)
	STRING(REGEX REPLACE "([^ ]+)[/\\].*" "\\1" MINGW_BIN_DIR "${CMAKE_CXX_COMPILER}")
	STRING(REGEX REPLACE "\\\\" "/" MINGW_BIN_DIR "${MINGW_BIN_DIR}") # Replace back slashes to slashes
ENDIF(MINGW)

# Set Qt4 bin dir to find QtCore4.dll and other libs to install
STRING(REGEX REPLACE "([^ ]+)[/\\].*" "\\1" QT_BIN_DIR "${QT_QMAKE_EXECUTABLE}")
STRING(REGEX REPLACE "\\\\" "/" QT_BIN_DIR "${QT_BIN_DIR}")  # Replace back slashes to slashes

#-----------------------------------------------------------------------------
# Happy Farmer version number.
FILE(READ VERSION HF_VERSION)
STRING(REGEX REPLACE "\n" "" HF_VERSION "${HF_VERSION}") # get rid of the newline at the end

#-----------------------------------------------------------------------------
# Set default install path:
# In *nix environments this is /usr/local 
# Under M$ Windows this is C:\Program files\Happy Farmer
# On Mac OS X it is /Applications for the .app and /Library/Fonts for the fonts, but see note below
IF(MINGW)
        IF (NOT CMAKE_INSTALL_PREFIX)
                SET(CMAKE_INSTALL_PREFIX "C:/Program files/Happy Farmer")
        ENDIF (NOT CMAKE_INSTALL_PREFIX)
        SET(HF_INSTALL_DATA_DIR "")
        SET(HF_INSTALL_BIN_DIR "")
        SET(HF_INSTALL_LIB_DIR "")

ELSE(MINGW)
IF(APPLE)
        # This is where OSX-specific resources and scripts live.
        SET(HF_OSX_DIR ${CMAKE_CURRENT_BINARY_DIR}/macosx)

        # "make install" will always install to macosx/package-contents,
        # regardless of any -DCMAKE_INSTALL_PREFIX=foo
        # To install locally, build a package and use the OSX installer
        # TODO: integrate packaging script into CMake so we can just do "make install"
        # or similar and have it install and link the libraries properly
        SET(CMAKE_INSTALL_PREFIX "${HF_OSX_DIR}/package-contents")

        SET(HF_OSX_APP_DIR "HappyFarmer.app/Contents")

        SET(HF_INSTALL_BIN_DIR ${HF_OSX_APP_DIR}/MacOS)
        SET(HF_INSTALL_DATA_DIR ${HF_OSX_APP_DIR}/Resources)
        SET(HF_INSTALL_LIB_DIR ${HF_OSX_APP_DIR}/Resources/lib)
ELSE(APPLE)
        IF (NOT CMAKE_INSTALL_PREFIX)
                SET(CMAKE_INSTALL_PREFIX "/usr/local")
        ENDIF (NOT CMAKE_INSTALL_PREFIX)
        SET(HF_INSTALL_DATA_DIR "share/happyfarmer")
        SET(HF_INSTALL_BIN_DIR "bin")
        SET(HF_INSTALL_LIB_DIR "lib")
ENDIF(APPLE)
ENDIF(MINGW)
#-----------------------------------------------------------------------------

#-----------------------------------------------------------------------------
# Search for Qt4. We need the latest version of Qt
SET(QT_MIN_VERSION "4.4.0")

# this line includes FindQt4.cmake, which searches the Qt library and headers
FIND_PACKAGE(Qt4 REQUIRED)

# in the following lines all the requires include directories are added
INCLUDE_DIRECTORIES(src)

# Recurse into the "src" and "doc" subdirectories.  This does not actually
# cause another cmake executable to run.  The same process will walk through
# the project's entire directory structure.
ADD_SUBDIRECTORY(src)

# Install README, VERSION, COPYING and other raw txt files
INSTALL(FILES AUTHORS DEVELOPERS COPYING NEWS README VERSION DESTINATION "${CMAKE_INSTALL_PREFIX}/${HF_INSTALL_DATA_DIR}")

