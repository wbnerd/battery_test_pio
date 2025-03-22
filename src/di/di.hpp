#ifndef DI_HPP
#define DI_HPP
#include <Arduino.h>

template <typename T>
class Container {
private:
  static T* instance;
public:
  static void set(T* obj) {
    if (instance != nullptr)
    {
      Serial.println("Dep is already set");
    }

    instance = obj;
  }

  static T* get() {
    if (instance == nullptr)
    {
      Serial.println("Dep is not ready");
    }

    return instance;
  }
};

#endif