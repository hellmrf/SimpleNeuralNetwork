#include <iostream>
#include "../include/Neuron.hpp"
#include "../include/Matrix.hpp"
#include "../include/NeuralNetwork.hpp"
#include <random>

int main(int, char **)
{
    srand((unsigned)time(NULL));
    Neuron n = Neuron(0.9);
    std::cout << "Val: " << n.getValue() << std::endl;
    std::cout << "Activated Val: " << n.getActivatedValue() << std::endl;
    std::cout << "Derived Val: " << n.getDerivedValue() << std::endl;

    Matrix mat = Matrix(3, 5, true);
    auto [lin, col] = mat.size();
    std::cout << "(" << lin << ", " << col << ")" << std::endl;

    std::cout << mat << std::endl;
    std::cout << "------------" << std::endl;
    std::cout << mat.transposed() << std::endl;

    std::vector<int> topology{3, 2, 3};
    std::vector<double> input{1., 0., 1.};

    NeuralNetwork ann = NeuralNetwork(topology);
    ann.setInputLayer(Layer(input));

    std::cout << ann << std::endl;
    // std::cout << mat.getValue(0, 0) << std::endl;

    return 0;
}
