#ifndef BUTTON_CLASS_HPP
#define BUTTON_CLASS_HPP

class Button {
public:
  Button();
  void set();
  void unset();
  bool isTriggered();
private:
  bool isSet = false;
};


#endif