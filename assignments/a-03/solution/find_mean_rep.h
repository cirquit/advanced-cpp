#ifndef CPPPC__S03__FIND_MEAN_REP_H__INCLUDED
#define CPPPC__S03__FIND_MEAN_REP_H__INCLUDED

// Some headers you might find useful:
#include <algorithm>
#include <numeric>
#include <vector>
#include <cmath>

namespace cpppc {

template <class Iter>
Iter find_mean_rep(Iter first, Iter last) {
  typedef typename std::iterator_traits<Iter>::value_type value_t;

  if (first == last) return last;

  int n = 0;

  value_t sum = std::accumulate(first
                              , last
                              , static_cast<value_t>(0)
                              , [&](value_t & xs,  value_t & x) {
                                   n += 1;
                                   return xs + x;
                                });

  double mean = sum / n;

  auto result = std::min_element(first
                               , last
                               , [&](value_t & a, value_t & b) {
                                    return std::abs(mean - a) < std::abs(mean - b);
                                 });
  return result;
}

} // namespace cpppc

#endif // CPPPC__S03__FIND_MEAN_REP_H__INCLUDED
