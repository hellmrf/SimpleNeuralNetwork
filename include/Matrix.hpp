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

    const int *size() const
    {
        int *p = new int[2];
        p[0] = this->m;
        p[1] = this->n;
        return p;
    }

private:
    int m;
    int n;

    std::vector<std::vector<double>> values;
};