#--------------------------------------------------------
# The CMakeLists.txt for:                       ploc
# Author(s):                              Sravya K
#--------------------------------------------------------
cmake_minimum_required(VERSION 3.5)
find_package(PkgConfig)
pkg_check_modules(PC_ZeroMQ QUIET zmq)

find_path(ZeroMQ_INCLUDE_DIR
        NAMES zmq
        PATHS ${PC_ZeroMQ_INCLUDE_DIRS}
        )
find_library(ZeroMQ_LIBRARY
        NAMES zmq
        PATHS ${PC_ZeroMQ_LIBRARY_DIRS}
        )

SET(SRC
  loc.cpp
  loc_Info.cpp
  main.cpp
)

ADD_EXECUTABLE(ploc ${SRC})

target_include_directories(ploc PUBLIC ${ZeroMQ_INCLUDE_DIR})


TARGET_LINK_LIBRARIES(ploc
   ${MOOS_LIBRARIES}
   ${MOOSGeodesy_LIBRARIES}
   mbutil
   m
   pthread
   ${ZeroMQ_LIBRARY})
