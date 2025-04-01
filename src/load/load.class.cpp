#include "load.class.hpp"

Load::Load(float value) : value(value) {
}

float Load::getValue() const {
    return value;
}

void Load::setValue(float value) {
    this->value = value;
}