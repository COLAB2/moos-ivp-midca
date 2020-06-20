#--------------------------------------------------------
# The CMakeLists.txt for:                       prelocate
# Author(s):                              Sravya
#--------------------------------------------------------


SET(SRC
  relocate.cpp
  relocate_Info.cpp
  main.cpp
)

ADD_EXECUTABLE(prelocate ${SRC})


TARGET_LINK_LIBRARIES(prelocate
   ${MOOS_LIBRARIES}
   mbutil
   m
   pthread)
