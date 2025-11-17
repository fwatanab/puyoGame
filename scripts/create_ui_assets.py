#!/usr/bin/env python3
import os
import struct
import subprocess
import shutil
import zlib

ASSETS_DIR = os.path.join(os.path.dirname(__file__), "..", "assets", "images")


def write_png(path, width, height, pixels):
    """Write a simple RGBA PNG using only the standard library."""
    def chunk(tag, data):
        data_crc = zlib.crc32(tag + data) & 0xFFFFFFFF
        return struct.pack(">I", len(data)) + tag + data + struct.pack(">I", data_crc)

    raw_rows = []
    for row in pixels:
        raw = bytearray()
        for r, g, b, a in row:
            raw.extend((r, g, b, a))
        raw_rows.append(b"\x00" + bytes(raw))
    raw_image_data = b"".join(raw_rows)
    compressed = zlib.compress(raw_image_data, level=9)

    ihdr = struct.pack(">IIBBBBB", width, height, 8, 6, 0, 0, 0)

    with open(path, "wb") as png:
        png.write(b"\x89PNG\r\n\x1a\n")
        png.write(chunk(b"IHDR", ihdr))
        png.write(chunk(b"IDAT", compressed))
        png.write(chunk(b"IEND", b""))


def lerp(a, b, t):
    return int(a + (b - a) * t)


def make_panel(width, height, top_color, bottom_color, border_color, accent_color, glow=False):
    pixels = []
    for y in range(height):
        row = []
        ty = y / max(height - 1, 1)
        for x in range(width):
            tx = x / max(width - 1, 1)
            r = lerp(top_color[0], bottom_color[0], ty)
            g = lerp(top_color[1], bottom_color[1], ty)
            b = lerp(top_color[2], bottom_color[2], ty)
            if glow:
                influence = max(0.0, 0.5 - abs(0.5 - tx))
                r = min(255, int(r + accent_color[0] * influence))
                g = min(255, int(g + accent_color[1] * influence))
                b = min(255, int(b + accent_color[2] * influence))
            row.append([r, g, b, 255])
        pixels.append(row)

    # borders
    for x in range(width):
        pixels[0][x] = [*border_color, 255]
        pixels[height - 1][x] = [*border_color, 255]
    for y in range(height):
        pixels[y][0] = [*border_color, 255]
        pixels[y][width - 1] = [*border_color, 255]

    # accent separators
    mid = height // 2
    for x in range(10, width - 10):
        pixels[mid][x] = [*accent_color, 255]
    return pixels


def make_next_panel(width, height, base_color, accent_color, border_color):
    pixels = []
    for y in range(height):
        row = []
        ty = y / max(height - 1, 1)
        for x in range(width):
            tx = x / max(width - 1, 1)
            gradient = 0.3 + 0.7 * ty
            r = int(base_color[0] * gradient)
            g = int(base_color[1] * gradient)
            b = int(base_color[2] * gradient)
            vignette = (abs(0.5 - tx) + abs(0.5 - ty)) * 0.4
            r = max(0, min(255, int(r * (1 - vignette) + accent_color[0] * vignette)))
            g = max(0, min(255, int(g * (1 - vignette) + accent_color[1] * vignette)))
            b = max(0, min(255, int(b * (1 - vignette) + accent_color[2] * vignette)))
            row.append([r, g, b, 240])
        pixels.append(row)

    for x in range(width):
        pixels[0][x] = [*border_color, 255]
        pixels[height - 1][x] = [*border_color, 255]
    for y in range(height):
        pixels[y][0] = [*border_color, 255]
        pixels[y][width - 1] = [*border_color, 255]

    return pixels


def make_wall_texture(width, height, base_top, base_bottom, neon_color, grid_spacing=12):
    pixels = []
    for y in range(height):
        row = []
        for x in range(width):
            ty = y / max(height - 1, 1)
            tx = x / max(width - 1, 1)
            r = lerp(base_top[0], base_bottom[0], ty)
            g = lerp(base_top[1], base_bottom[1], ty)
            b = lerp(base_top[2], base_bottom[2], ty)

            diag = (tx + ty) * 0.5
            r = min(255, int(r + 20 * diag))
            g = min(255, int(g + 25 * diag))
            b = min(255, int(b + 35 * diag))

            glow = 0
            if x % grid_spacing == 0 or y % grid_spacing == 0:
                glow = 0.7
            elif x % grid_spacing == grid_spacing // 2 or y % grid_spacing == grid_spacing // 2:
                glow = 0.4

            if glow > 0:
                r = int((1 - glow) * r + glow * neon_color[0])
                g = int((1 - glow) * g + glow * neon_color[1])
                b = int((1 - glow) * b + glow * neon_color[2])

            row.append([r, g, b, 255])
        pixels.append(row)
    return pixels


def reencode_png(path):
    if not shutil.which("sips"):
        return
    tmp_path = f"{path}.tmp"
    try:
        subprocess.run(["sips", "-s", "format", "png", path, "--out", tmp_path], check=True, stdout=subprocess.DEVNULL, stderr=subprocess.DEVNULL)
        os.replace(tmp_path, path)
    except Exception:
        if os.path.exists(tmp_path):
            os.remove(tmp_path)

def ensure_assets_dir():
    os.makedirs(ASSETS_DIR, exist_ok=True)


def main():
    ensure_assets_dir()
    hud_panel = make_panel(
        width=360,
        height=240,
        top_color=(32, 24, 66),
        bottom_color=(58, 45, 118),
        border_color=(255, 197, 92),
        accent_color=(255, 221, 149),
        glow=True,
    )
    hud_panel_path = os.path.join(ASSETS_DIR, "hud_panel.png")
    write_png(hud_panel_path, 360, 240, hud_panel)
    reencode_png(hud_panel_path)

    next_panel = make_next_panel(
        width=240,
        height=280,
        base_color=(30, 90, 120),
        accent_color=(90, 200, 255),
        border_color=(255, 255, 255),
    )
    next_panel_path = os.path.join(ASSETS_DIR, "hud_next_panel.png")
    write_png(next_panel_path, 240, 280, next_panel)
    reencode_png(next_panel_path)
    print(f"Generated {hud_panel_path} and {next_panel_path}")

    wall_texture = make_wall_texture(
        width=128,
        height=128,
        base_top=(20, 35, 60),
        base_bottom=(45, 70, 110),
        neon_color=(80, 220, 255),
        grid_spacing=16,
    )
    wall_path = os.path.join(ASSETS_DIR, "wall.png")
    write_png(wall_path, 128, 128, wall_texture)
    reencode_png(wall_path)
    print(f"Generated {wall_path}")


if __name__ == "__main__":
    main()
