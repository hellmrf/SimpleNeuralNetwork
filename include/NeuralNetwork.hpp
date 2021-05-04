#pragma once
#include <iostream>
#include <vector>
#include <Eigen/Dense>
#include "Layer.hpp"
#include "Util.hpp"

class NeuralNetwork
{
private:
    std::vector<int> topology;
    std::vector<Layer> layers;
    std::vector<Eigen::MatrixXd> weights;
    std::vector<double> inputLayer;
    std::vector<double> target;

public:
    NeuralNetwork(std::vector<int> topology);
    ~NeuralNetwork();

    void setInputLayer(Layer input);
    void setTarget(std::vector<double> target);
    Layer getLayer(uint index) const;
    std::vector<double> getOutputLayer();

    std::vector<Eigen::MatrixXd> DEBUG_get_raw_weights()
    {
        return this->weights;
    }
    void feedForward();

    friend std::ostream &operator<<(std::ostream &os, const NeuralNetwork &ann);
};
