#ifndef file_HPP
#define file_HPP

#include <cstddef>
#include <cstdint>
#include <fcntl.h>
#include <filesystem>
#include <string>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>

class file {
public:
	file(const file&) = default;
	file(file&&) = default;
	auto operator=(const file&) -> file& = default;
	auto operator=(file&&) -> file& = default;
	explicit file(const std::filesystem::path& path) {
		_fd = open(path.c_str(), O_RDONLY);
		if (_fd < 0) throw std::runtime_error(std::format("Failed to open file: {}", path.string()));
		struct stat st{};
		if (fstat(_fd, &st) < 0) {
			close(_fd);
			throw std::runtime_error(std::format("Failed to stat file: {}", path.string()));
		}
		_size = st.st_size;
		_data = static_cast<char*>(mmap(nullptr, _size, PROT_READ, MAP_PRIVATE, _fd, 0));
		if (_data == MAP_FAILED) {
			close(_fd);
			throw std::runtime_error(std::format("Failed to mmap file: {}", path.string()));
		}
	}
	~file() {
		munmap(_data, _size);
		close(_fd);
	}

	[[nodiscard]] auto size() const -> size_t {
		return _size;
	}

	[[nodiscard]] auto data() const -> const char* {
		return _data;
	}

	[[nodiscard]] auto str() const -> std::string {
		return _data;
	}

private:
	int32_t _fd = -1;
	char* _data = nullptr;
	size_t _size = 0;
};

#endif // !file_HPP
