#pragma once

#define DEBUG_SHOW_LINE_WORKING std::cout << "\u001b[02m" << __FILE__ << ":" << __LINE__ << " I'm here" \
                                          << "\u001b[0m" << std::endl;
#include <random>
#include <iostream>

namespace Util
{
    inline double randd()
    {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_real_distribution<> dis(0, 1);

        return dis(gen);
    }

    inline double randi(int lower, int upper)
    {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dis(lower, upper);

        return dis(gen);
    }
}