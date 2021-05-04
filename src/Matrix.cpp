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
Matrix operator*(Matrix &A, const Matrix &B)
{
    auto [m1, n1] = A.size();
    auto [m2, n2] = B.size();
    if (n1 != m2)
    {
        std::stringstream ss;
        ss << "Dimensions not compatible. A(";
        ss << m1 << ", " << n1 << ") * B(" << m2 << ", " << n2 << ").";
        throw(DimensionMismatchException(ss.str()));
    }
    auto C = Matrix(m1, n2);
    for (uint i = 0; i < m1; ++i)
        for (uint j = 0; j < n2; ++j)
            for (uint k = 0; k < n1; ++k)
            {
                double val = A.getValue(i, k) * B.getValue(k, j);
                C.setValue(i, j, val);
            }

    return C;
}
