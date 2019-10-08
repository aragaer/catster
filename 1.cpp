#include <functional>
#include <iostream>
#include <type_traits>

#include "common.h"

auto identity(auto x) {
  return x;
}

int plus1(int x) {
  return x+1;
}

int times2(int x) {
  return x*2;
}

const auto compose(auto g, auto f) {
  return [f, g] (auto x) {
           return g(f(x));
         };
}

int main() {
  std::cout << identity(10) << std::endl;
  std::cout << identity("hello, world") << std::endl;
  std::cout << compose(times2, plus1)(3) << std::endl;
  std::cout << times2(3) << " == " << compose(times2, identity<int>)(3) << std::endl;
  std::cout << plus1(3) << " == " << compose(identity<int>, plus1)(3) << std::endl;
}
