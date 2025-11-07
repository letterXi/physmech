#include <cmath>
#include <vector>
#include <string>
#include "SolverUtils.hpp"
#include <iostream>

int main()
{
	size_t t_points = 1000;
	double c = 0.1;
	double tau = 1.0 / static_cast<double>(t_points);
	size_t n_points = static_cast<size_t>(std::ceil(c * static_cast<double>(t_points)));
	double h = 1.0 / static_cast<double>(n_points - 1);
	std::cout << "c = " << c << std::endl;
	solver(t_points, n_points, tau, h, "minmodSolve/", minmodLimiter);
	std::cout << "minmod done" << std::endl;
	solver(t_points, n_points, tau, h, "vanleerSolve/", vanleerLimiter);
	std::cout << "vanleer done" << std::endl;
	solver(t_points, n_points, tau, h, "superbeeSolve/", superbeeLimiter);
	std::cout << "superbee done" << std::endl << std::endl;
	return 0;
}
