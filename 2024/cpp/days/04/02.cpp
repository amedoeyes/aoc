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
			if (grid[(i * height) + j] == 'A') {
				if ((i == 0 || i == height - 1) || (j == 0 || j == width - 1)) {
					continue;
				}
				const char ne = grid[((i - 1) * width) + (j + 1)];
				const char nw = grid[((i - 1) * width) + (j - 1)];
				const char se = grid[((i + 1) * width) + (j + 1)];
				const char sw = grid[((i + 1) * width) + (j - 1)];
				if (((nw != 'M' || se != 'S') && (nw != 'S' || se != 'M')) ||
						((ne != 'M' || sw != 'S') && (ne != 'S' || sw != 'M'))) {
					continue;
				}
				++sum;
			}
		}
	}

	std::println("{}", sum);

	return 0;
}
