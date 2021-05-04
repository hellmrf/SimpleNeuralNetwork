#pragma once

#include <iostream>
#include <iomanip>
#include <vector>
#include <sstream>
#include <string>
#include "Util.hpp"

class DimensionMismatchException : public std::exception
{
public:
    explicit DimensionMismatchException(const std::string what_arg)
    {
        throw(std::domain_error("Dimension Mismatch: " + what_arg));
    }
    explicit DimensionMismatchException(char const *what_arg)
    {
        throw(std::domain_error("Dimension Mismatch: " + std::string(what_arg)));
    }
};
class Matrix
{
public:
    Matrix(int m, int n, bool isRandom = false);
    ~Matrix();

    Matrix transposed();

    void setValue(int i, int j, double value);
    const double getValue(int i, int j) const;

    friend std::ostream &operator<<(std::ostream &os, const Matrix &mat);
    friend Matrix operator*(Matrix &A, const Matrix &B);

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