#pragma once
#include <iostream>

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

public:
    Neuron(double value);
    ~Neuron();

    // Fast Sigmoid Function
    // f(x) = x / (1 + |x|)
    void activate();

    // Derivative of the activation function
    // f'(x) = f(x) * (1 - f(x))
    void derive();

    // Getter
    double getValue() { return this->value; }
    double getActivatedValue() { return this->activatedValue; }
    double getDerivedValue() { return this->derivedValue; }

    void setValue(double val);
};
