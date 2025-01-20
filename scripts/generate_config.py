import json

# 入力設定ファイル
CONFIG_FILE = "config.json"
# 出力ヘッダファイル
OUTPUT_FILE = "include/GeneratedConfig.hpp"

def generate_header():
    try:
        # JSONファイルを読み込む
        with open(CONFIG_FILE, "r") as config_file:
            config = json.load(config_file)

        # ヘッダーファイルを生成
        with open(OUTPUT_FILE, "w") as header_file:
            header_file.write("#pragma once\n\n")
            header_file.write("// 自動生成された設定ヘッダーファイル\n")
            header_file.write("// config.json を編集して再コンパイルしてください。\n\n")

            # スクリーン設定
            header_file.write(f"#define SCREEN_WIDTH {config['screen']['resolution']['width']}\n")
            header_file.write(f"#define SCREEN_HEIGHT {config['screen']['resolution']['height']}\n")
            header_file.write(f"#define FULLSCREEN {str(config['screen']['fullscreen']).lower()}\n")

            # ボード設定
            header_file.write(f"#define BOARD_WIDTH {config['board']['width']}\n")
            header_file.write(f"#define BOARD_HEIGHT {config['board']['height']}\n")
            header_file.write(f"#define PUYO_SIZE {config['board']['puyo_size']}\n")
            header_file.write(f"#define MARGIN_TOP {config['board']['margin_top']}\n")
            header_file.write(f"#define MARGIN_SIDE {config['board']['margin_side']}\n")

            # ゲームプレイ設定
            header_file.write(f"#define DROP_INTERVAL {config['gameplay']['drop_interval']}\n")
            header_file.write(f"#define CHAIN_SPEED {config['gameplay']['chain_speed']}\n")
            header_file.write(f"#define GRAVITY_SPEED {config['gameplay']['gravity_speed']}\n")

            # テーマ設定
            themes = config['themes']
            header_file.write("\n// テーマ設定\n")
            header_file.write(f"#define BACKGROUND_IMAGE \"{themes['default']['background']}\"\n")

            puyo_colors = themes['default']['puyo_colors']
            for color, image_path in puyo_colors.items():
                # 各ぷよの色を定義
                macro_name = f"PUYO_{color.upper()}_IMAGE"
                header_file.write(f"#define {macro_name} \"{image_path}\"\n")

            print(f"Generated {OUTPUT_FILE} successfully.")
    except Exception as e:
        print(f"Error generating header: {e}")

if __name__ == "__main__":
    generate_header()

