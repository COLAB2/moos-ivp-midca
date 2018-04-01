#===========================================================================
# FILE:  moos-ivp-extend/CMakeLists.txt
# DATE:  2012/07/24
# INFO:  Top-level CMakeLists.txt file for the moos-ivp-extend project
# NAME:  Maintained by Mike Benjamin - Original setup by Christian Convey
#        Chris Gagner, and tips borrowed from Dave Billin
#===========================================================================

CMAKE_MINIMUM_REQUIRED(VERSION 2.8)
PROJECT( IVP_EXTEND )

#=============================================================================
# Set the output directories for the binary and library files
#=============================================================================

GET_FILENAME_COMPONENT(IVP_EXTEND_BIN_DIR "${CMAKE_SOURCE_DIR}/bin"  ABSOLUTE )
GET_FILENAME_COMPONENT(IVP_EXTEND_LIB_DIR "${CMAKE_SOURCE_DIR}/lib"  ABSOLUTE )

SET( LIBRARY_OUTPUT_PATH      "${IVP_EXTEND_LIB_DIR}" CACHE PATH "" )
SET( ARCHIVE_OUTPUT_DIRECTORY "${IVP_EXTEND_LIB_DIR}" CACHE PATH "" )
SET( LIBRARY_OUTPUT_DIRECTORY "${IVP_EXTEND_LIB_DIR}" CACHE PATH "" )

SET( EXECUTABLE_OUTPUT_PATH    "${IVP_EXTEND_BIN_DIR}" CACHE PATH "" )
SET( RUNTIME_OUTPUT_DIRECTORY "${IVP_EXTEND_BIN_DIR}"  CACHE PATH "" )

#=============================================================================
# Find MOOS
#=============================================================================
find_package(MOOS 10.0)
INCLUDE_DIRECTORIES(${MOOS_INCLUDE_DIRS})

#=============================================================================
# Find the "moos-ivp" base directory
#=============================================================================

# Search for the moos-ivp folder
find_path( MOOSIVP_SOURCE_TREE_BASE
           NAMES build-ivp.sh build-moos.sh configure-ivp.sh
           PATHS "../moos-ivp" "../../moos-ivp" "../../moos-ivp/trunk/" "../moos-ivp/trunk/"
           DOC "Base directory of the MOOS-IvP source tree"
           NO_DEFAULT_PATH
)

if (NOT MOOSIVP_SOURCE_TREE_BASE)
    message("Please set MOOSIVP_SOURCE_TREE_BASE to  ")
    message("the location of the \"moos-ivp\" folder ")
    return()
endif()

#=============================================================================
# Specify where to find IvP's headers and libraries...
#=============================================================================

FILE(GLOB IVP_INCLUDE_DIRS ${MOOSIVP_SOURCE_TREE_BASE}/ivp/src/lib_* )
INCLUDE_DIRECTORIES(${IVP_INCLUDE_DIRS})

FILE(GLOB IVP_LIBRARY_DIRS ${MOOSIVP_SOURCE_TREE_BASE}/lib )
LINK_DIRECTORIES(${IVP_LIBRARY_DIRS})

#=============================================================================
# Specify Compiler Flags
#=============================================================================

IF (${WIN32})
  # Define Windows Compiler flags here
  SET(CMAKE_CXX_FLAGS " ")
ELSE (${WIN32})
  SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
ENDIF (${WIN32})

INCLUDE(CheckCXXCompilerFlag)
CHECK_CXX_COMPILER_FLAG("-std=c++11" COMPILER_SUPPORTS_CXX11)
CHECK_CXX_COMPILER_FLAG("-std=c++0x" COMPILER_SUPPORTS_CXX0X)
IF(COMPILER_SUPPORTS_CXX11)
  SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
  ADD_DEFINITIONS(-D_USE_UNIQUE_PTR)
ELSEIF(COMPILER_SUPPORTS_CXX0X)
  SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")
  ADD_DEFINITIONS(-D_USE_UNIQUE_PTR)
ELSE()
  MESSAGE(STATUS "${CMAKE_CXX_COMPILER} has no C++11 support.")
  REMOVE_DEFINITIONS(-D_USE_UNIQUE_PTR)
ENDIF()
#=============================================================================
# Add Subdirectories
#=============================================================================
ADD_SUBDIRECTORY( src )
