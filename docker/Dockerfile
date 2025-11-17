# ベースイメージ
FROM debian:bookworm

# 必要パッケージのインストール
RUN apt-get update && apt-get install -y --no-install-recommends \
    build-essential \
    cmake \
    pkg-config \
    libx11-dev \
    libxext-dev \
    wget \
    tar \
    python3 \
    python3-pip \
    xvfb \
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

# SDL2_image および SDL2_ttf の依存関係をインストール
RUN apt-get update && apt-get install -y --no-install-recommends \
    libsdl2-image-dev \
    libsdl2-ttf-dev \
    libjpeg-dev \
    libpng-dev \
    libtiff-dev \
    && rm -rf /var/lib/apt/lists/*

# JSON関連ライブラリ
RUN apt-get update && apt-get install -y --no-install-recommends \
    libjsoncpp-dev \
    nlohmann-json3-dev \
    && apt-get clean && rm -rf /var/lib/apt/lists/*

# 作業ディレクトリを設定
WORKDIR /app

# プロジェクトファイルをコピー
COPY . /app

# ビルド手順
RUN mkdir -p build \
    && cd build \
    && cmake .. \
    && cmake --build . -- -j"$(nproc)"

COPY docker/entrypoint.sh /entrypoint.sh
RUN chmod +x /entrypoint.sh

ENTRYPOINT ["/entrypoint.sh"]
