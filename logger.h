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

// helper
template <typename... Types>
constexpr unsigned sizeof_args(Types&&...) { return sizeof...(Types); }

// helper
constexpr size_t CountPlaceholders(const char* formatString)
{
	return (formatString[0] == '\0') ? 0 : (
		(formatString[0] == '%' ? 1u : 0u) + CountPlaceholders(formatString + 1));
}

// write the given log line to a buffer
template <typename... Args>
void WriteLog(const char* formatString, const Args&... args)
{
	// TODO
}

} // ns detail

} // ns Logger

#define LOG(formatString, ...) \
	static_assert(Logger::Detail::CountPlaceholders(formatString) == Logger::Detail::sizeof_args(__VA_ARGS__), "Number of arguments mismatch"); \
	do { \
		Logger::Detail::WriteLog(formatString, ##__VA_ARGS__); \
	} while (false);
