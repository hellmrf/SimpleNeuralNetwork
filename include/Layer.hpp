#pragma once

#include <iostream>
#include <vector>
#include <Eigen/Dense>
#include "Neuron.hpp"
class Layer
{
private:
    int size;

    std::vector<Neuron> neurons;

public:
    Layer(std::vector<double> topology);
    Layer(int size);
    ~Layer();
    void setValue(uint index, double value);
    void setValues(Eigen::RowVectorXd values);

    Eigen::MatrixXd as_matrix(NeuronValueState state = Value, bool column_matrix = false);
};
