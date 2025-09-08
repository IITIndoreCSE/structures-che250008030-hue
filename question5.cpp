#include <iostream>
#include <fstream>
#include <cstring>

using namespace std;

// Define Sensor struct
struct Sensor {
    int id;
    double temperature;
    double voltage;
    char status[20];  // fixed size char array for status
};

void print_sensor(int index, int id, double temperature, double voltage, const char* status) {
    cout << "Sensor[" << index << "]: "
         << "id=" << id << ", "
         << "temperature=" << temperature << ", "
         << "voltage=" << voltage << ", "
         << "status=" << status << "\n";
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

    int num_sensors;
    input >> num_sensors;
    input.ignore(); // skip newline after number

    const int MAX_SENSORS = 10;
    if (num_sensors > MAX_SENSORS) {
        cerr << "Too many sensors, max allowed is " << MAX_SENSORS << endl;
        return 1;
    }

    // Create array of Sensor
    Sensor sensors[MAX_SENSORS];

    // Read sensor data from input
    for (int i = 0; i < num_sensors; i++) {
        input >> sensors[i].id;
        input >> sensors[i].temperature;
        input >> sensors[i].voltage;
        input.ignore(); // skip newline before status line
        input.getline(sensors[i].status, 20);
    }

    // Iterate using a pointer and print sensor data
    Sensor* ptr = sensors;
    for (int i = 0; i < num_sensors; i++) {
        print_sensor(i, ptr->id, ptr->temperature, ptr->voltage, ptr->status);
        ++ptr;
    }

    return 0;
}
