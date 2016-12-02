#ifndef CPPPC__S03__SPARSE_ARRAY_H__INCLUDED
#define CPPPC__S03__SPARSE_ARRAY_H__INCLUDED

#include <unordered_map>

namespace cpppc {

namespace detail {

template <class SparseArrayT>
class sparse_array_proxy_ref;

template <class SparseArrayT>
class sparse_array_iterator
{
  private:
    typedef sparse_array_iterator<SparseArrayT> self_t;
    typedef long                                index_t;

  public:
    using iterator_category = std::random_access_iterator_tag;
    using difference_type   = std::ptrdiff_t;
    using elem_t            = typename SparseArrayT::value_t; // compiler told me to use typename, why tho?
    using value_type        = elem_t;
    using pointer           = elem_t *;
    using reference         = elem_t &;
    using proxy_reference   = sparse_array_proxy_ref<SparseArrayT>;

  public:
    sparse_array_iterator(
        reference sparse_array
      , index_t   index)
      : _sarr(sparse_array),
        _idx(index)
      { }

# if 0
    const value_type & operator*() const { return *this; }    we use * to return the reference in every other function,
                                                              but now we 'overloaded' it to return the value_type, how does
                                                              the compiler know what to do?
# endif
    proxy_reference & operator*()       {                    return proxy_reference(_sarr, _idx);  }
    const elem_t    & operator*() const { return const_cast<elem_t>(proxy_reference(_sarr, _idx)); }

    inline self_t & operator++()   {                     ++_idx; return *this; }
    inline self_t & operator++(int){ self_t res = *this; ++_idx; return res;   }

    friend inline self_t operator+(difference_type lhs, const self_t & rhs) {
      return sparse_array_iterator(rhs._sarr, rhs._idx + lhs);
    }
    friend inline self_t operator-(difference_type lhs, const self_t & rhs) {
      return sparse_array_iterator(rhs._sarr, rhs._idx - lhs);
    }
    inline self_t & operator+=(difference_type rhs)      {        _idx += rhs; return *this; }
    inline self_t & operator-=(difference_type rhs)      {        _idx -= rhs; return *this; }
    inline self_t & operator+(difference_type rhs) const { self_t temp = this; return temp += rhs; }
    inline self_t & operator-(difference_type rhs) const { self_t temp = this; return temp -= rhs; }
 
    inline bool operator==(const self_t & rhs) const {
      return (*this  == rhs)
          || ( _idx  == rhs._idx
          &&  *_sarr == *rhs._sarr);
    }
    inline bool operator!=(const self_t & other) const { return !(*this == other); }
    inline bool operator<(const self_t & other)  const { return _idx < other._idx; }
    inline bool operator>(const self_t & other)  const { return _idx > other._idx; }
    inline bool operator<=(const self_t & other) const { return !(this > other);   }
    inline bool operator>=(const self_t & other) const { return !(this < other);   }

  private:
    reference _sarr;
    index_t   _idx;
};

template <class SparseArrayT>
class sparse_array_proxy_ref
{

  public:
    typedef sparse_array_iterator<SparseArrayT> self_t;
    typedef long                                index_t;
    typedef SparseArrayT &                      reference;
    typedef typename SparseArrayT::value_t      elem_t;    // same question as in #27

  public:
    sparse_array_proxy_ref(
        reference sarr
      , index_t idx)
      : _sarr(sarr)
      , _idx(idx)
    { }

    operator elem_t() const { return get_element(); }

// i just can't get the viable candidate function :(
    self_t & operator=(self_t & other) const {
      if (&this == other) return *this;
      _sarr[_idx] = static_cast<elem_t>(other);
      return _sarr[_idx];
    }

    void operator=(self_t & lhs, self_t & rhs) const {
      if (lhs == rhs) return lhs;
      lhs._sarr[lhs._idx] = static_cast<elem_t>(rhs);
      return lhs;
    }

    void operator=(self_t & lhs, elem_t & rhs) const {
      if (lhs == rhs) return lhs;
      lhs._sarr[lhs._idx] = rhs;
    }
//

    self_t & operator=(elem_t & other) const {
      _sarr._umap[_idx] = other;
      return *this;
    }

    bool operator==(self_t & other) const {
      if (*this == other) return true;
      return static_cast<elem_t>(*this)
          == static_cast<elem_t>(other);
    }

    bool operator!=(self_t & other){ return !(*this == other);}

    bool operator<(self_t & other){
      return static_cast<elem_t>(*this)
           < static_cast<elem_t>(other);
    }

    bool operator>(self_t & other){
      return static_cast<elem_t>(*this)
           > static_cast<elem_t>(other);
    }

    bool operator>=(self_t & other){ return !(*this < other); }
    bool operator<=(self_t & other){ return !(*this > other); }

    void swap(self_t & lhs, self_t & rhs) {
      // TODO 
    }

  private:
    elem_t get_element(){
      auto miter = _sarr.umap.find(_idx);
      if(miter == _sarr.umap.end()){
        return _sarr.default_value;
      } else {
        return miter->second;
      }
    }

  private:
    reference _sarr;
    index_t   _idx;

};

} // namespace detail


template <class T, std::size_t N>
class sparse_array
{

public:
  typedef sparse_array<T, N>                      self_t;
  typedef detail::sparse_array_proxy_ref<self_t>  proxy_reference;
  typedef int                                     index_t;
  typedef       T                                 value_t;
  typedef       T &                             reference;
  typedef const T &                       const_reference;

public:

  typedef detail::sparse_array_iterator<self_t>   iterator;
  typedef index_t                                 difference_type;

  friend iterator;
  friend proxy_reference;

public:

  sparse_array(value_t def)
    : _begin(0)
    , _default_value(def)
    , _asize(N)
  { }

  sparse_array()
    : _begin(0)
    , _default_value(0)
    , _asize(N)
  { }

  sparse_array(const sparse_array<T,N> & other){
    _default_value  = other._default_value;
    _asize          = other._asize;
    _umap           = other._umap;
  }

  iterator       at(index_t pos)       { return std::advance(begin(), pos); }
  const iterator at(index_t pos) const { return std::advance(begin(), pos); }

  proxy_reference operator[](index_t pos)       { return sparse_array_proxy_ref(at(pos)); }
  const_reference operator[](index_t pos) const { return sparse_array_proxy_ref(at(pos)); }

  proxy_reference front()       { return at(0); }
  const_reference front() const { return at(0); }

  proxy_reference back()       { return at(_asize-1); }
  const_reference back() const { return at(_asize-1); }

  iterator       begin()        { return _begin; }
  iterator       rbegin()       { return _begin + _asize - 1; }
  const iterator begin()  const { return _begin; }
  const iterator rbegin() const { return _begin + _asize - 1; }

  iterator       end()        { return _begin + _asize; }
  iterator       rend()       { return _begin - 1; }
  const iterator end()  const { return _begin + _asize; }
  const iterator rend() const { return _begin - 1; }

  size_t size()     const { return _asize;      }
  bool   empty()    const { return size() == 0; }
  size_t max_size() const { return size();      }

  void fill(const_reference value){
    _umap.clear();
    _default_value = value;
  }

  bool operator==(const self_t & rhs){
    const self_t & lhs = *this;
    return lhs == rhs
        && lhs._default_value == rhs._default_value
        && lhs._umap          == rhs._umap
        && lhs._asize         == rhs._asize;
  }

  bool operator<(const self_t & rhs){
    const self_t & lhs = *this;
    return lhs._asize < rhs._asize
        && lhs._umap  < rhs._umap
        && lhs._default_value < rhs._default_value;
  }
  bool operator>(const self_t & rhs){
    return rhs < *this;
  }

  bool operator<=(const self_t & rhs){
	return !(*this > rhs);
  }
  bool operator>=(const self_t & rhs){
	return !(*this < rhs);
  }

# if 0
  template<std::size_t I>
  const_reference get(self_t & value){
    return value.at[I];
  }
# endif
  void swap(self_t & lhs, self_t & rhs) {
    // TODO 
  }

private:

  value_t                              _default_value;
  size_t                               _asize;
  std::unordered_map<index_t, value_t> _umap;
  iterator                             _begin;
};

} // namespace cpppc

#endif // CPPPC__S03__SPARSE_ARRAY_H__INCLUDED
