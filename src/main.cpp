#include <iostream>
#include "../include/Neuron.hpp"
#include "../include/NeuralNetwork.hpp"
#include <random>
#include <Eigen/Dense>

int main(int, char **)
{
    srand((unsigned)time(NULL));
    Neuron n = Neuron(0.9);
    std::cout << "Val: " << n.getValue() << std::endl;
    std::cout << "Activated Val: " << n.getActivatedValue() << std::endl;
    std::cout << "Derived Val: " << n.getDerivedValue() << std::endl;

    auto mat = Eigen::MatrixXd(3, 5);
    std::cout << "(" << mat.rows() << ", " << mat.cols() << ")" << std::endl;

    std::cout << mat << std::endl;
    std::cout << "------------" << std::endl;
    std::cout << mat.transpose() << std::endl;

    std::vector<int> topology{3, 2, 3};
    std::vector<double> input{1., 0., 1.};

    NeuralNetwork ann = NeuralNetwork(topology);
    ann.setInputLayer(Layer(input));

    std::cout << ann << std::endl;
    // std::cout << mat.getValue(0, 0) << std::endl;

    // auto mat1 = Matrix(1000, 1000, true);
    // auto mat2 = Matrix(1000, 1000, true);
    // auto result = mat1 * mat2;
    // std::cout << result.size()[0] << " x " << result.size()[1] << std::endl;
    // auto mat1 = Eigen::MatrixXd::Random(3, 5);
    // auto mat2 = Eigen::MatrixXd::Random(5, 3);
    // auto result = mat1 * mat2;
    // std::cout << result.rows() << " x " << result.cols() << std::endl;
    // std::cout << result << std::endl;

    return 0;
}
