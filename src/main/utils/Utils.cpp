/**
 * @file Utils.cpp
 * @brief Utils class implementation
 * @author Samuel Gauthier
 * @version 0.1.0
 * @date 2018-11-27
 */
#include <fstream>
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

bool Utils::glfwInitialized = false;

bool Utils::glewInitialized = false;

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
