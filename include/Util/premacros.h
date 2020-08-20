#pragma once

#include <iostream>

template <class T>
void LOG(T x)
{
    std::cout << x << std::endl;
}

template <class T, class U>
void LOG(T x, U y)
{
    std::cout << x << " " << y << std::endl;
}

template <class T, class U, class V>
void LOG(T x, U y, V z)
{
    std::cout << x << " " << y << " " << z << std::endl;
}

template <class T, class U, class V, class W>
void LOG(T x, U y, V z, W a)
{
    std::cout << x << " " << y << " " << z << " " << a << std::endl;
}

template <class T, class U, class V, class W, class X>
void LOG(T x, U y, V z, W a, X b)
{
    std::cout << x << " " << y << " " << z << " " << a << " " << b << std::endl;
}

template <class T>
T bruh() {
  int hi =1;
  return hi;
}