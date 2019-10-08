#include <iostream>
#include <math.h>


class Shape {
public:
  virtual float area() = 0;
  virtual float circ() = 0;
};

class Circle: public Shape {
  float _r;

public:
  Circle(float r): _r(r) {}

  virtual float area() {
    return M_PI * _r * _r / 2;
  }

  virtual float circ() {
    return M_PI * 2 * _r;
  }
};

class Rect: public Shape {
  float _w, _h;

public:
  Rect(float w, float h): _w(w), _h(h) {}

  virtual float area() {
    return _w * _h;
  }

  virtual float circ() {
    return _w + _h + _w + _h;
  }
};

class Square: public Shape {
  float _s;

public:
  Square(float s): _s(s) {}

  virtual float area() {
    return _s * _s;
  }

  virtual float circ() {
    return _s * 4;
  }
};

int main() {
  Shape *s1 = new Circle(2);
  Shape *s2 = new Rect(3, 4);
  Shape *s3 = new Square(2);

  std::cout << s1->area() << " " << s1->circ() << std::endl;
  std::cout << s2->area() << " " << s2->circ() << std::endl;
  std::cout << s3->area() << " " << s3->circ() << std::endl;
}
