cmake_minimum_required(VERSION 3.10.0)
project(CGame VERSION 0.1.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)
FetchContent_Declare(
  raylib
  GIT_REPOSITORY https://github.com/raysan5/raylib.git
  GIT_TAG        6.0
)

set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE) 
FetchContent_MakeAvailable(raylib)

add_executable(${PROJECT_NAME} src/main.cpp
  src/tower.h
  src/tower.cpp
  src/entity.h
  src/entity.cpp
  src/enemy.h
  src/enemy.cpp
  src/wavemanager.h
  src/wavemanager.cpp
  src/text.h)

target_link_libraries(${PROJECT_NAME} PRIVATE raylib)

set(ASSETS_DIR "${CMAKE_CURRENT_SOURCE_DIR}/assets")
set(ASSETS_OUT_DIR "$<TARGET_FILE_DIR:${PROJECT_NAME}>/assets")

add_custom_command(
    TARGET ${PROJECT_NAME} POST_BUILD
    
    COMMAND ${CMAKE_COMMAND} -E rm -rf ${ASSETS_OUT_DIR}
    
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${ASSETS_DIR} ${ASSETS_OUT_DIR}
    
    COMMENT "Sincronizando a pasta assets para o diretorio do executavel..."
)