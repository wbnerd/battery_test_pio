#ifndef RESISTOR_CLASS_HPP
#define RESISTOR_CLASS_HPP

class Resistor {
public:
    Resistor(float value);
    float getValue() const;
    void setValue(float value);

private:
    float value;
};

#endif