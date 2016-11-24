#ifndef CPPPC__S03__FIND_MEAN_REP_H__INCLUDED
#define CPPPC__S03__FIND_MEAN_REP_H__INCLUDED

// Some headers you might find useful:
#include <algorithm>
#include <numeric>
#include <vector>
#include <cmath>

namespace cpppc {

// naive implementation O(2n)
template <class Iter>
Iter find_mean_rep(Iter first, Iter last) {
  typedef typename std::iterator_traits<Iter>::value_type value_t;

  if (first == last) return last;

  double  mean = 0;
  int        n = 0;
  value_t  sum = 0;

  std::for_each(first, last,
      [&](value_t & x) {
        sum += x;
        n   += 1;
      });

  mean              = sum / n;
  n                 = 0;
  int result_offset = 0;
  value_t diff  = std::abs(mean - *first);

  std::for_each(first, last,
      [&](value_t & x) {
        double cur_diff = std::abs(mean - x);
        if (cur_diff < diff){
          diff   = cur_diff;
          result_offset = n;
        }
        n++;
      });


  std::advance(first,result_offset);
  return first;
}

} // namespace cpppc

#endif // CPPPC__S03__FIND_MEAN_REP_H__INCLUDED
