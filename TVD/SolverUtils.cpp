#include "SolverUtils.hpp"
#include <iomanip>
#include <cmath>
#include <filesystem>
#include <fstream>
#include <sstream>

void write_frame(size_t time, const std::vector<double> &u, double h, const std::string&  path)
{
	std::ostringstream oss;
	oss << "frame_" << std::setw(10) << std::setfill('0') << time << ".txt";
	std::ofstream file(path + oss.str());
	if (file.is_open())
	{
		file << "x,T" << std::endl;
		for(size_t i = 0; i < u.size(); i++)
			file << h * static_cast<double>(i) << ',' << u[i] << std::endl;
	}
	file.close();
}

double initial_condition(double x)
{
	if (x <= 0.1)
		return 1.0;
	return 0.0;
}

double minmodLimiter(double r)
{
	if (std::isinf(r) || std::isnan(r))
		return 0.0;
	return std::max(0.0, std::min(1.0, r));
}

double vanleerLimiter(double r)
{
	if (std::isinf(r) || std::isnan(r))
		return 0.0;
	return r <= 0 ? 0 : (r + std::abs(r)) / (1 + std::abs(r));
}

double superbeeLimiter(double r)
{
	if (std::isinf(r) || std::isnan(r))
		return 0.0;
	return std::max(0.0, std::max(std::min(2.0 * r, 1.0), std::min(r, 2.0)));

}

void solver(size_t t_points, size_t n_points, double tau, double h, const std::string& path, std::function<double(double)> limiter)
{
	std::vector<double> u(n_points, 0.0);
	std::filesystem::create_directory(path);
	for(size_t i = 0; i < n_points; i++)
	{
		u[i] = initial_condition(static_cast<double>(i)*h);
	}
	write_frame(0, u, h, path);
	for(size_t t = 1; t < t_points; t++)
	{
		if (static_cast<double>(t) * tau > 0.9)
			break;
		std::vector<double> newu(n_points);
		newu[1] = u[1] - tau / h * (u[1] - u[0]);
		newu[n_points - 2] = u[n_points - 2] - tau / h * (u[n_points - 2] - u[n_points - 3]); 
		for(size_t i = 2; i < n_points - 2; i++)
		{
			double denominator_plus = u[i+1] - u[i];
			double r_plus =  std::abs(denominator_plus) < 1e-12 ? 0.0 : (u[i] - u[i-1]) / denominator_plus;
	
			double denominator_minus = u[i] - u[i-1];
			double r_minus = std::abs(denominator_minus) < 1e-12 ? 0.0 : (u[i-1] - u[i-2]) / denominator_minus;
	
			double phi_plus = limiter(r_plus);
			double phi_minus = limiter(r_minus);
		
			double F_plus = u[i] - phi_plus * (u[i] - (u[i+1] + u[i]) / 2);	
			double F_minus = u[i-1] - phi_minus * (u[i-1] - (u[i] + u[i-1]) / 2);

			newu[i] = u[i] - tau / h * (F_plus - F_minus);
		}
		write_frame(t, u, h, path);
		u = newu;
	}
}
