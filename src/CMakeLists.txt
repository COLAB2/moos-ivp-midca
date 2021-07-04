##############################################################################
# FILE:        moos-ivp-extend/src/CMakeLists.txt
# DATE:        2010/09/07
# DESCRIPTION: CMakeLists.txt file for the moos-ivp-extend source directory
##############################################################################


#============================================================================
# Add the libraries in the current directory to the include path
#============================================================================
FILE(GLOB LOCAL_LIBRARY_DIRS ./lib_*)
INCLUDE_DIRECTORIES(${LOCAL_LIBRARY_DIRS})

#===============================================================================
# FINDING MOOSGeodesy' HEADERS AND LIBRARIES...
#===============================================================================
# moos - http://www.robots.ox.ac.uk/~mobile/MOOS/wiki/pmwiki.php
find_package(MOOSGeodesy)
include_directories(${MOOSGeodesy_INCLUDE_DIRS})
#link_directories(${MOOSGeodesy_LIBRARY_PATH})


#============================================================================
# List the subdirectories to build...
#============================================================================

ADD_SUBDIRECTORY(pmidca)
ADD_SUBDIRECTORY(pvisual)
ADD_SUBDIRECTORY(pvisualGenios)
ADD_SUBDIRECTORY(ploc)
ADD_SUBDIRECTORY(prelocate)
ADD_SUBDIRECTORY(pmine_distributor)
ADD_SUBDIRECTORY(pmine_layer)
ADD_SUBDIRECTORY(ppause_vessels)

##############################################################################
#                           END of CMakeLists.txt
##############################################################################
