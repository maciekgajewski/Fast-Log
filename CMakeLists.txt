set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -std=c++14")

add_executable(log_example
	main.cc
	logger.h logger.cc
)
