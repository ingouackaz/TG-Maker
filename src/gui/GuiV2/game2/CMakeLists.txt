project(Pfa)
cmake_minimum_required(VERSION 2.8)

set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake_modules")
set(CMAKE_CXX_FLAGS "-DSERVER -g -Wall -Wextra")
SET(SOURCES
DAPROJECT.cpp
)

SET(EXECUTABLE_NAME
PFA-MENU
)



add_executable (
${EXECUTABLE_NAME} ${SOURCES}
)
target_link_libraries(${EXECUTABLE_NAME} ${SFML_LIBRARY} -lsfml-graphics -lsfml-window -lsfml-system )
