
#include "plotter.hpp"

#include <iostream>
#include <string>
#include <vector>
#include <limits>

int main() {
    std::cout << "====================================\n";
    std::cout << "   PROGRAM GRAFIK FUNGSI KALKULUS 2\n";
    std::cout << "====================================\n\n";

    std::string formula;
    double x1, x2, density;

    std::cout << "Masukkan fungsi f(x): ";
    std::getline(std::cin, formula);

    std::cout << "Batas bawah X (x1): ";
    std::cin >> x1;

    std::cout << "Batas atas X (x2): ";
    std::cin >> x2;

    std::cout << "Interval titik (D): ";
    std::cin >> density;

    std::cout << "\nMenghitung titik grafik...\n";

    std::vector<Point> points = Plotter::generatePoints(
        x1,
        x2,
        density,
        formula
    );

    if (points.empty()) {
        std::cout << "Tidak ada titik yang berhasil dihitung.\n";
        return 1;
    }

    if (!Plotter::saveData(points, "UTS/data/points.dat")) {
        return 1;
    }

    std::cout << "\nPerhitungan berhasil!\n";
    std::cout << "Jumlah titik: " << points.size() << "\n";
    std::cout << "Data tersimpan di UTS/data/points.dat\n";

    return 0;
}
