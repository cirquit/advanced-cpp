#include <iostream>
#include <algorithm>

template<typename X>
void log10(X x)
{   
    if (std::is_integral<X>::value)
    {
      std::cout << std::log10(x) << '\n';
    } else
    {
      std::cout << std::log10(std::sqrt(x)) << '\n';
    }
}

int main(int argc, char const *argv[])
{
  int   i = 10;
  float f = 10.0;
  std::cout << "int: ";
  log10(i);
  std::cout << "double: ";
  log10(f);
  return 0;
}