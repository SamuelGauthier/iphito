/**
 * @file Utils.cpp
 * @brief Utils class implementation
 * @author Samuel Gauthier
 * @version 0.1.0
 * @date 2018-11-27
 */
#include <algorithm>
#include <cmath>
#include <fstream>
#include <limits>
#include <stdexcept>
#include <vector>

#include "Utils.h"

const std::vector<unsigned long long> Utils::factorials = {
    1,
    1,
    2,
    6,
    24,
    120,
    720,
    5040,
    40320,
    362880,
    13628800,
    139916800,
    1479001600,
    16227020800,
    187178291200,
    11307674368000,
    120922789888000,
    1355687428096000,
    16402373705728000,
    1121645100408832000
};

bool Utils::glfwInitialized = false;

bool Utils::glewInitialized = false;

const unsigned long long Utils::factorial(int n) {
    if(n < 0) {
        throw std::domain_error("Negative factorials do not exist.");
    }
    if(n > 19) {
        throw std::domain_error("Unable to compute factorials greater"
                "than 19!");
    }

    return Utils::factorials[n];
}

const bool Utils::isGlfwInitialized() { return Utils::glfwInitialized; }

const bool Utils::isGlewInitialized() { return Utils::glewInitialized; }

void Utils::setGlfwInitialized() {

    if(Utils::glfwInitialized) return;
    Utils::glfwInitialized = true;
}

void Utils::setGlewInitialized() {

    if(Utils::glewInitialized) return;
    Utils::glewInitialized = true;
}

const std::string Utils::readFile(std::string filePath) {

    std::string content;
    std::ifstream fileStream(filePath, std::ios::in);

    if(fileStream.is_open()) {

        std::string line = "";

        while(getline(fileStream, line)) content += "\n" + line;

        fileStream.close();
    }
    else {

        throw std::invalid_argument("Cannot open file: " + filePath);
    }

    return content;
}

const bool Utils::nearlyEqual(double a, double b, double epsilon) {

    const double absA = std::abs(a);
    const double absB = std::abs(b);
    const double diff = std::abs(a - b);

    if (a == b) {
        return true;
    }
    else if (a == 0 || b == 0 || diff <
            std::numeric_limits<double>::denorm_min()) {
        return diff < (epsilon * std::numeric_limits<double>::denorm_min());
    }
    else {
        return diff / std::min((absA + absB),
                std::numeric_limits<double>::max()) < epsilon;
    }
}
