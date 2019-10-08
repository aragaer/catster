#include <chrono>
#include <functional>
#include <iostream>
#include <map>
#include <stdlib.h>
#include <time.h>
#include <type_traits>

#include "common.h"

extern std::function<unsigned long (unsigned long)> fibonacci;

unsigned long fibonacci_orig(unsigned long n) {
  if (n <= 1)
    return 1UL;
  return fibonacci(n-1) + fibonacci(n-2);
}

std::function<unsigned long (unsigned long)> fibonacci = fibonacci_orig;

#define ITER 1
#define DEPTH 30

int nrandom(unsigned int seed) {
  srand(seed);
  return rand();
}

const auto memoize(auto f) {
  return [f] (auto... a) {
           auto t = std::make_tuple(a...);
           static std::map<decltype(t), decltype(f(a...))> memo;

           if (memo.find(t) == memo.end())
             memo[t] = f(a...);

           return memo[t];
         };
}

int mul(int a, int b) {
  return a * b;
}

auto f = memoize(mul);

int main() {
  long o = 0;
  auto start = std::chrono::system_clock::now();
  for (int i = 0; i < ITER; i++)
    o += fibonacci(DEPTH);
  auto end = std::chrono::system_clock::now();
  std::chrono::duration<double> elapsed_seconds = end - start;
  std::cout << "non-memoized took " << elapsed_seconds.count() << " seconds" << std::endl;

  o = 0;
  start = std::chrono::system_clock::now();
  for (int i = 0; i < ITER; i++)
    o += fibonacci(DEPTH);
  end = std::chrono::system_clock::now();
  elapsed_seconds = end - start;
  std::cout << "non-memoized again took " << elapsed_seconds.count() << " seconds" << std::endl;

  fibonacci = memoize(fibonacci);

  o = 0;
  start = std::chrono::system_clock::now();
  for (int i = 0; i < ITER; i++)
    o += fibonacci(DEPTH);
  end = std::chrono::system_clock::now();
  elapsed_seconds = end - start;
  std::cout << "memoized took " << elapsed_seconds.count() << " seconds" << std::endl;

  o = 0;
  start = std::chrono::system_clock::now();
  for (int i = 0; i < ITER; i++)
    o += fibonacci(DEPTH);
  end = std::chrono::system_clock::now();
  elapsed_seconds = end - start;
  std::cout << "memoized again took " << elapsed_seconds.count() << " seconds" << std::endl;

  srand(time(NULL));

  std::cout << "non-memoized random:" << std::endl;
  for (int i = 0; i < 5; i++)
    std::cout << rand() << std::endl;

  auto prand = memoize(rand);

  std::cout << "memoized random:" << std::endl;
  for (int i = 0; i < 5; i++)
    std::cout << prand() << std::endl;

  std::cout << "non-memoized nrandom:" << std::endl;
  for (int i = 0; i < 5; i++)
    std::cout << nrandom(i+1) << " " << nrandom(i+1) << std::endl;

  auto pnrandom = memoize(nrandom);

  std::cout << "memoized nrandom:" << std::endl;
  for (int i = 0; i < 5; i++)
    std::cout << pnrandom(i+1) << " " << pnrandom(i+1) << std::endl;

  std::cout << f(2,2) << std::endl;
}
