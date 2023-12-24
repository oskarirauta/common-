#include <iostream>
#include <algorithm>
#include <utility>
#include <sstream>
#include <string>
#include <cmath>
#include <filesystem>

#include "common.hpp"

namespace common {

	bool has_prefix(const std::string str, const std::string prefix) {

		return ((prefix.length() <= str.length()) &&
			std::equal(prefix.begin(), prefix.end(), str.begin()));
	}

	bool has_suffix(const std::string str, const std::string suffix) {

		return ((suffix.length() <= str.length()) &&
			str.find(suffix, str.size() - suffix.size()) != std::string::npos);
	}

	std::string str_first(const std::string str, char delim) {

		std::stringstream ss(str);
		std::string ret;
		while ( std::getline(ss, ret, delim)) break;
		return ret;
	}

	std::string trim(std::string &str, const std::string trimchars) {

		if ( str.empty() || trimchars.empty()) return str;

		for ( const char &ch : trimchars )
			str.erase(std::remove(str.begin(), str.end(), ch), str.end());

		return str;
	}

	std::string trim(const std::string &str, const std::string trimchars) {

		std::string s = str;
		return common::trim(s, trimchars);
	}

	std::vector<std::string> lines(const std::string &str, char delim, const std::string trimchars) {

		std::vector<std::string> elems;
		if ( str.empty()) return elems;
		if ( str.find(delim) == std::string::npos) {
			std::string item = str;
			for ( const char &ch : trimchars )
				item.erase(std::remove(item.begin(), item.end(), ch), item.end());
			elems.push_back(item);
			return elems;
		}

		std::stringstream ss(str);
		std::string item;

		while ( std::getline(ss, item, delim)) {
			if ( !trimchars.empty())
				for ( const char &ch : trimchars )
					item.erase(std::remove(item.begin(), item.end(), ch), item.end());
			elems.push_back(item);
		}

		return elems;
	}

	std::vector<std::string> split(const std::string &str, char delim, const std::string trimchars) {

		std::vector<std::string> elems;
		if ( str.empty()) return elems;

		std::stringstream ss(str);
		std::string item;

		while ( std::getline(ss, item, delim)) {
			if ( !trimchars.empty())
				for ( const char &ch : trimchars )
					item.erase(std::remove(item.begin(), item.end(), ch), item.end());
			elems.push_back(item);
		}

		elems.erase(std::remove_if(elems.begin(), elems.end(),
			[](const std::string& s) { return s.empty(); }),
			elems.end());

		return elems;

	}

	std::string to_lower(std::string &str) {

		for ( auto& ch : str )
			if ( std::isupper(ch))
				ch ^= 32;
		return str;
	}

	std::string to_lower(const std::string &str) {
		std::string s = str;
		return common::to_lower(s);
	}

	std::string to_upper(std::string &str) {

		for ( auto& ch : str )
			if ( std::islower(ch))
				ch &= ~32;
		return str;
	}

	std::string to_upper(const std::string &str) {
		std::string s = str;
		return common::to_upper(s);
	}

	std::string join_vector(const std::vector<std::string> v, const std::string delimeter) {

		std::string result;

                if (auto i = v.begin(), e = v.end(); i != e) {
                        result += *i++;
                        for (; i != e; ++i) result.append(delimeter).append(*i);
                }

		return result;
	}

	std::string c_tostr(const char *str) {

		std::string str2(str);
		return str2;
	}

	bool is_number(const std::string& s) {
		return !s.empty() && std::find_if(s.begin(),
			s.end(), [](unsigned char c) { return !std::isdigit(c); }) == s.end();
	}

	bool is_hex(std::string const& s) {
		return s.compare(0, 2, "0x") == 0
			&& s.size() > 2
			&& s.find_first_not_of("0123456789abcdefABCDEF", 2) == std::string::npos;
	}

	bool is_whitespace(const char& ch) {
		return ( ch == ' ' || ch == '\t' || ch == '\n' || ch == '\r' || ch == '\f' || ch == '\v' );
	}

	bool is_whitespace(const std::string& s) {
		return !s.empty() && is_whitespace(s.front());
	}

	bool is_space(const char& ch) {
		return ch == ' ' || ch == '\t';
	}

        bool is_space(const std::string& s) {
		return !s.empty() && is_space(s.front());
	}

        bool is_digit(const char& ch) {
		return ch >= '0' && ch <= '9';
	}

        bool is_digit(const std::string& s) {
		return !s.empty() && is_digit(s.front());
	}

        bool is_alpha(const char& ch) {
		return ( ch >= 'A' && ch <= 'Z' ) || ( ch >= 'a' && ch <= 'z' ) || ch == '_';
	}

        bool is_alpha(const std::string& s) {
		return !s.empty() && is_alpha(s.front());
	}

        bool is_alnum(const char& ch) {
		return is_alpha(ch) || is_digit(ch);
	}

        bool is_alnum(const std::string& s) {
		return !s.empty() && is_alnum(s.front());
	}

        const std::string erase_prefix(std::string& s, size_t n) {

		if ( s.empty() || n == 0 )
			return "";

		std::string r;

		if ( r = s.substr(0, n > s.size() ? s.size() : n); !r.empty())
			s.erase(0, r.size());

		return r;
	}

        const char erase_front(std::string &s) {

		if ( !s.empty()) {
			char ch = s.front();
			s.erase(0, 1);
			return ch;
		} else return 0;
	}

        const std::string to_string(const double& d) {

		std::stringstream ss;
		ss << d;
		return ss.str();
	}

	const std::string unquoted(const std::string& s, bool trimmed) {

		std::string r = trimmed ? trim_ws(s) : s;

		if ( r.empty())
			return r;

		if ( trimmed ) {

			if ( r.front() == '\'' && r.back() == '\'' ) {

				r.erase(0, 1);
				r.pop_back();
			} else if ( r.front() == '"' && r.back() == '"' ) {

				r.erase(0, 1);
				r.pop_back();
			}

			return r;
		}

		int i1 = -1;
		int i2 = -1;
		std::string ws = " \t\r\f\v";

		for ( size_t i = 0; i < r.size(); i++ ) {

			if ( ws.find_first_of(r.at(i)) == std::string::npos && (
				r.at(i) == '\'' || r.at(i) == '"' )) {

				i1 = i;
				break;
			}
		}

		if ( i1 == -1 )
			return r;

		for ( size_t i = r.size() - 1; i > 0; i++ ) {

			if ( ws.find_first_of(r.at(i)) == std::string::npos &&
				i != (size_t)i1 && r.at(i) == r.at(i1) && (
				r.at(i) == '\'' || r.at(i) == '"' )) {

					i2 = i;
					break;
			}
		}

		if ( i2 > i1 ) {

			r.erase(i2, 1);
			r.erase(i1, 1);
		}

		return r;
	}

	const std::string unquoted(std::string& s, bool trimmed) {
		s = unquoted(std::as_const(s));
		return s;
	}


	std::string trim_leading(const std::string str, int count) {

		if ( count < 1 )
			return str;

		if ( (size_t)count > str.size())
			count = str.size();

		std::string ret = str;
		ret.erase(0, count);
		return ret;
	}

	double round(double val) {
		return val < 0 ? std::ceil(val - 0.5) : std::floor(val + 0.5);
	}

	std::string memToStr(double amount, bool gigabytes) {

		std::ostringstream res;
		double value = amount;
		uint8_t valuetype = 0;

		if ( value >= 1024 ) {
			value = common::round(value / 1024);
			valuetype = 1;
			if ( value >= 1024 ) {
				value = common::round(value / 1024);
				valuetype = 2;
				if ( gigabytes && value >= 1024 ) {
					value = round((value / 1024) * 100.0 ) / 100.0;
					valuetype = 3;
				}
			}
		}

		res.precision(valuetype == 3 ? 2 : 0);
		res << std::fixed << value;

		switch ( valuetype ) {
			case 0: res << "b"; break;
			case 1: res << "kb"; break;
			case 2: res << "mb"; break;
			case 3: res << "gb"; break;
		}

		return res.str();
	}

	std::filesystem::path selfexe() {
		return std::filesystem::exists("/proc/self/exe") &&
			std::filesystem::is_symlink("/proc/self/exe") ?
				std::filesystem::read_symlink("/proc/self/exe") : "";

	}

	std::filesystem::path selfpath() {
		return std::filesystem::exists("/proc/self/exe") &&
			std::filesystem::is_symlink("/proc/self/exe") ?
				std::filesystem::read_symlink("/proc/self/exe").parent_path() : "";
	}

	std::filesystem::path selfbasename() {
		return std::filesystem::exists("/proc/self/exe") &&
			std::filesystem::is_symlink("/proc/self/exe") ?
				std::filesystem::read_symlink("/proc/self/exe").filename() : "";
	}

}
