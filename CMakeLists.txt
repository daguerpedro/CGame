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

FetchContent_Declare(
  entt
  GIT_REPOSITORY https://github.com/skypjack/entt.git
  GIT_TAG v4.0.0
)
FetchContent_MakeAvailable(entt)

FetchContent_Declare(
    imgui
    GIT_REPOSITORY https://github.com/ocornut/imgui.git
    GIT_TAG        v1.92.9b-docking
)
FetchContent_GetProperties(imgui)
FetchContent_MakeAvailable(imgui)

FetchContent_Declare(
  rlImGui
  GIT_REPOSITORY https://github.com/raylib-extras/rlImGui.git
  GIT_TAG Raylib_6_0
)
FetchContent_MakeAvailable(rlImGui)

add_library(rlImGui STATIC
    ${rlimgui_SOURCE_DIR}/rlImGui.cpp
    ${imgui_SOURCE_DIR}/imgui.cpp
    ${imgui_SOURCE_DIR}/imgui_draw.cpp
    ${imgui_SOURCE_DIR}/imgui_tables.cpp
    ${imgui_SOURCE_DIR}/imgui_widgets.cpp
    ${imgui_SOURCE_DIR}/imgui_demo.cpp
)

target_include_directories(rlImGui PUBLIC
    ${rlimgui_SOURCE_DIR}
    ${imgui_SOURCE_DIR}
)

target_link_libraries(rlImGui PUBLIC raylib)

add_executable(${PROJECT_NAME} src/main.cpp
  src/engine/app.h
  src/engine/app.cpp
  src/engine/scene.h
  src/engine/scenemanager.h
  src/engine/scenemanager.cpp
  src/engine/editor.h
  src/engine/editor.cpp
  src/engine/logger.h
  src/engine/components.h
  src/engine/entity.h
  src/engine/defs.h
  src/game/scenes/menu.h
  src/engine/engine.h
  src/engine/renderer.h
)

target_include_directories(${PROJECT_NAME} PUBLIC src/engine)
target_link_libraries(${PROJECT_NAME} PRIVATE raylib rlImGui EnTT::EnTT)

target_compile_definitions(${PROJECT_NAME} PRIVATE
    $<$<CONFIG:Debug>:DEBUG>
    $<$<CONFIG:Release>:RELEASE>
)

set(ASSETS_DIR "${CMAKE_CURRENT_SOURCE_DIR}/assets")
set(ASSETS_OUT_DIR "$<TARGET_FILE_DIR:${PROJECT_NAME}>/assets")

add_custom_command(
    TARGET ${PROJECT_NAME} POST_BUILD
    
    COMMAND ${CMAKE_COMMAND} -E rm -rf ${ASSETS_OUT_DIR}
    
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${ASSETS_DIR} ${ASSETS_OUT_DIR}
    
    COMMENT "Sincronizando a pasta assets para o diretorio do executavel..."
)