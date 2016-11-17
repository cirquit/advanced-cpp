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

  Measurements(const self_t & other){
    _values = other._values;
    _n      = other._n;
    _s      = other._s;
    _mean   = other._mean;
  }

  ~Measurements(){
    _values.clear();
  }

  const value_t & operator[](int i) const{
    return _values[i];
  }

  // TODO find a solution to reduce complexity
  //
  // if this references will be changed, every calculation 
  // will be in O(n)
  value_t & operator[](int i){
    return _values[i];
  }

  self_t &  operator=(const self_t & other){
    _values = other._values;
    _n      = other._n;
    _s      = other._s;
    _mean   = other._mean;
    return *this;
  }

  bool operator==(const self_t & other) const{
    if (this == &other) return true;
    if (_values == other._values) return true;
    return false;
  }

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

  void insert(T & item){
    _values.push_back(item);
  }

  void insert(T item){
    T & ref = item;
    _values.push_back(ref);
  }


  void insert(iterator begin_it, iterator end_it){
    _values.clear();
    clear_stats();
    for(auto iter = begin_it; iter != end_it; ++iter){
      _values.push_back(*iter);
      update_stats(*iter);
    }
  }

  const_iterator begin() const{
    return _values.begin();
  }

  const_iterator end() const{
    return _values.end();
  }

  // O(1)
  double mean() const{
     return _mean;
  }

  // O(1), biased
  double variance() const{
     return _s / (_n);
  }

  // O(1)
  double sigma() const{
     return sqrt(variance());
  }

  //   O(n * logn) for ordered data
  // + O(n) for the vector copy
  value_t median() const{
    if (_values.size() == 0) return 0;
    std::vector<value_t> sorted(_values);
    std::sort(sorted.begin(), sorted.end());

    if (sorted.size() % 2 == 0){
      int i = sorted.size() / 2;
      return (sorted[i] + sorted[i-1]) / 2;
    } else {
      int i = std::ceil(sorted.size() / 2);
      return sorted[i];
    }
  }


private:

  std::vector<T> _values;

  double _s     = 0.0;
  double _mean  = 0.0;
  double _n     = 0.0;

  // NOT numerically stable (Knuth's algorithm for single pass variance + mean)
  // if the sample data is close to the mean, catastrophic cancellation
  // takes place
  void update_stats(T & val){
     double delta = val - _mean;
    _n    += 1;
    _mean += delta / _n;
    _s    += delta * (val - _mean);
  }

  void clear_stats(){
    _s    = 0.0;
    _mean = 0.0;
    _n    = 0.0;
  }

};

} // namespace cpppc


#endif // CPPPC__A02__MEASUREMENTS_H__INCLUDED
