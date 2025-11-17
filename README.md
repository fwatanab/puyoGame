# PuyoGame

A simple Puyo Puyo clone built using C++ and SDL2. This project demonstrates fundamental game development concepts, including rendering, input handling, and game logic.

## Features

- Puyo Puyo-style gameplay
- Basic rendering using SDL2
- Cross-platform compatibility via Docker
- Modular code structure for easy extension

---

## Prerequisites

To build and run this project, you need:

- **Docker**: To ensure a consistent development environment
- **Docker Compose**: For easy service management

---

## Getting Started

### Clone the Repository

```bash
git clone https://github.com/fwatanab/puyoGame.git
cd puyogame
```

## Build and Run with Docker

### Quick start
1. ビルドと起動:
```bash
docker compose -f docker/docker-compose.yml up --build
```
コンテナが起動すると自動的に `cmake` でビルド済みの `./build/PuyoGame` が実行されます。

2. 既存コンテナに入って自分でコマンドを叩きたい場合:
```bash
docker compose -f docker/docker-compose.yml exec puyogame /bin/bash
# 例: /app/build/PuyoGame
```

3. 停止とクリーンアップ:
```bash
docker compose -f docker/docker-compose.yml down --volumes --remove-orphans
```

`docker/docker-compose.yml` は `/app` にホストのワークスペースをマウントし、エントリーポイントで `cmake -S . -B build && cmake --build build` を自動実行します。`FORCE_REBUILD=1` を環境変数に指定すると毎回フルリビルドが走ります。

### ディスプレイ設定
- ホストの X11 を使ってウィンドウを表示したい場合は、ホスト側で `DISPLAY` と `/tmp/.X11-unix` をエクスポートしてください（macOS なら XQuartz、Windows なら X410/VcXsrv などを利用）。例:  
  ```bash
  export DISPLAY=host.docker.internal:0
  xhost +localhost
  docker compose -f docker/docker-compose.yml up --build
  ```
- `DISPLAY` が未設定、もしくはソケットにアクセスできない状況ではコンテナ内で自動的に `xvfb-run` を起動し、仮想ディスプレイ上で SDL を実行します（FORCE_HEADLESS=1 で明示的に指定可能）。ヘッドレス実行は可視化されませんが、CI や自動テスト用途では便利です。
- 画面サイズを変えたい場合は `XVFB_RESOLUTION=1280x720x24` のように指定してください。

Makefile のラッパーを使いたい場合は `make build` などもそのまま利用できますが、内部的には上記 compose ファイルを呼び出すようにしてください。
---

## Development
### Running Locally (Optional)
If you prefer to run the project without Docker, ensure you have the following installed:

- SDL2
- SDL2_image  

Install the required dependencies:

```bash
sudo apt-get update && sudo apt-get install -y \
    build-essential \
    cmake \
    libsdl2-dev \
    libsdl2-image-dev
```
Then build and run the project:

```bash
mkdir -p build
cd build
cmake ..
cmake --build .
./PuyoGame
```
---

## Troubleshooting

### Common Errors

1. SDL2_image not found
- Ensure libsdl2-image-dev is installed or use pkg-config in CMakeLists.txt.
2. Docker issues
- Ensure Docker is running and your user has permissions to run Docker commands.
3. Display not working
- Ensure X11 forwarding is enabled or a compatible display environment is available.
