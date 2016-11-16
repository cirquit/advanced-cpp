#ifndef CPPPC__A02__MEASUREMENTS_IMPL_H__INCLUDED
#define CPPPC__A02__MEASUREMENTS_IMPL_H__INCLUDED

namespace cpppc {

Measurements(const Measurements& other){
  _values = other._values;
  _n      = other._n;
  _s      = other._s;
  _mean   = other._mean;
}

self_t & operator=(const self_t& other){
  _values = other._values;
  _n      = other._n;
  _s      = other._s;
  _mean   = other._mean;
  return *this;
}

// TODO
bool operator==(const_reference rhs) const {
  return false;
}


void insert(iterator begin_it, iterator end_it){
  _values.clear()
  for(auto iter = begin(); iter != end(); ++iter){
    _values.push_back(&iter);
    update_stats(&iter);
  }
}

// O(n)
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

// NOT numerically stable (Knuth's algorithm for single pass variance + mean)
// if the sample data is close to the mean, catastrophic cancellation takes place
void update_stats(T val){
  double delta = val - _mean;
  _n    += 1;
  _mean += delta / _n;
  _s    += delta * (val - _mean);
}

} // namespace cpppc

#endif // CPPPC__A02__MEASUREMENTS_IMPL_H__INCLUDED
