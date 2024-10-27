#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <cmath>

// #define PI 3.14159265

const std::vector<double> LILDAN_ANGLES = {135, 90, 45};
const std::vector<double> DHARMI_ANGLES = {120, 0, -120};
const double LILDAN_RADIUS = 0.15;
const double DHARMI_RADIUS = 0.15;
const double LILDAN_WHEEL_DIAMETER = 0.127;
const double DHARMI_WHEEL_DIAMETER = 0.048;

std::vector<double> calculateWheelSpeeds(const std::string &name, double Vx, double Vy, double omega) {
    std::vector<double> speeds;
    const std::vector<double>* angles = nullptr;
    double radius, wheelRadius;

    if (name == "LILDAN") {
        angles = &LILDAN_ANGLES;
        radius = LILDAN_RADIUS;
        wheelRadius = LILDAN_WHEEL_DIAMETER / 2.0;
    } else if (name == "DHARMI") {
        angles = &DHARMI_ANGLES;
        radius = DHARMI_RADIUS;
        wheelRadius = DHARMI_WHEEL_DIAMETER / 2.0;
    } else {
        std::cerr << "Invalid robot name!" << std::endl;
        return speeds;
    }

    for (double angle : *angles) {
        double angleRad = angle * M_PI / 180.0;
        double wheelSpeed = (std::sin(angleRad) * Vy + std::cos(angleRad) * Vx + omega * radius) / wheelRadius;
        speeds.push_back(wheelSpeed);
    }

    return speeds;
}

int main() {
    std::string name, command;
    double Vx, Vy, omega;

    std::cin >> name;

    if (name == "LILDAN") {
        std::cout << "∇" << std::endl;
    } else if (name == "DHARMI") {
        std::cout << "Δ" << std::endl;
    }

    while (true) {
        std::cin >> command;
        if (command == "GAS") break;

        Vy = std::stod(command);
        std::cin >> Vx >> omega;

        std::vector<double> wheelSpeeds = calculateWheelSpeeds(name, Vx, Vy, omega);

        for (double speed : wheelSpeeds) {
            std::cout << std::fixed << std::setprecision(2) << speed << std::endl;
        }
    }

    return 0;
}