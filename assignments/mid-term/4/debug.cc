#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>


template <typename Vector, typename UnaryPred>
Vector & drop(Vector & v, UnaryPred condition) {
  for (auto i = v.begin(); i != v.end(); ++i) {
    if (condition(*i)) {
      v.erase(i);
    }
  }
}

int main() {

  std::vector<int> v;

  std::generate_n(
    std::back_inserter(v), 100,
    []() { return std::rand() % 1024; });

  auto & vd = drop(v, [](int x) -> bool {
                        return x % 3 == 0;
                      });

  return EXIT_SUCCESS;
}
