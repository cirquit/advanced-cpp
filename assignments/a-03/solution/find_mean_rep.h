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

  for(auto iter = first; iter != last; iter++){
    sum += &iter;
    n   += 1;
  }

  mean = sum / n;
  value_t diff = abs(mean - &first);
  Iter cur = first;

  for(auto iter = (first+1); iter != last; iter++){
    if (abs((mean - &iter)) < diff){
      diff = abs(mean - &iter);
      cur  = iter;
    }
  }

  return cur;
}

} // namespace cpppc




#endif // CPPPC__S03__FIND_MEAN_REP_H__INCLUDED
