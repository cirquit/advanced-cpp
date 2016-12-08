#ifndef POOL_H

#include <iostream>
#include <mutex>
#include <set>
#include <stdexcept>  // length_error, invalid_argument
#include <iterator>   // advance
#include <algorithm>  // max

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
      , _default_size(std::distance(first, last))
    { }

  public:

    void release(value_t element)
    {
      static std::mutex io_mx;
      std::lock_guard<std::mutex> io_lg(io_mx);

      auto melem = _set.find(element);
      if (melem != _set.end()){
        throw std::invalid_argument("cpppc::Pool::release - duplicate element insertion");
      }

      _set.insert(element);
    }

    value_t acquire()
    {
      static std::mutex io_mx;
      std::lock_guard<std::mutex> io_lg(io_mx);

      std::srand(std::time(0));

      // VM randomness blocks, uncomment and try for yourself

      int random_index = 0; //std::rand() % std::max(_set.size(), _default_size);
      auto melement    = _set.begin();
      std::advance(melement, random_index);

      if (melement != _set.end()){
        value_t element = *melement;
        _set.erase(melement);
        std::cout << *melement << std::endl;
        return element;
      } else if (_default_size > 0){
        std::cout << "default" << std::endl;
        return _default_value;
      } else {
        throw std::length_error("cpppc:Pool::acquire - pool is empty");
      }
    }

  public:

    size_t size()  const { return std::max(_set.size(), _default_size); }
    bool   empty() const { return size() == 0; }

  private:
    std::set<value_t>            _set;
    size_t              _default_size;
    const_value_t  _default_value = 0;
};

} // namespace cppp
#endif
