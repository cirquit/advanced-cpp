#ifndef CPPPC__CHUNKS_H__INCLUDED
#define CPPPC__CHUNKS_H__INCLUDED

#include <vector>
#include <array>
#include <cstdlib>

namespace cpppc {

namespace detail {

template <class ContainerT>
class delegate_iterator
{
public:
  
  using self_t          = delegate_iterator<ContainerT>;
  using element_t       = typename ContainerT::value_type;

  using iterator_category = std::random_access_iterator_tag;
  using difference_type   = typename ContainerT::difference_type;
  using value_type        = element_t;
  using pointer           = element_t *;
  using reference         = element_t &;

public:
   delegate_iterator() = delete;
   delegate_iterator(ContainerT & container)
   : _container(container)
   , _pos(0) // a chunk.begin() starts always at the first position,
             // even if it was already traversed a bit in the previous iterator
   { }

public:

  inline element_t & operator*()
  {
    return _container[_pos];
  }

  // blatantly copied from the solution in a-03
  inline self_t & operator++() {
    ++_pos;
    return *this;
  }

  inline self_t & operator--() {
    --_pos;
    return *this;
  }

  inline self_t operator++(int) {
    self_t copy(*this);
    ++_pos;
    return copy;
  }

  inline self_t operator--(int) {
    self_t copy(*this);
    --_pos;
    return copy;
  }
  inline self_t operator+(const int &n) {
    self_t copy(*this);
    copy._pos += n;
    return copy;
  }
  inline self_t operator-(const int &n) {
    self_t copy(*this);
    copy._pos -= n;
    return copy;
  }
  inline difference_type operator-(const self_t &rhs) const {
    return _pos - rhs._pos;
  }

  inline self_t & operator+=(const difference_type n) {
    _pos += n;
    return *this;
  }
  inline self_t & operator-=(const difference_type n) {
    _pos -= n;
    return *this;
  }
  inline self_t & operator=(const self_t &other) {
    _pos = other._pos;
    return *this;
  }

  inline self_t operator[](int offset) const {
    return *(*this + offset);
  }

// Comparison
  inline bool operator==(const self_t &other) const {
    return (&_container == &(other._container) && _pos == other._pos);
  }
  inline bool operator!=(const self_t &other) const {
    return !(&_container == &(other._container) && _pos == other._pos);
  }
  inline bool operator<=(const self_t &other) const {
    return _pos <= other._pos;
  }
  inline bool operator<(const self_t &other) const {
    return _pos < other._pos;
  }
  inline bool operator>=(const self_t &other) const {
    return _pos >= other._pos;
  }
  inline bool operator>(const self_t &other) const {
    return _pos > other._pos;
  }

private:
  ContainerT &    _container;
  difference_type _pos;
};


template <class ChunksT>
class chunks_iterator
{
public:
  using self_t          = chunks_iterator<ChunksT>;
  using element_t       = typename ChunksT::chunk_t;

  using iterator_category = std::random_access_iterator_tag;
  using difference_type   = typename ChunksT::difference_type;
  using value_type        = element_t;
  using pointer           = element_t *;
  using reference         = element_t &;

public:
  using iterator           = delegate_iterator<element_t>;
  using inner_element_t    = typename ChunksT::value_t;
  using inner_difference_t = typename ChunksT::index_t;

  friend iterator;

public:
  chunks_iterator() = delete;
  chunks_iterator(ChunksT & chunks, difference_type pos)
  : _chunks(chunks)
  , _pos(pos) { }


public:
  inline element_t & operator*()
  {
    element_t & chunk = _chunks._chunks[_pos];
    return chunk;
  }

  // blatantly copied from the solution in a-03
  inline self_t & operator++() {
    ++_pos;
    return *this;
  }

  inline self_t & operator--() {
    --_pos;
    return *this;
  }

  inline self_t operator++(int) {
    self_t copy(*this);
    ++_pos;
    return copy;
  }

  inline self_t operator--(int) {
    self_t copy(*this);
    --_pos;
    return copy;
  }
  inline self_t operator+(const int &n) {
    self_t copy(*this);
    copy._pos += n;
    return copy;
  }
  inline self_t operator-(const int &n) {
    self_t copy(*this);
    copy._pos -= n;
    return copy;
  }
  inline difference_type operator-(const self_t &rhs) const {
    return _pos - rhs._pos;
  }

  inline self_t & operator+=(const difference_type n) {
    _pos += n;
    return *this;
  }
  inline self_t & operator-=(const difference_type n) {
    _pos -= n;
    return *this;
  }
  inline self_t & operator=(const self_t &other) {
    _pos = other._pos;
    return *this;
  }

// Comparison
  inline bool operator==(const self_t &other) const {
    return (&_chunks == &(other._chunks) && _pos == other._pos);
  }
  inline bool operator!=(const self_t &other) const {
    return !(&_chunks == &(other._chunks) && _pos == other._pos);
  }
  inline bool operator<=(const self_t &other) const {
    return _pos <= other._pos;
  }
  inline bool operator<(const self_t &other) const {
    return _pos < other._pos;
  }
  inline bool operator>=(const self_t &other) const {
    return _pos >= other._pos;
  }
  inline bool operator>(const self_t &other) const {
    return _pos > other._pos;
  }

  iterator begin() const {
    return iterator(_chunks._chunks[_pos]);
  }

  iterator end() const {
    return iterator(_chunks._chunks[_pos]);
  }

  inline inner_element_t operator[](int offset) const {
    return *(begin() + offset);
  }

private:
//  this can be used to calculate the offsetted beginning of the chunks, if needed
//  const std::ldiv_t get_current_chunk_info() const
//  {
//    return std::div(static_cast<long>(_pos), static_cast<long>(_max_bounds));
//  }

private:
  ChunksT &       _chunks;
  difference_type _pos = 0;
};

}; // namespace detail

template <std::size_t B, class T, class Container>
class chunks
{

public:
  using self_t          = chunks<B, T, Container>;

  using chunk_t         = std::array<T,B>;
  using chunk_ref       = chunk_t &;
  using chunk_const_ref = const chunk_t &;
  using chunk_index_t   = size_t;

  using value_t         = T;
  using reference       = T &;
  using const_reference = const T &;
  using index_t         = size_t;

public:
  using iterator        = detail::chunks_iterator<self_t>;
  using difference_type = chunk_index_t;

  friend iterator;

public:
  chunks(Container container)
  { 
    int i = 0;
    std::for_each(container.begin()
                 ,container.end()
                 ,[&](T & item){

                    if (_chunks.empty() ||  i >= B)
                    { 
                      _chunks.push_back(std::array<T, B> {{ item }});
                      std::cout << "Created new array with: " << item << '\n';
                      i = 1;
                    } else
                    {
                      _chunks.back()[i] = item;
                      std::cout << "Appended to array: " << item << '\n';
                      ++i;
                    }
                  });

    _end = iterator(*this, _chunks.size());
  }

  iterator begin() { return _begin; }
  iterator end()   { return _end;   }

  inline chunk_t operator[](int offset) const {
    return _chunks[offset];
  }

private:
  std::vector<std::array<T,B>> _chunks;

  iterator _begin = iterator(*this, 0);
  iterator _end   = iterator(*this, 0);
};

} // namespace cppp

#endif