#ifndef CPPPC__CHUNKS_H__INCLUDED
#define CPPPC__CHUNKS_H__INCLUDED

#include <vector>
#include <array>

namespace cpppc {

namespace detail {

template <class ChunksT>
class chunks_iterator
{
public:
	using self_t    = chunks_iterator<ChunksT>;
	using element_t = typename ChunksT::container_t;

	using iterator_category = std::random_access_iterator_tag;
	using difference_type   = typename ChunksT::container_difference_type;
	using value_type        = element_t;
	using pointer           = element_t *;
	using reference         = element_t &;

public:
	chunks_iterator() = delete;
	chunks_iterator(ChunksT & chunks, difference_type pos)
	: _chunks(chunks)
	, _pos(pos) { }

	inline const element_t & operator*() const
	{
		return 
	}
private:
	ChunksT & 	    _chunks;
	difference_type _pos = 0;
};




}; // namespace detail

template <std::size_t B, class T, class Container>
class chunks
{

public:
	using self_t   		      = chunks<B, T, Container>;
	
	using container_t         = Container;
	using container_ref       = Container &;
	using container_const_ref = const Container &;
	using container_index_t   = size_t;

	using index_t  		      = size_t;
	using value_t  		      = T;
	using reference  	      = T &;          			
	using const_reference     = const T &;

public:
	using iterator 		 		 = detail::chunks_iterator<self_t> ;
	using const_iterator 		 = detail::chunks_iterator<const self_t>;
	using container_difference_t = container_index_t;
	
	friend iterator;

public:
	chunks(Container container)
	{ }

private:
	void fill_up(Container container) {}

private:
	std::vector<std::array<T, B>> _chunks;
//	iterator 					  _begin;
};


} // namespace cppp

#endif