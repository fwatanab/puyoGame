# ベースイメージ
FROM debian:bookworm

# 必要パッケージのインストール
RUN apt-get update && apt-get install -y \
    build-essential \
    cmake \
    pkg-config \
    libx11-dev \
    libxext-dev \
    wget \
    tar \
    && rm -rf /var/lib/apt/lists/*

# SDL2 のソースコードをダウンロードしてビルド
RUN wget https://www.libsdl.org/release/SDL2-2.28.0.tar.gz -O /tmp/SDL2.tar.gz \
    && tar -xzf /tmp/SDL2.tar.gz -C /tmp/ \
    && cd /tmp/SDL2-2.28.0 \
    && ./configure --disable-video-opengl --disable-video-opengles \
    && make -j4 \
    && make install \
    && cd / \
    && rm -rf /tmp/SDL2*

# SDL2_image の依存関係をインストール
RUN apt-get update && apt-get install -y \
    libsdl2-image-dev \
    libjpeg-dev \
    libpng-dev \
    libtiff-dev \
    && rm -rf /var/lib/apt/lists/*

# 作業ディレクトリを設定
WORKDIR /app

# プロジェクトファイルをコピー
COPY . /app

# ビルド手順
RUN mkdir -p build \
    && cd build \
    && cmake .. \
    && make -j4

# 実行可能ファイルをデフォルトで起動
CMD ["./build/PuyoGame"]
