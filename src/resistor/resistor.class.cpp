#include "resistor.class.hpp"

Resistor::Resistor(float value) : value(value) {
}

float Resistor::getValue() const {
    return value;
}

void Resistor::setValue(float value) {
    this->value = value;
}