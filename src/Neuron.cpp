#include "../include/Neuron.hpp"
#include <stdlib.h>

Neuron::Neuron(double value)
{
    this->value = value;
    activate();
    derive();
}

Neuron::~Neuron()
{
}

void Neuron::activate()
{
    this->activatedValue = this->value / (1 + abs(this->value));
}

void Neuron::derive()
{
    this->derivedValue = this->activatedValue * (1 - this->activatedValue);
}

void Neuron::setValue(double val)
{
    this->value = val;
    activate();
    derive();
}