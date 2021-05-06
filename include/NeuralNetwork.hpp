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
    std::vector<Eigen::MatrixXd> gradientMatrices;
    std::vector<double> target;

public: // TODO: REMOVE THIS
    // Raw errors of each output neuron.
    Eigen::RowVectorXd outputErrors;
    // Squared errors of each output neuron.
    Eigen::RowVectorXd outputMSE;

    // Mean_error in this iteration
    double mean_error;
    // Error throughout net training
    std::vector<double> historicalErrors;

    double learning_rate = 0.5;
    double momentum = 1;
    double bias = 1;

public:
    NeuralNetwork(std::vector<uint> topology);
    ~NeuralNetwork();

    void setInputLayer(Layer input);
    void setTarget(std::vector<double> target);
    Layer getLayer(uint index) const;
    uint numLayers() { return this->layers.size(); };
    Eigen::RowVectorXd getOutputLayer(NeuronValueState state = Value);

    Eigen::MatrixXd getWeights(uint layer_index)
    {
        return this->weights.at(layer_index);
    }
    void feedForward();
    void computeErrors();
    void backPropagation();

    friend std::ostream &operator<<(std::ostream &os, const NeuralNetwork &ann);
};
