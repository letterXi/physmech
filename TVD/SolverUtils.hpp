#ifndef SOLVER_UTILS_HPP
#define SOLVER_UTILS_HPP
#include <string>
#include <vector>
#include <functional>

void write_frame(size_t time, const std::vector<double> &u, double h, const std::string&  path);

double initial_condition(double x);

double minmodLimiter(double r);

double vanleerLimiter(double r);

double superbeeLimiter(double r);

void solver(size_t t_points, size_t n_points, double tau, double h, const std::string& path, std::function<double(double)> limiter);

#endif
