#include "AmgclSolver.hpp"
#include "CsrMatrix.hpp"
#include <chrono>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>
#include <filesystem>

int main() {
    int n = 1100;
    int m = 1000;
    double h = 1.0 / (n - 1);
    double tau = 1.0 / (m - 1);

    std::vector<size_t> addr;
    addr.reserve(n);
    std::vector<size_t> cols;
    cols.reserve(n * 3);
    std::vector<double> vals;
    vals.reserve(n * 3);
    std::vector<double> rhs(n);
    std::vector<double> T(n, 0);

    std::string folder = "kranknickSolve/";
    std::filesystem::create_directory(folder);
    for (int i = 0; i < n; i++) {
        if (i * h <= 0.1) {
            T[i] = 1;
        } else {
            break;
        }
    }

    addr.push_back(0);
    for (int i = 0; i < n; i++) {
        if (i == 0 || i == n - 1) {
            cols.push_back(i);
            vals.push_back(1);
        } else {
            cols.push_back(i - 1);
            vals.push_back(-1.0 / (4 * h));
            cols.push_back(i);
            vals.push_back(1.0 / tau);
            cols.push_back(i + 1);
            vals.push_back(1.0 / (4 * h));
        }
        addr.push_back(cols.size());
    }

    CsrMatrix mat(std::move(addr), std::move(cols), std::move(vals));

    std::ofstream file0(folder + "step_00000.csv");
    file0 << "x,T" << std::endl;
    for (int i = 0; i < n; i++) {
        file0 << std::fixed << std::setprecision(6) << i * h << "," << T[i] << std::endl;
    }
    file0.close();

    AmgclSolver solver;
    solver.set_matrix(mat);
    auto start = std::chrono::high_resolution_clock::now();
    for (int t = 1; t < m; t++) {
        if (t * tau > 0.9)
            break;
        for (int i = 0; i < n; i++) {
            if (i == 0 || i == n - 1)
                rhs[i] = 0;
            else {
                rhs[i] = (T[i] / tau + 1.0 / (4 * h) * (T[i - 1] - T[i + 1]));
            }
        }

        solver.solve(rhs, T);
        std::ostringstream filename;
        filename << folder << "step_" << std::setw(5) << std::setfill('0') << t << ".csv";

        std::ofstream file(filename.str());
        file << "x,T" << std::endl;
        for (int i = 0; i < n; i++) {
            file << std::fixed << std::setprecision(6) << i * h << "," << T[i] << std::endl;
        }
        file.close();
    }
    auto end = std::chrono::high_resolution_clock::now();

    std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << " ms" << std::endl;

    return 0;
}
