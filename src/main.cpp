#include <iostream>
#include <random>
#include <Eigen/Dense>
#include "../include/Neuron.hpp"
#include "../include/NeuralNetwork.hpp"
#include "Util.hpp"

int main(int, char **)
{
    srand((unsigned)time(0));
    Neuron n = Neuron(0.9);
    std::cout << "Val: " << n.getValue() << std::endl;
    std::cout << "Activated Val: " << n.getActivatedValue() << std::endl;
    std::cout << "Derived Val: " << n.getDerivedValue() << std::endl;

    std::vector<uint> topology{3, 2, 3};
    std::vector<double> input{1., 0., 1.};

    NeuralNetwork ann = NeuralNetwork(topology);
    ann.setInputLayer(Layer(input));

    std::cout << ann << std::endl;
    ann.feedForward();
    std::cout << ann << std::endl;

    return 0;
}
