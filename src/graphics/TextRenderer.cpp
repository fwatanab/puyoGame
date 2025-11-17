#include "TextRenderer.hpp"

#include <array>
#include <cctype>
#include <initializer_list>
#include <unordered_map>

namespace {
constexpr int kGlyphWidth = 5;
constexpr int kGlyphHeight = 7;
using Glyph = std::array<uint8_t, kGlyphWidth * kGlyphHeight>;

Glyph glyphFromRows(std::initializer_list<const char*> rows) {
	Glyph glyph = {0};
	int rowIndex = 0;
	for (const char* row : rows) {
		if (rowIndex >= kGlyphHeight) {
			break;
		}
		for (int col = 0; col < kGlyphWidth; ++col) {
			char ch = row[col];
			glyph[rowIndex * kGlyphWidth + col] = (ch == '#' ? 1 : 0);
		}
		rowIndex++;
	}
	return glyph;
}

const std::unordered_map<char, Glyph>& glyphMap() {
	static const std::unordered_map<char, Glyph> glyphs = {
		{'0', glyphFromRows({
			".###.",
			"##.##",
			"##.##",
			"##.##",
			"##.##",
			"##.##",
			".###."
		})},
		{'1', glyphFromRows({
			"..#..",
			".##..",
			"..#..",
			"..#..",
			"..#..",
			"..#..",
			".###."
		})},
		{'2', glyphFromRows({
			".###.",
			"##.##",
			"...##",
			"..##.",
			".##..",
			"##...",
			"#####"
		})},
		{'3', glyphFromRows({
			".###.",
			"##.##",
			"...##",
			"..##.",
			"...##",
			"##.##",
			".###."
		})},
		{'4', glyphFromRows({
			"...##",
			"..###",
			".#.##",
			"#.###",
			"#####",
			"...##",
			"...##"
		})},
		{'5', glyphFromRows({
			"#####",
			"##...",
			"####.",
			"..###",
			"...##",
			"##.##",
			".###."
		})},
		{'6', glyphFromRows({
			"..##.",
			".##..",
			"##...",
			"####.",
			"##.##",
			"##.##",
			".###."
		})},
		{'7', glyphFromRows({
			"#####",
			"...##",
			"..##.",
			"..##.",
			".##..",
			".##..",
			".##.."
		})},
		{'8', glyphFromRows({
			".###.",
			"##.##",
			"##.##",
			".###.",
			"##.##",
			"##.##",
			".###."
		})},
		{'9', glyphFromRows({
			".###.",
			"##.##",
			"##.##",
			".####",
			"...##",
			"..##.",
			".##.."
		})},
		{'S', glyphFromRows({
			".####",
			"##...",
			"##...",
			".###.",
			"...##",
			"...##",
			"####."
		})},
		{'C', glyphFromRows({
			"..###",
			".##.#",
			"##...",
			"##...",
			"##...",
			".##.#",
			"..###"
		})},
		{'D', glyphFromRows({
			"####.",
			"##.##",
			"##.##",
			"##.##",
			"##.##",
			"##.##",
			"####."
		})},
		{'O', glyphFromRows({
			".###.",
			"##.##",
			"##.##",
			"##.##",
			"##.##",
			"##.##",
			".###."
		})},
		{'R', glyphFromRows({
			"####.",
			"##.##",
			"##.##",
			"####.",
			"##.#.",
			"##.##",
			"##.##"
		})},
		{'E', glyphFromRows({
			"#####",
			"##...",
			"##...",
			"####.",
			"##...",
			"##...",
			"#####"
		})},
		{'H', glyphFromRows({
			"##.##",
			"##.##",
			"##.##",
			"#####",
			"##.##",
			"##.##",
			"##.##"
		})},
		{'A', glyphFromRows({
			".###.",
			"##.##",
			"##.##",
			"#####",
			"##.##",
			"##.##",
			"##.##"
		})},
		{'I', glyphFromRows({
			"#####",
			"..#..",
			"..#..",
			"..#..",
			"..#..",
			"..#..",
			"#####"
		})},
		{'L', glyphFromRows({
			"##...",
			"##...",
			"##...",
			"##...",
			"##...",
			"##...",
			"#####"
		})},
		{'N', glyphFromRows({
			"##.##",
			"###.#",
			"###.#",
			"##.##",
			"##.##",
			"##.##",
			"##.##"
		})},
		{'B', glyphFromRows({
			"####.",
			"##.##",
			"##.##",
			"####.",
			"##.##",
			"##.##",
			"####."
		})},
		{'T', glyphFromRows({
			"#####",
			"..#..",
			"..#..",
			"..#..",
			"..#..",
			"..#..",
			"..#.."
		})},
		{'U', glyphFromRows({
			"##.##",
			"##.##",
			"##.##",
			"##.##",
			"##.##",
			"##.##",
			".###."
		})},
		{'X', glyphFromRows({
			"##.##",
			"##.##",
			".###.",
			"..#..",
			".###.",
			"##.##",
			"##.##"
		})},
		{',', glyphFromRows({
			".....",
			".....",
			".....",
			".....",
			"..#..",
			"..#..",
			".#..."
		})},
		{'?', glyphFromRows({
			".###.",
			"##.##",
			"...##",
			"..##.",
			"..#..",
			".....",
			"..#.."
		})}
	};
	return glyphs;
}
}

void TextRenderer::renderText(SDL_Renderer* renderer, const std::string& text, int x, int y, int scale, SDL_Color color) {
	if (renderer == nullptr || scale <= 0) {
		return;
	}

	const auto& glyphs = glyphMap();
	SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
	SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);

	int cursor = x;
	for (char ch : text) {
		if (ch == ' ') {
			cursor += (kGlyphWidth - 2) * scale;
			continue;
		}
		char key = static_cast<char>(std::toupper(static_cast<unsigned char>(ch)));
		std::unordered_map<char, Glyph>::const_iterator it = glyphs.find(key);
		if (it == glyphs.end()) {
			it = glyphs.find('?');
		}
		const Glyph& glyph = it->second;
		for (int row = 0; row < kGlyphHeight; ++row) {
			for (int col = 0; col < kGlyphWidth; ++col) {
				if (!glyph[row * kGlyphWidth + col]) {
					continue;
				}
				SDL_Rect pixel = {cursor + col * scale, y + row * scale, scale, scale};
				SDL_RenderFillRect(renderer, &pixel);
			}
		}
		cursor += (kGlyphWidth + 1) * scale;
	}
}
