#--------------------------------------------------------
# The CMakeLists.txt for:                       pmine_distributor
# Author(s):                              Sravya Kondrakunta
#--------------------------------------------------------
cmake_minimum_required(VERSION 3.5)
find_package(PkgConfig)
pkg_check_modules(PC_ZeroMQ QUIET zmq)
find_path(ZeroMQ_INCLUDE_DIR
        NAMES zmq.hpp
        PATHS ${PC_ZeroMQ_INCLUDE_DIRS}
        )
find_library(ZeroMQ_LIBRARY
        NAMES zmq
        PATHS ${PC_ZeroMQ_LIBRARY_DIRS}
        )

SET(SRC
  mine_layer.cpp
  mine_layer_Info.cpp
  main.cpp
)

ADD_EXECUTABLE(pmine_layer ${SRC})
target_include_directories(pmine_layer PUBLIC ${ZeroMQ_INCLUDE_DIR})

TARGET_LINK_LIBRARIES(pmine_layer
   ${MOOS_LIBRARIES}
   mbutil
   m
   pthread
   ${ZeroMQ_LIBRARY})

