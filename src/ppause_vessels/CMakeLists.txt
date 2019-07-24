#--------------------------------------------------------
# The CMakeLists.txt for:                       ppause_vessels
# Author(s):                              
#--------------------------------------------------------

SET(SRC
  pause_vessels.cpp
  pause_vessels_Info.cpp
  main.cpp
)

ADD_EXECUTABLE(ppause_vessels ${SRC})

TARGET_LINK_LIBRARIES(ppause_vessels
   ${MOOS_LIBRARIES}
   mbutil
   m
   pthread)

