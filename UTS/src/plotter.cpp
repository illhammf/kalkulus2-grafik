
#include "plotter.hpp"
#include "function.hpp"

#include <cstdlib>
#include <fstream>
#include <cmath>
#include <iostream>
#include <iomanip>
#include <process.h>
#include <cstdio>

std::vector<Point> Plotter::generatePoints(
    double x1,
    double x2,
    double density,
    const std::string& formula
) {
    std::vector<Point> points;

    MathematicalFunction function;

    if (!function.setFormula(formula)) {
        std::cerr << "Rumus matematika tidak valid!\n";
        return points;
    }

    if (density <= 0 || x1 >= x2) {
        std::cerr << "Rentang atau interval tidak valid!\n";
        return points;
    }

    for (double x = x1; x <= x2; x += density) {
        double y = function.evaluate(x);

        if (std::isfinite(y)) {
            points.push_back({x, y});
        }
    }

    return points;
}

bool Plotter::saveData(
    const std::vector<Point>& points,
    const std::string& filename
) {
    std::ofstream file(filename);

    if (!file.is_open()) {
        std::cerr << "Gagal membuat file data!\n";
        return false;
    }

    file << std::fixed << std::setprecision(6);

    for (const Point& point : points) {
        file << point.x << " " << point.y << "\n";
    }

    file.close();

    return true;
}

// Fungsi untuk memanggil Gnuplot dan menampilkan grafik

bool Plotter::plotGraph(
    const std::string& dataFile,
    const std::string& formula
) {
    const std::string scriptFile = "UTS/output/plot.gp";

    std::ofstream script(scriptFile);

    if (!script.is_open()) {
        std::cerr << "Gagal membuat script Gnuplot!\n";
        return false;
    }

    script << "set title 'Grafik Fungsi f(x)'\n";
    script << "set xlabel 'X'\n";
    script << "set ylabel 'Y'\n";
    script << "set grid\n";
    script << "set zeroaxis\n";
    script << "set border linewidth 1.5\n";
    script << "set samples 500\n";

    script << "plot '" << dataFile
           << "' using 1:2 with lines linewidth 2 "
           << "title 'f(x) = " << formula << "'\n";

    script.close();

    const char* gnuplotPath =
        "C:\\Program Files\\gnuplot\\bin\\gnuplot.exe";

    std::cout << "Menjalankan Gnuplot...\n";

    intptr_t result = _spawnl(
        _P_NOWAIT,
        gnuplotPath,
        "gnuplot",
        "-persist",
        scriptFile.c_str(),
        nullptr
    );

    if (result == -1) {
        perror("Gagal menjalankan Gnuplot");
        return false;
    }

    return true;
}
