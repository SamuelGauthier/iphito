/**
 * @file Utils.h
 * @brief Utils class for iphito
 * @author Samuel Gauthier
 * @version 0.1.0
 * @date 2018-10-16
 */
#ifndef UTILS_H
#define UTILS_H
#include <stdexcept>
#include <string>

#include <vector>

class Utils {

public:
    Utils() = delete;
    ~Utils() = delete;

    static const unsigned long long factorial(int n);
    static const bool isGlfwInitialized();
    static const bool isGlewInitialized();
    static void setGlfwInitialized();
    static void setGlewInitialized();
    static const std::string readFile(std::string filePath);

private:
    static const std::vector<unsigned long long> factorials;
    static bool glfwInitialized;
    static bool glewInitialized;
};

#endif /* ifndef UTILS_H */
