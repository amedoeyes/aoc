#ifndef UTILITY_HPP
#define UTILITY_HPP

#include <filesystem>
#include <fstream>
#include <linux/limits.h>
#include <print>
#include <sys/types.h>
#include <unistd.h>
#include <vector>

auto get_exec_path() -> std::filesystem::path {
	std::array<char, PATH_MAX> buffer{};
	const ssize_t size = readlink("/proc/self/exe", buffer.data(), buffer.size());
	if (size == -1) {
		return "";
	}
	return buffer.data();
}

auto find_root(
	const std::filesystem::path& directory, const std::vector<std::string_view>& patterns
) -> std::filesystem::path {
	auto current = directory;
	while (!current.empty()) {
		for (const auto& pattern : patterns) {
			if (std::filesystem::exists(current / pattern)) {
				return current;
			}
		}
		current = current.parent_path();
	}
	return "";
}

auto readfile(const std::filesystem::path& path) -> std::ifstream {
	std::filesystem::path exec_path = get_exec_path();
	std::filesystem::path root_path = find_root(exec_path, {".clangd"});
	return root_path / path;
}

#endif // !UTILITY_HPP
