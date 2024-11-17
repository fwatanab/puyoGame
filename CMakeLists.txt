# CMakeのバージョンを設定
cmake_minimum_required(VERSION 3.13)

# プロジェクト設定
project(puyoGame VERSION 1.0 LANGUAGES CXX)

# C++の標準バージョンを設定
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# ソースファイルを設定
set(SOURCE
	src/main.cpp
	src/Game.cpp
	src/SpriteSheet.cpp
	src/Board.cpp
	src/Puyo.cpp
	src/PuyoPair.cpp
	)

# 実行ファイルを作成
add_executable(puyoGame ${SOURCE})

# ヘッダファイルのディレクトリを追加↲
include_directories(${PROJECT_SOURCE_DIR}/include)

# SDL2のパッケージを探す
find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})
target_link_libraries(puyoGame ${SDL2_LIBRARIES})

# SDL2_imageのパッケージを探す
# find_package(SDL2_IMAGE REQUIRED)
# include_directories(${SDL2_IMAGE_INCLUDE_DIRS})
# target_link_libraries(puyoGame ${SDL2_IMAGE_LIBRARIES})

# SDL2_imageのパスを手動で指定
include_directories(/Users/sukakaedefutoshi/.brew/opt/sdl2_image/include)
link_directories(/Users/sukakaedefutoshi/.brew/opt/sdl2_image/lib)

# 手動でライブラリファイルを指定してリンクする
target_link_libraries(puyoGame /Users/sukakaedefutoshi/.brew/opt/sdl2_image/lib/libSDL2_image.dylib)

# コンパイル時のオプションを追加
target_compile_options(puyoGame PRIVATE -Wall -Wextra)
