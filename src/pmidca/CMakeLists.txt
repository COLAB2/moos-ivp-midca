#--------------------------------------------------------
# The CMakeLists.txt for:                       pmidca
# Author(s):                              Sravya
#--------------------------------------------------------

SET(SRC
  midca.cpp
  midca_Info.cpp
  main.cpp
)

ADD_EXECUTABLE(pmidca ${SRC})

TARGET_LINK_LIBRARIES(pmidca
   ${MOOS_LIBRARIES}
   mbutil
   m
   pthread
   zmq)

