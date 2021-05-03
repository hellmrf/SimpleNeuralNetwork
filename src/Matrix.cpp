#include "../include/Matrix.hpp"

Matrix::Matrix(int m, int n, bool isRandom)
{
    this->m = m;
    this->n = n;
    for (uint i = 0; i < m; ++i)
    {
        std::vector<double> tmp;
        for (uint j = 0; j < n; ++j)
        {
            double val = isRandom ? Util::randd() : 0.0;
            tmp.push_back(val);
        }
        this->values.push_back(tmp);
    }
}

Matrix::~Matrix()
{
}

Matrix Matrix::transposed()
{
    Matrix tranposed = Matrix(this->n, this->m, false);

    for (uint i = 0; i < this->m; ++i)
        for (uint j = 0; j < this->n; ++j)
            tranposed.setValue(j, i, this->getValue(i, j));

    return tranposed;
}
void Matrix::setValue(int i, int j, double value)
{
    this->values[i][j] = value;
}

const double Matrix::getValue(int i, int j) const
{
    return this->values[i][j];
}

std::ostream &operator<<(std::ostream &os, const Matrix &mat)
{
    for (uint i = 0; i < mat.m; ++i)
    {
        for (uint j = 0; j < mat.n; ++j)
        {
            os << std::setw(7) << std::setprecision(6) << std::fixed << std::showpoint;
            os << mat.getValue(i, j) << "  ";
        }
        os << std::endl;
    }
    return os;
}