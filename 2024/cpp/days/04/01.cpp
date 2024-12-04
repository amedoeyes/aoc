#include <cctype>
#include <cstdint>
#include <cstdlib>
#include <fstream>
#include <print>
#include <string>

auto main(int /*argc*/, char** argv) -> int {
	std::ifstream file(argv[1]);

	std::string grid;
	uint64_t width = 0;
	uint64_t height = 0;
	for (std::string line; std::getline(file, line);) {
		++height;
		width = line.size();
		grid += line;
	}

	int64_t sum = 0;
	for (size_t i = 0; i < height; ++i) {
		for (size_t j = 0; j < width; ++j) {
			for (int8_t dy = -1; dy <= 1; ++dy) {
				for (int8_t dx = -1; dx <= 1; ++dx) {
					if (dx == 0 && dy == 0) {
						continue;
					}
					bool found = true;
					for (size_t k = 0; k < 4; k++) {
						const size_t di = i + (k * dy);
						const size_t dj = j + (k * dx);
						if (di >= height || dj >= width || grid[(di * width) + dj] != "XMAS"[k]) {
							found = false;
							break;
						}
					}
					if (found) {
						++sum;
					}
				}
			}
		}
	}

	std::println("{}", sum);

	return 0;
}
