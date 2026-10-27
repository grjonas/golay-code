#pragma once

#include <iostream>
#include <optional>
#include <bitset>
#include <random>
#include <cassert>
#include <algorithm>

#define UNREACHABLE assert(false && "This code should be unreachable")

class RandomNumberGenerator
{
    public:
        RandomNumberGenerator(double min_bound, double max_bound);
        double generate();

    private:
        std::mt19937 rng;
        std::uniform_real_distribution<double> distribution;
};

// https://uncodemy.com/blog/prime-number-program-in-c-check-print-primes-with-code-examples
extern bool is_prime(int integer);

