#pragma once

template<typename F>
struct argument_of;

template<typename A,
         typename B>
struct argument_of<B (*)(A)> {
  typedef A type;
};
