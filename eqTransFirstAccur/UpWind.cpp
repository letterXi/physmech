#include <vector>
#include <fstream>
#include <string>
#include <iomanip>
#include <chrono>
#include <iostream>
#include <filesystem>

int main()
{
    int n = 600;
    int m = 1000;
    double h = 1.0 / (n - 1);
    double tau = 1.0 / (m - 1);
    std::vector<double> T(n, 0);

    std::string folder = "upwindSolve/";
    std::filesystem::create_directory(folder);
    for (int i = 0; i < n; i++)
    {
        if (i * h <= 0.1)
        {
            T[i] = 1;
        }
        else
        {
            break;
        }
    }

    std::ofstream file0(folder + "step_00000.csv");
    file0 << "x,T" << std::endl;
    for (int i = 0; i < n; i++)
    {
        file0 << std::fixed << std::setprecision(6) << i * h << "," << T[i] << std::endl;
    }
    file0.close();

    auto start = std::chrono::high_resolution_clock::now();
    for (int t = 1; t < m; t++)
    {
        if (t * tau > 0.9)
            break;
        std::vector<double> newT(n);
        for (int i = 1; i < n - 1; i++)
        {
            newT[i] = tau / h * (T[i - 1] - T[i]) + T[i];
        }
        T = newT;

        std::ostringstream filename;
        filename << folder << "step_" << std::setw(5) << std::setfill('0') << t << ".csv";

        std::ofstream file(filename.str());
        file << "x,T" << std::endl;
        for (int i = 0; i < n; i++)
        {
            file << std::fixed << std::setprecision(6) << i * h << "," << T[i] << std::endl;
        }
        file.close();
    }
    auto end = std::chrono::high_resolution_clock::now();

    std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << " ms" << std::endl;

    return 0;
}
