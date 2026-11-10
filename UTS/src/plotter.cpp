#include "plotter.hpp"
#include "function.hpp"

#include <fstream>
#include <cmath>
#include <iostream>
#include <iomanip>
#include <limits>
#include <cstddef>
#include <process.h>
#include <cstdio>

// Fungsi untuk menghasilkan titik-titik grafik dari rumus matematika
std::vector<Point> Plotter::generatePoints(
    double x1,
    double x2,
    double density,
    const std::string& formula
) {
    std::vector<Point> points;

    // Validasi batas X
    if (!std::isfinite(x1) || !std::isfinite(x2)) {
        std::cerr << "Batas X harus berupa angka yang valid!\n";
        return points;
    }

    if (x1 >= x2) {
        std::cerr << "Batas bawah X harus lebih kecil dari batas atas X!\n";
        return points;
    }

    // Validasi interval
    if (!std::isfinite(density) || density <= 0) {
        std::cerr << "Interval harus lebih besar dari 0!\n";
        return points;
    }

    // Validasi rumus
    MathematicalFunction function;

    if (!function.setFormula(formula)) {
        std::cerr << function.getErrorMessage() << "\n";
        return points;
    }

    // Hitung jumlah titik sebelum melakukan perulangan
    long double intervalCount =
        (static_cast<long double>(x2) -
         static_cast<long double>(x1)) /
        static_cast<long double>(density);

    long double estimatedPoints = std::floor(intervalCount) + 1;

    const long double MAX_POINTS = 1000000;

    if (!std::isfinite(estimatedPoints) ||
        estimatedPoints > MAX_POINTS) {
        std::cerr << "Jumlah titik terlalu banyak!\n";
        std::cerr << "Maksimal 1.000.000 titik.\n";
        return points;
    }

    std::size_t totalPoints =
        static_cast<std::size_t>(estimatedPoints);

    points.reserve(totalPoints);

    // Hitung nilai fungsi
    for (std::size_t i = 0; i < totalPoints; i++) {
        double currentX = static_cast<double>(
            static_cast<long double>(x1) +
            static_cast<long double>(i) * density
        );

        if (currentX > x2) {
            break;
        }

        double currentY = function.evaluate(currentX);

        // Abaikan hasil yang tidak terdefinisi
        if (std::isfinite(currentY)) {
            points.push_back({currentX, currentY});
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

    // Menulis perintah Gnuplot ke dalam file script
    script << "set terminal qt size 1200,800 font 'Arial,12'\n";

    script << "set title 'Grafik Fungsi f(x)' font 'Arial,16' offset 0,-0.5\n";

    script << "set xlabel 'Sumbu X' font 'Arial,12' offset 0,-1\n";
    script << "set ylabel 'Sumbu Y' font 'Arial,12' offset -1,0\n";

    script << "set xtics font 'Arial,10'\n";
    script << "set ytics font 'Arial,10'\n";

    script << "set grid xtics ytics linewidth 1 dashtype 2\n";
    script << "set zeroaxis linewidth 1.5\n";

    script << "set border linewidth 1.5\n";

    script << "set tmargin 4\n";
    script << "set bmargin 5\n";
    script << "set lmargin 9\n";
    script << "set rmargin 4\n";

    script << "set autoscale\n";
    script << "set mouse\n";

    script << "set samples 1000\n";


    script << "plot '" << dataFile
           << "' using 1:2 with lines linewidth 3 "
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
