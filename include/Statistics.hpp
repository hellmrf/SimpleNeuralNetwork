#pragma once
#include <vector>
#include <stdexcept>
#include <math.h>

namespace Statistics
{
    double MSE(std::vector<double> target, std::vector<double> pred)
    {
        if (target.size() != pred.size())
            throw(std::domain_error("Target and predicted vectors has to be of the same size."));
        auto N = target.size();
        double result = 0.0;
        for (uint i = 0; i < N; ++i)
            result += pow((target[i] - pred[i]), 2);
        return result / N;
    }
    double RMSE(std::vector<double> target, std::vector<double> pred)
    {
        return sqrt(MSE(target, pred));
    }
}