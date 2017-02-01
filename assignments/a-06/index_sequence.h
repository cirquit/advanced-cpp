#ifndef CPPPC__A06__INDEX_SEQUENCE_H__INCLUDED
#define CPPPC__A06__INDEX_SEQUENCE_H__INCLUDED

// Consider:
// http://ldionne.com/2015/11/29/efficient-parameter-pack-indexing/

namespace ce {

template <
  std::size_t... Is >
struct index_sequence
{ };

template <
  std::size_t    N,
  std::size_t... Is >
struct make_index_sequence
  : make_index_sequence<N-1, N-1, Is...>
{ };

template <
  std::size_t... Is>
struct make_index_sequence<0, Is...>
  : index_sequence<Is...>
{ };

} // namespace ce

#endif // CPPPC__A06__INDEX_SEQUENCE_H__INCLUDED