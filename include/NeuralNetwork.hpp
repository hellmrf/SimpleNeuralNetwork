#pragma once
#include <iostream>
#include <vector>
#include <Eigen/Dense>
#include "Layer.hpp"
#include "Util.hpp"

class NeuralNetwork
{
private:
    std::vector<uint> topology;
    std::vector<Layer> layers;
    std::vector<Eigen::MatrixXd> weights;
    std::vector<double> target;

public: // TODO: REMOVE THIS
    // Squared errors of each output neuron.
    std::vector<double> outputErrors;
    // Mean_error in this iteration
    double mean_error;
    // Error throughout net training
    std::vector<double> historicalErrors;

public:
    NeuralNetwork(std::vector<uint> topology);
    ~NeuralNetwork();

    void setInputLayer(Layer input);
    void setTarget(std::vector<double> target);
    Layer getLayer(uint index) const;
    Eigen::RowVectorXd getOutputLayer(NeuronValueState state);

    std::vector<Eigen::MatrixXd> DEBUG_get_raw_weights()
    {
        return this->weights;
    }
    void feedForward();
    void computeErrors();

    friend std::ostream &operator<<(std::ostream &os, const NeuralNetwork &ann);
};
