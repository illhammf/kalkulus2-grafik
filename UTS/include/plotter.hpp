#ifndef PLOTTER_HPP
#define PLOTTER_HPP

#include <vector>
#include <string>

struct Point {
    double x;
    double y;
};

class Plotter {
public:
    static std::vector<Point> generatePoints(
        double x1,
        double x2,
        double density,
        const std::string& formula
    );

    static bool saveData(
        const std::vector<Point>& points,
        const std::string& filename
    );

    static bool plotGraph(
        const std::string& dataFile,
        const std::string& formula
    );
};

#endif
