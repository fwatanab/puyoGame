# # CMakeのバージョンを設定
# cmake_minimum_required(VERSION 3.13)
# 
# # プロジェクト設定 (C++ を使う)
# project(puyoGame VERSION 1.0 LANGUAGES CXX)
# 
# # C++の標準バージョンを設定
# set(CMAKE_CXX_STANDARD 17)
# set(CMAKE_CXX_STANDARD_REQUIRED True)
# 
# # ソースファイルを設定
# set(SOURCE
#     src/main.cpp
#     src/Game.cpp
#     src/SpriteSheet.cpp
#     src/Board.cpp
#     src/Puyo.cpp
#     src/PuyoPair.cpp
# )
# 
# # 実行ファイルを作成
# add_executable(puyoGame ${SOURCE})
# 
# # ヘッダファイルのディレクトリを追加
# target_include_directories(puyoGame PRIVATE
#     ${PROJECT_SOURCE_DIR}/include
# )
# 
# ###
# # SDL2 の自動検出
# ###
# find_package(SDL2 REQUIRED)
# if(SDL2_FOUND)
#     message(STATUS "Found SDL2 in ${SDL2_INCLUDE_DIRS}")
#     target_include_directories(puyoGame PRIVATE ${SDL2_INCLUDE_DIRS})
#     target_link_libraries(puyoGame PRIVATE ${SDL2_LIBRARIES})
# else()
#     message(FATAL_ERROR "SDL2 not found!")
# endif()
# 
# ###
# # SDL2_image の自動検出
# ###
# find_package(SDL2_image REQUIRED)
# if(SDL2_IMAGE_FOUND)
#     message(STATUS "Found SDL2_image in ${SDL2_IMAGE_INCLUDE_DIRS}")
#     target_include_directories(puyoGame PRIVATE ${SDL2_IMAGE_INCLUDE_DIRS})
#     target_link_libraries(puyoGame PRIVATE ${SDL2_IMAGE_LIBRARIES})
# else()
#     message(FATAL_ERROR "SDL2_image not found!")
# endif()
# 
# # コンパイル時のオプションを追加
# target_compile_options(puyoGame PRIVATE -Wall -Wextra)

cmake_minimum_required(VERSION 3.13)
project(PuyoGame VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# ソースファイル指定
set(SOURCE
    src/main.cpp
    src/Game.cpp
    src/Board.cpp
    src/Puyo.cpp
    src/PuyoPair.cpp
)

add_executable(PuyoGame ${SOURCE})

target_include_directories(PuyoGame PRIVATE ${PROJECT_SOURCE_DIR}/include)

# SDL2を設定
find_package(SDL2 REQUIRED)
if(SDL2_FOUND)
    target_include_directories(PuyoGame PRIVATE ${SDL2_INCLUDE_DIRS})
    target_link_libraries(PuyoGame PRIVATE ${SDL2_LIBRARIES})
else()
    message(FATAL_ERROR "SDL2 not found!")
endif()

# SDL2_imageを設定
find_package(PkgConfig REQUIRED)
pkg_check_modules(SDL2IMAGE REQUIRED SDL2_image)

# インクルードディレクトリ追加
target_include_directories(PuyoGame PRIVATE ${SDL2IMAGE_INCLUDE_DIRS})
# リンクライブラリ追加
target_link_libraries(PuyoGame PRIVATE ${SDL2IMAGE_LIBRARIES})

# 警告オプション
target_compile_options(PuyoGame PRIVATE -Wall -Wextra)

