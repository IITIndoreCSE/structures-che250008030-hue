#include <iostream>
#include <cmath>
#include <fstream>

using namespace std;

// Define Point struct
struct Point {
    double x;
    double y;
};

void print_point_rotation(double x_before, double y_before,
                          double theta, double x_after, double y_after) {
    cout << "Before rotation: (x=" << x_before << ", y=" << y_before << ")\n";
    cout << "After rotation (θ=" << theta << " rad): "
         << "(x=" << x_after << ", y=" << y_after << ")\n";
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        cerr << "Usage: " << argv[0] << " <input_file>" << endl;
        return 1;
    }

    ifstream input(argv[1]);
    if (!input) {
        cerr << "Error opening " << argv[1] << endl;
        return 1;
    }

    // Declare points and angle
    Point p, pivot;
    double theta;

    // Read input: x, y, theta, px, py
    input >> p.x >> p.y >> theta >> pivot.x >> pivot.y;

    // Translate point relative to pivot
    double translated_x = p.x - pivot.x;
    double translated_y = p.y - pivot.y;

    // Perform rotation
    double rotated_x = translated_x * cos(theta) - translated_y * sin(theta);
    double rotated_y = translated_x * sin(theta) + translated_y * cos(theta);

    // Translate back
    double final_x = rotated_x + pivot.x;
    double final_y = rotated_y + pivot.y;

    // Print result
    print_point_rotation(p.x, p.y, theta, final_x, final_y);

    return 0;
}
