#ifndef CPPPC__A02__MEASUREMENTS_IMPL_H__INCLUDED
#define CPPPC__A02__MEASUREMENTS_IMPL_H__INCLUDED

namespace cpppc {

// self_t is not visible? - why
template <typename T>
Measurements<T>(const Measurements<T> & other){
  _values = other._values;
  _n      = other._n;
  _s      = other._s;
  _mean   = other._mean;
}

template <typename T>
self_t & operator=(const Measurements<T> & other){
  _values = other._values;
  _n      = other._n;
  _s      = other._s;
  _mean   = other._mean;
  return *this;
}

// TODO
bool operator==(const_reference rhs) const {
  if (*this == rhs) return true;
  if (_values == rhs._values) return true;
  return false;
}

void insert(iterator begin_it, iterator end_it){
  _values.clear()
  for(auto iter = begin(); iter != end(); ++iter){
    _values.push_back(&iter);
    update_stats(&iter);
  }
}

value_t median() const{

  value_t value;
  double diff = *begin() - mean();
  double cur_diff;

  for(auto iter = begin(); iter != end(); ++iter){
     cur_diff = *iter - mean();
     if(cur_diff < diff) {
       value = *iter;
       diff  = cur_diff;
     }
  }

  return value;
}

void update_stats(T val){
  double delta = val - _mean;
  _n    += 1;
  _mean += delta / _n;
  _s    += delta * (val - _mean);
}

} // namespace cpppc

#endif // CPPPC__A02__MEASUREMENTS_IMPL_H__INCLUDED
