#include <iostream>
#include <math.h>


template<class A>
class optional {
  bool _isValid;
  A    _value;
public:
  optional()    : _isValid(false) {}
  optional(A v) : _isValid(true), _value(v) {}
  bool isValid() const { return _isValid; }
  A value() const { return _value; }
};


template<class A>
std::ostream& operator<< (std::ostream& stream, const optional<A>& data) {
  if (data.isValid())
    return stream << data.value();
  else
    return stream << "invalid";
}

optional<double> safe_root(double x) {
  if (x >= 0)
    return optional<double>{sqrt(x)};
  else
    return optional<double>{};
}

optional<double> safe_reciprocal(double x) {
  if (x == 0)
    return optional<double>{};
  else
    return optional<double>{1/x};
}

auto const compose(auto m1, auto m2) {
    return [m1, m2](auto x) {
        auto p1 = m1(x);
        if (p1.isValid())
          return m2(p1.value());
        return p1;
    };
};

int main() {
  std::cout << "root" << std::endl;
  std::cout << 4 << " " <<  safe_root(4) << std::endl;
  std::cout << -4 << " " << safe_root(-4) << std::endl;
  std::cout << 0 << " " <<  safe_root(0) << std::endl;

  std::cout << "reciprocal" << std::endl;
  std::cout << 4 << " " <<  safe_reciprocal(4) << std::endl;
  std::cout << -4 << " " << safe_reciprocal(-4) << std::endl;
  std::cout << 0 << " " <<  safe_reciprocal(0) << std::endl;

  std::cout << "root reciprocal" << std::endl;
  auto safe_root_reciprocal = compose(safe_root, safe_reciprocal);
  std::cout << 4 << " " <<  safe_root_reciprocal(4) << std::endl;
  std::cout << -4 << " " << safe_root_reciprocal(-4) << std::endl;
  std::cout << 0 << " " <<  safe_root_reciprocal(0) << std::endl;
}
