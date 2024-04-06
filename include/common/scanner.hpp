#pragma once

#include <map>
#include <string>
#include <variant>

namespace common {

	using scanner_variant = std::variant<char *, unsigned char*, int*, unsigned int*, long*, unsigned long*, long long*, unsigned long long*, std::string*>;
	using scanner_map = std::map<size_t, scanner_variant>;

	size_t scan(const std::string& s, const scanner_map& m);
}
