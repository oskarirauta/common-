#include <sstream>
#include <limits>

#include "common/scanner.hpp"

size_t common::scan(const std::string& s, const common::scanner_map& m) {

        std::stringstream ss(s + ( std::isspace(s.back()) ? "" : " "));
	size_t m_len = std::numeric_limits<std::streamsize>::max();
        size_t index = 0;
	size_t captured = 0;
	bool failed = false;

        for ( auto p : m ) {

		if ( index > p.first )
			continue;

                while ( p.first > 0 && index < p.first && !failed ) {

                        ss.ignore(m_len, ' ');

			if ( !ss.good() || ss.fail() || ss.bad())
				failed = true;
                        index++;
                }

		if ( failed || ss.eof())
			break;

		std::visit([&ss, &m_len, &captured, &failed](auto v) {

			ss >> *v;

			if ( !ss.good() || ss.fail() || ss.bad())
				failed = true;
			else captured++;

			if ( !ss.eof())
				ss.ignore(m_len, ' ');
		}, p.second);

		if ( failed )
			break;
		else index++;
        }

	return captured;
}
