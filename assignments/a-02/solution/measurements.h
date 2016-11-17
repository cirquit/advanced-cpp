#ifndef CPPPC__A02__MEASUREMENTS_H__INCLUDED
#define CPPPC__A02__MEASUREMENTS_H__INCLUDED

#include <vector>
#include <cmath>

namespace cpppc {

template <typename T>
class Measurements
{

  typedef Measurements<T>                                   self_t;
  typedef T                                                value_t;

  typedef       T &                                      reference;
  typedef const T &                                const_reference;
  typedef typename std::vector<T>::iterator               iterator;
  typedef typename std::vector<T>::const_iterator   const_iterator;

public:

  Measurements() noexcept {}

  Measurements(const self_t & other);

  ~Measurements(){
    _values.clear();
  }

  value_t & operator[](int i){
    return _values[i];
  }

  self_t &  operator=(const self_t & rhs);

  bool      operator==(const_reference rhs);

  value_t front(){
    return _values.front();
  }

  value_t back(){
    return _values.back();
  }

  bool empty(){
    return _values.empty();
  }

  int size(){
    return _values.size();
  }

  void clear(){
    _values.clear();
  }

  void insert(T item){
    _values.push_back(item);
  }

  const_iterator begin(){
    return _values.begin();
  }

  const_iterator end(){
    return _values.end();
  }

  // O(1)
  double mean() const{
     return _mean;
  }

  // O(1), unbiased
  double variance() const{
     return _s / (_n - 1);
  }

  // O(1)
  double sigma() const{
     return sqrt(variance());
  }

  // O(n)
  value_t median() const;

  void insert(iterator begin_it, iterator end_it);


private:

  std::vector<T> _values;

  double _s     = 0.0;
  double _mean  = 0.0;
  double _n     = 0.0;

  // NOT numerically stable (Knuth's algorithm for single pass variance + mean)
  // if the sample data is close to the mean, catastrophic cancellation takes place
  void update_stats(T val);
};

} // namespace cpppc

#include "measurements.impl.h"

#endif // CPPPC__A02__MEASUREMENTS_H__INCLUDED
