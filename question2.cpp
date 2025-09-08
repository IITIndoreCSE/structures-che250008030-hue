#include <iostream>
#include <fstream>
#include <string>
#include <cctype>

using namespace std;

struct Rectangle {
    double width;
    double height;
    double thickness;
    double density;
    string material;
};

void print_plate(int index, double width, double height,
                 double density, double mass, const char* material) {
    cout << "Plate[" << index << "]: "
         << "width=" << width << ", "
         << "height=" << height << ", "
         << "density=" << density << ", "
         << "mass=" << mass << ", "
         << "material=" << material << "\n";
}

// Helper function to skip empty lines
void skip_empty_lines(ifstream& input) {
    while (input && input.peek() == '\n') {
        input.ignore();
    }
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

    int num_plates;
    input >> num_plates;
    input.ignore(); // skip newline after number

    if (num_plates <= 0) {
        cerr << "Invalid number of plates: " << num_plates << endl;
        return 1;
    }

    Rectangle* plates = new Rectangle[num_plates];

    for (int i = 0; i < num_plates; ++i) {
        input >> plates[i].width
              >> plates[i].height
              >> plates[i].thickness
              >> plates[i].density;
        input.ignore(); // skip newline after density

        // Skip any empty lines before material
        skip_empty_lines(input);

        getline(input, plates[i].material);
        if (plates[i].material.empty()) {
            cerr << "Missing material for plate " << i << endl;
            delete[] plates;
            return 1;
        }
    }

    Rectangle* ptr = plates;
    for (int i = 0; i < num_plates; ++i, ++ptr) {
        double mass = ptr->width * ptr->height * ptr->thickness * ptr->density;
        print_plate(i, ptr->width, ptr->height, ptr->density, mass, ptr->material.c_str());
    }

    delete[] plates;
    return 0;
}
