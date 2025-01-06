# CMake のバージョンを設定
cmake_minimum_required(VERSION 3.13)

# プロジェクト設定
project(PuyoGame VERSION 1.0 LANGUAGES CXX)

# C++ 標準バージョンの設定
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# ソースファイルの指定
set(SOURCE
    src/main.cpp
    src/Game.cpp
    src/Board.cpp
    src/Puyo.cpp
    src/PuyoPair.cpp
    src/SpriteSheet.cpp
)

# 実行ファイルをビルドディレクトリに生成
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

# 実行ファイルを生成
add_executable(PuyoGame ${SOURCE})
target_include_directories(PuyoGame PRIVATE ${PROJECT_SOURCE_DIR}/include)

# SDL2 の設定
find_package(SDL2 REQUIRED)
if(SDL2_FOUND)
    message(STATUS "Found SDL2 in ${SDL2_INCLUDE_DIRS}")
    target_include_directories(PuyoGame PRIVATE ${SDL2_INCLUDE_DIRS})
    target_link_libraries(PuyoGame PRIVATE ${SDL2_LIBRARIES})
else()
    message(FATAL_ERROR "SDL2 not found!")
endif()

# SDL2_image の設定
find_package(PkgConfig REQUIRED)
pkg_check_modules(SDL2IMAGE REQUIRED SDL2_image)

if(SDL2IMAGE_FOUND)
    message(STATUS "Found SDL2_image in ${SDL2IMAGE_INCLUDE_DIRS}")
    target_include_directories(PuyoGame PRIVATE ${SDL2IMAGE_INCLUDE_DIRS})
    target_link_libraries(PuyoGame PRIVATE ${SDL2IMAGE_LIBRARIES})
else()
    message(FATAL_ERROR "SDL2_image not found!")
endif()

# OpenGL の設定
find_package(OpenGL REQUIRED)
if(OpenGL_FOUND)
    message(STATUS "Found OpenGL")
    target_link_libraries(PuyoGame PRIVATE OpenGL::GL)
else()
    message(FATAL_ERROR "OpenGL not found!")
endif()

# 必要なライブラリのリンク
find_library(X11_LIB X11 REQUIRED)
if(X11_LIB)
    message(STATUS "Found X11: ${X11_LIB}")
    target_link_libraries(PuyoGame PRIVATE ${X11_LIB})
else()
    message(FATAL_ERROR "X11 not found!")
endif()

# アセットディレクトリの定義
set(ASSETS_DIR "${PROJECT_SOURCE_DIR}/assets")
target_compile_definitions(PuyoGame PRIVATE ASSETS_DIR="${ASSETS_DIR}")

# 警告オプションを追加
target_compile_options(PuyoGame PRIVATE -Wall -Wextra)
