
#include "plotter.hpp"
#include "function.hpp"

#include <cstdlib>
#include <fstream>
#include <cmath>
#include <iostream>
#include <iomanip>

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

bool Plotter::plotGraph(
    const std::string& dataFile,
    const std::string& formula
) {
    // Implementasi Gnuplot akan dibuat pada tahap berikutnya.
    return false;
}
