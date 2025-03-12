#ifndef DI_HPP
#define DI_HPP

template <typename T>
class Container {
private:
  static T* instance = nullptr;
public:
  static void set(T* obj) {
    if (instance != nullptr)
    {
      char buffer[32];
      std::snprintf(buffer, sizeof(buffer), "Dep is not ready %s ", typeid(T).name());
      throw std::runtime_error(buffer);
    }

    instance = obj;
  }

  static T* get() {
    if (instance == nullptr)
    {
      char buffer[32];
      std::snprintf(buffer, sizeof(buffer), "Dep is not ready %s ", typeid(T).name());
      throw std::runtime_error(buffer);
    }

    return instance;
  }
};

#endif