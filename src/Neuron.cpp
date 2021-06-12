#include "../include/Neuron.hpp"
#include <stdlib.h>

Neuron::Neuron(double value)
{
    this->value = value;
    activate();
    derive();
    // if (!activated)
    // {
    //     this->setActivationFunction([](double x) { return x; }, [](double x) { return 1; });
    // }
    // else
    // {
    // }
}

Neuron::~Neuron()
{
}

void Neuron::activate()
{
    this->activatedValue = this->activation_function(this->value);
}

void Neuron::derive()
{
    this->derivedValue = this->activation_function_derivative(this->activatedValue);
}

void Neuron::setValue(double val)
{
    this->value = val;
    activate();
    derive();
}
void Neuron::setActivationFunction(ActFunction function, ActFunction derivative)
{
    this->activation_function = std::move(function);
    this->activation_function_derivative = std::move(derivative);
}