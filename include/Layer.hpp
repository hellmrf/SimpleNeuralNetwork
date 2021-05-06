#pragma once

#include <iostream>
#include <vector>
#include <Eigen/Dense>
#include "Neuron.hpp"
#include "Util.hpp"
class Layer
{
private:
    uint n_neurons;

    std::vector<Neuron> neurons;

public:
    Layer(std::vector<double> layer);
    Layer(int size);
    ~Layer();
    void setValue(uint index, double value);
    void setValues(Eigen::RowVectorXd values);
    uint size() { return this->n_neurons; };

    Eigen::MatrixXd as_matrix(NeuronValueState state = Value, bool column_matrix = false);
};
