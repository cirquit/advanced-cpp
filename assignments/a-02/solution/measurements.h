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

  // default constructor
  Measurements(){}

  // copy constructor
  Measurements(const Measurements& rhs){
    _values = rhs.get_values();
  }
/*    for(auto begin = rhs.begin(); begin != rhs.end(); ++begin){

    } */

  // delete
  ~Measurements(){}

  value_t &operator[](int i){
    return _values[i];
  }

  self_t& operator=(const self_t& rhs){
//    _values = rhs.get_values();
  }

  bool operator==(const_reference rhs) const {
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

  void insert(iterator begin_it, iterator end_it){
    _values.clear()
    for(auto iter = begin(); iter != end(); ++iter){
      _values.push_back(&iter);
      update_stats(&iter);
    }
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

  value_t median() const{
    return 0;
  }

  double mean() const{
     return _mean;
  }

  // unbiased
  double variance() const{
     return _s / (_n - 1);
  }

  double sigma() const{
     return sqrt(variance());
  }

private:

  std::vector<T> _values;

  T      _median; // would love to use optional...

  double _s     = 0.0;
  double _mean  = 0.0;
  double _n     = 0.0;

  // NOT numerically stable (Knuth's algorithm for single pass variance + mean)
  // if the sample data is close to the mean, catastrophic cancellation takes place
  void update_stats(T val){
    double delta = val - _mean;
    _n    += 1;
    _mean += delta / _n;
    _s    += delta * (val - _mean);
  }
};

} // namespace cpppc

#endif // CPPPC__A02__MEASUREMENTS_H__INCLUDED
