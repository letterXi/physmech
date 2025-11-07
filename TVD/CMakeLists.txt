add_library(tvdlib STATIC SolverUtils.cpp SolverUtils.hpp) 
add_executable(solver
	main.cpp)
target_link_libraries(solver tvdlib)
