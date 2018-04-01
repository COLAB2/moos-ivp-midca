#--------------------------------------------------------
# The CMakeLists.txt for:                       pvisual
# Author(s):                              Sravya K
#--------------------------------------------------------

SET(SRC
  visual.cpp
  visual_Info.cpp
  main.cpp
)

ADD_EXECUTABLE(pvisual ${SRC})

TARGET_LINK_LIBRARIES(pvisual
   ${MOOS_LIBRARIES}
   mbutil
   m
   pthread
   zmq)

