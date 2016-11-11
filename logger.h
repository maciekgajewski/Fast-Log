#pragma once

#include <vector>
#include <ostream>

namespace Logger {
	
// == Public interface ==
	
// Will cosume all stored log data and render it to std::ostream
void Consume();
	

namespace Detail {

using FormatFunction = void(*)(std::ostream& stream, const char* buffer);

std::vector<char> gBuffer;
	
}

}

#define LOG(formatString, ...) \
	static_assert(CountPlaceholders(formatString) == sizeof_args(__VA_ARGS__), "Number of arguments mismatch"); \
	do { \
		Logger::Detail::WriteLog(formatString, ##__VA_ARGS__); \
	} while (false);
