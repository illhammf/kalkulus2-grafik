
#include "plotter.hpp"

#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <cctype>
#include <iomanip>
#include <algorithm>

// Membaca angka dengan validasi
bool readNumber(const std::string& prompt, double& value) {
    std::string input;

    std::cout << prompt;

    if (!std::getline(std::cin, input)) {
        return false;
    }

    try {
        std::size_t position = 0;
        value = std::stod(input, &position);

        // Pastikan tidak ada karakter tambahan
        std::size_t remaining = input.find_first_not_of(
            " \t\r\n", position
        );

        if (remaining != std::string::npos) {
            std::cout << "Input harus berupa angka!\n";
            return false;
        }

        if (!std::isfinite(value)) {
            std::cout << "Angka harus berupa nilai yang valid!\n";
            return false;
        }

        return true;

    } catch (...) {
        std::cout << "Input tidak valid! Masukkan angka.\n";
        return false;
    }
}

int main() {
    std::cout << "====================================\n";
    std::cout << "   PROGRAM GRAFIK FUNGSI KALKULUS 2\n";
    std::cout << "====================================\n\n";

    std::string formula;
    double x1, x2, density;

    std::cout << "Masukkan fungsi f(x): ";

    if (!std::getline(std::cin, formula)) {
        std::cout << "Gagal membaca rumus.\n";
        return 1;
    }

    if (formula.empty()) {
        std::cout << "Rumus tidak boleh kosong!\n";
        return 1;
    }

    if (!readNumber("Batas bawah X (x1): ", x1)) {
        return 1;
    }

    if (!readNumber("Batas atas X (x2): ", x2)) {
        return 1;
    }

    if (!readNumber("Interval titik (D): ", density)) {
        return 1;
    }

    std::cout << "\n====================================\n";
    std::cout << "       METODE PERHITUNGAN\n";
    std::cout << "====================================\n";

    std::cout << "Fungsi       : " << formula << "\n";
    std::cout << "Batas bawah  : " << x1 << "\n";
    std::cout << "Batas atas   : " << x2 << "\n";
    std::cout << "Interval     : " << density << "\n";

    std::cout << "\nRumus perhitungan:\n";
    std::cout << "x(i) = x1 + (i * D)\n";
    std::cout << "y(i) = f(x(i))\n";

    std::cout << "\nMenghitung titik grafik...\n";

    std::vector<Point> points = Plotter::generatePoints(
        x1,
        x2,
        density,
        formula
    );

    if (points.empty()) {
        std::cout << "\nTidak ada titik yang berhasil dihitung.\n";
        return 1;
    }

    // Menampilkan tabel hasil perhitungan
    std::cout << "\n";
    std::cout << "============================================================\n";
    std::cout << "              TABEL HASIL PERHITUNGAN FUNGSI\n";
    std::cout << "============================================================\n";

    std::cout << std::left
              << std::setw(10) << "No."
              << std::setw(20) << "Nilai X"
              << std::setw(25) << "Nilai Y"
              << "\n";

    std::cout << "------------------------------------------------------------\n";

    std::cout << std::fixed << std::setprecision(6);

    // Batas tampilan agar terminal tidak terlalu panjang
    const std::size_t DISPLAY_LIMIT = 100;

    std::size_t displayCount = std::min(
        points.size(),
        DISPLAY_LIMIT
    );

    for (std::size_t i = 0; i < displayCount; i++) {
        std::cout << std::left
                  << std::setw(10) << i + 1
                  << std::setw(20) << points[i].x
                  << std::setw(25) << points[i].y
                  << "\n";
    }

    if (points.size() > DISPLAY_LIMIT) {
        std::cout << "\n... "
                  << points.size() - DISPLAY_LIMIT
                  << " titik lainnya disimpan dalam file data.\n";
    }

    std::cout << "------------------------------------------------------------\n";
    std::cout << "Total titik valid: " << points.size() << "\n";
    std::cout << "============================================================\n\n";


    if (!Plotter::saveData(points, "UTS/data/points.dat")) {
        std::cout << "Gagal menyimpan data grafik.\n";
        return 1;
    }

    std::cout << "\nPerhitungan berhasil!\n";
    std::cout << "Jumlah titik valid: " << points.size() << "\n";
    std::cout << "Data tersimpan di UTS/data/points.dat\n";

    std::cout << "\nMembuka grafik...\n";

    if (!Plotter::plotGraph("UTS/data/points.dat", formula)) {
        std::cout << "Grafik gagal ditampilkan.\n";
        return 1;
    }

    std::cout << "Grafik berhasil ditampilkan!\n";

    return 0;
}
