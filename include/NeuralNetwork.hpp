#pragma once
#include <iostream>
#include <vector>
#include <Eigen/Dense>
#include "Layer.hpp"

class NeuralNetwork
{
private:
    std::vector<int> topology;
    std::vector<Layer> layers;
    std::vector<Eigen::MatrixXd> weights;
    std::vector<double> inputLayer;

public:
    NeuralNetwork(std::vector<int> topology);
    ~NeuralNetwork();
    void setInputLayer(Layer input);
    Layer getLayer(uint index) const;
    std::vector<double> getOutputLayer();
    friend std::ostream &operator<<(std::ostream &os, const NeuralNetwork &ann);
};
