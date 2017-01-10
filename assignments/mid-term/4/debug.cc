#include <iostream>
#include <algorithm>
#include <numeric>
#include <list>

template <typename List, typename UnaryPred>
List & drop(List & l, UnaryPred condition) {
  for (auto i = l.begin(); i != l.end(); ++i) {
    if (condition(*i)) {
      l.erase((i++));
    }
  }
  return l;
}

int main() {

  std::list<int> l;

  std::generate_n(
    std::back_inserter(l), 10,
    []() { return std::rand() % 1024; });

  auto & ld = drop(l, [](int x) -> bool {
                        return x % 3 == 0;
                      });

  return EXIT_SUCCESS;
}
