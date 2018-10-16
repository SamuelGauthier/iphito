/**
 * @file Utils.h
 * @brief Utils class for iphito
 * @author Samuel Gauthier
 * @version 1.0
 * @date 2018-10-16
 */
#ifndef UTILS_H
#define UTILS_H
#include <stdexcept>

#include <vector>

class Utils {

public:
    Utils() = delete;
    ~Utils() = delete;

    static const unsigned long long factorial(int n) {
        if(n < 0) {
            throw std::domain_error("Negative factorials do not exist.");
        }
        if(n > 19) {
            throw std::domain_error("Unable to compute factorials greater"
                                    "than 19!");
        }
        
        return Utils::factorials[n];
    }

private:
    static const std::vector<unsigned long long> factorials;

};

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
#endif /* ifndef UTILS_H */
