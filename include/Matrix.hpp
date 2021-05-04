#pragma once

#include <iostream>
#include <iomanip>
#include <vector>
#include "Util.hpp"

class Matrix
{
public:
    Matrix(int m, int n, bool isRandom = false);
    ~Matrix();

    Matrix transposed();

    void setValue(int i, int j, double value);
    const double getValue(int i, int j) const;

    friend std::ostream &operator<<(std::ostream &os, const Matrix &mat);

    std::array<int, 2> size() const
    {
        std::array<int, 2> sz{this->m, this->n};
        return sz;
    }

private:
    int m;
    int n;

    std::vector<std::vector<double>> values;
};