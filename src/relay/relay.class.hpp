#ifndef RELAY_HPP
#define RELAY_HPP

#include <constants.hpp>

class Relay {
public:
    Relay(uint8_t pin);
    void on();
    void off();
    bool isOn() const;

private:
    uint8_t pin;
    bool state;
};

#endif // RELAY_HPP