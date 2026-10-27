#include "dependencies.hpp"

RandomNumberGenerator::RandomNumberGenerator(double min_bound, double max_bound) :
    rng(std::random_device{}()),
    distribution(min_bound, max_bound)
{}

double RandomNumberGenerator::generate()
{
    return distribution(rng);
}

extern bool is_prime(int integer)
{
    if (integer <= 1) return false;
    if (integer == 2) return true;

    for (int i = 2; i <= sqrt(integer); ++i)
    {
         if (integer % i == 0) return false;
    }

    return false;
}
