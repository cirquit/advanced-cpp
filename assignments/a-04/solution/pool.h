#ifndef POOL_H

#include <iostream>
#include <mutex>
#include <set>
#include <stdexcept>  // length_error, invalid_argument
#include <iterator>   // advance

namespace cpppc {

template<typename Element>
class Pool
{
  typedef       Pool<Element>          self_t;
  typedef       Pool<Element> &    self_ref_t;

  typedef       Element               value_t;
  typedef       Element &         value_ref_t;
  typedef const Element         const_value_t;

  public:

    Pool(size_t size)
      : _default_size(size)
    { }

    template<typename Iter>
    Pool(Iter first, Iter last)
      : _set(first, last)
    { }

  public:

    void release(value_t element)
    {
      auto melem = _set.find(element);
      if (melem != _set.end()){
        throw std::invalid_argument("cpppc::Pool::release - duplicate element insertion");
      }

      _set.insert(element);

      if (_set.size() > _default_size){
        throw std::length_error("cpppc::Pool::release - pool length is exhausted");
      }
    }

    value_t acquire()
    {
      std::srand(std::time(0));
      int random_index = std::rand() % _default_size;
      auto melement    = _set.begin();
      std::advance(melement, random_index);

      if (melement != _set.end()){
        value_t element = *melement;
        _set.erase(melement);
        return element;
      } else if (_default_size > 0){
        return _default_value;
      } else {
        throw std::length_error("cpppc:Pool::acquire - pool is empty");
      }
    }

  public:

    size_t size()  const { return _default_size;      }
    bool   empty() const { return _default_size == 0; }

  private:
    std::set<value_t>            _set;
    size_t              _default_size;
    const_value_t  _default_value = 0;
};

} // namespace cppp
#endif
