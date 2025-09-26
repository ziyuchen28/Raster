#include <cstdint>
#include <vector>
#include <fstream>
#include <algorithm>
#include <cassert>
#include <iostream>

struct Color {
    uint8_t r, g, b;
};

struct Framebuffer {
    int w, h;
    std::vector<Color> pixels; // row-major

    Framebuffer(int W, int H) : w(W), h(H), pixels(w * h) {}

    void clear(Color c) {
        std::fill(pixels.begin(), pixels.end(), c);
    }

    void putPixel(int x, int y, Color c) {
        if (x < 0 || y < 0 || x >= w || y >= h) return;
        pixels[y * w + x] = c;
    }

    void writePPM(const char* path) const {
        std::ofstream f(path, std::ios::binary);
        f << "P6\n" << w << " " << h << "\n255\n";
        for (auto& p : pixels) {
            f.write(reinterpret_cast<const char*>(&p), 3);
        }
    }
};
