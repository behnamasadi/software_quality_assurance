#include <random>
#include "random_number_generator.hpp"

#ifndef UNIFORM_RANDOMNUMBERGENERATOT_H
#define UNIFORM_RANDOMNUMBERGENERATOT_H

class UniFormRandomNumberGenerator : public  IRandomNumberGenerator
{
    public:

    double  generate(double min,double  max) override
    {
        std::random_device rand_dev;
        std::mt19937 generator(rand_dev());
        std::uniform_real_distribution<double> distr(min, max);
        return distr(generator);
    }
};

#endif
