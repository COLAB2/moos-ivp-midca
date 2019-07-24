#--------------------------------------------------------
# The CMakeLists.txt for:                       pmidca
# Author(s):                              Sravya
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
  midca.cpp
  midca_Info.cpp
  main.cpp
)

ADD_EXECUTABLE(pmidca ${SRC})

target_include_directories(pmidca PUBLIC ${ZeroMQ_INCLUDE_DIR})


TARGET_LINK_LIBRARIES(pmidca
   ${MOOS_LIBRARIES}
   mbutil
   m
   pthread
   ${ZeroMQ_LIBRARY})
