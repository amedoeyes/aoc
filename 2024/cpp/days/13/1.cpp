#include <bits/stdc++.h>
#include <string_view>

static auto parse(std::string_view buffer) {
	return buffer //
			 | std::views::split('\n') //
			 | std::views::transform([](auto line) {
					 return std::string_view(line.begin(), line.size()); //
				 })
			 | std::views::filter([](std::string_view line) { return !line.empty(); })
			 | std::views::chunk(3) //
			 | std::views::transform([](auto chunk) {
					 auto it = chunk.begin();
					 auto a = *it;
					 auto b = *(++it);
					 auto p = *(++it);
					 auto parse_xy = [](std::string_view str, std::string_view xkey, std::string_view ykey) {
						 auto xstart = str.find(xkey) + xkey.size();
						 auto xend = str.find(',', xstart);
						 auto ystart = str.find(ykey) + ykey.size();
						 auto yend = str.size();
						 auto x = 0l;
						 auto y = 0l;
						 std::from_chars(str.data() + xstart, str.data() + xend, x);
						 std::from_chars(str.data() + ystart, str.data() + yend, y);
						 return std::pair(x, y);
					 };
					 return std::tuple(
						 parse_xy(a, "X+", "Y+"), parse_xy(b, "X+", "Y+"), parse_xy(p, "X=", "Y=")
					 );
				 });
}

auto main(int /*argc*/, char** argv) -> int {
	const auto buffer = (std::ostringstream() << std::ifstream(argv[1]).rdbuf()).str();

	auto sum = 0ul;
	for (auto [a, b, p] : parse(buffer)) {
		const auto [ax, ay] = a;
		const auto [bx, by] = b;
		const auto [px, py] = p;
		const auto det = (ax * by) - (ay * bx);
		const auto x = ((by * px) - (bx * py)) / det;
		const auto y = ((ax * py) - (ay * px)) / det;
		if ((ax * x) + (bx * y) == px && (ay * x) + (by * y) == py) sum += x * 3 + y;
	}

	std::println("{}", sum);
}
