# ベースイメージ
FROM ubuntu:22.04

# 必要なツールとライブラリをインストール
RUN apt-get update && apt-get install -y \
    build-essential \
    cmake \
    libsdl2-dev \
    libsdl2-image-dev \
    git \
    && apt-get clean


# 作業ディレクトリを設定
WORKDIR /app

# 必要なファイルをコピー
COPY . /app

# ビルド用ディレクトリを作成し、CMake 実行
RUN mkdir -p build && cd build && cmake .. && cmake --build .

# 実行可能ファイルをデフォルトで起動
CMD ["./build/PuyoGame"]
