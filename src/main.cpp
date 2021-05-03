#include <iostream>
#include "../include/Neuron.hpp"
#include "../include/Matrix.hpp"
#include <random>

int main(int, char **)
{
    srand((unsigned)time(NULL));
    Neuron *n = new Neuron(0.9);
    std::cout << "Val: " << n->getValue() << std::endl;
    std::cout << "Activated Val: " << n->getActivatedValue() << std::endl;
    std::cout << "Derived Val: " << n->getDerivedValue() << std::endl;

    Matrix mat = Matrix(3, 5, true);
    auto size = mat.size();
    auto lin = size[0];
    auto col = size[1];
    std::cout << "(" << lin << ", " << col << ")" << std::endl;

    std::cout << mat << std::endl;
    std::cout << "------------" << std::endl;
    std::cout << mat.transposed() << std::endl;

    // std::cout << mat.getValue(0, 0) << std::endl;

    delete n;
    return 0;
}
