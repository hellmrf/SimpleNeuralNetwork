#pragma once
#include <iostream>
#include <functional>
#include "Util.hpp"

typedef std::function<double(double)> ActFunction;

enum NeuronValueState
{
    Value,
    Activated,
    Derived
};
class Neuron
{
private:
    double value;
    double activatedValue;
    double derivedValue; // derivative of activatedValue

    // Fast Sigmoid Function
    // σ(x) = x / (1 + |x|)
    ActFunction activation_function = [](double val)
    { return val / (1 + abs(val)); };

    // Derivative of the activation function
    // σ'(x) = σ(x) * (1 - σ(x))
    ActFunction activation_function_derivative = [](double val)
    { return val * (1 - val); };

public:
    Neuron(double value);
    ~Neuron();

    void activate();
    void derive();

    // Getter
    double getValue() { return this->value; }
    double getActivatedValue() { return this->activatedValue; }
    double getDerivedValue() { return this->derivedValue; }

    void setValue(double val);
    void setActivationFunction(ActFunction function, ActFunction derivative);
};
