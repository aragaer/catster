#include <functional>
#include <iostream>
#include <string>


template<class R>
class Reader {

public:
  template<class A>
  class Hom {
    std::function<A (R&)> _f;

  public:
    Hom(std::function<A (R&)> f): _f(f) {}

    A operator() (R &r) const {
      return _f(r);
    }
  };
};

template<template<class> class F, class A, class B>
F<B> fmap(std::function<B (A)>, F<A>);

template<class A, class B, class R>
typename Reader<R>::template Hom<B> fmap(std::function<B (A)> f,
                                         typename Reader<R>::template Hom<A> g) {
  std::function<B (R&)> fg = [f, g] (R &r) {
                              return f(g(r));
                            };
  return typename Reader<R>::template Hom<B>(fg);
}

template<class A>
void print(A a) {
  std::cout << a << std::endl;
}

int square(int x) {
  return x * x;
}

int parse(std::string s) {
  return std::stoi(s);
}

int main() {
  auto plain_parser = Reader<std::string>::Hom<int>(parse);
  auto square_parser = fmap<int, int, std::string>(square, plain_parser);

  auto print_plain = fmap<int, void, std::string>(print<int>, plain_parser);
  std::string s1("42");
  print_plain(s1);

  auto print_squared = fmap<int, void, std::string>(print<int>, square_parser);
  std::string s2("5");
  print_squared(s2);
}
