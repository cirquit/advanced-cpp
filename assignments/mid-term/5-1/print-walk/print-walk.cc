#include <iostream>
#include <algorithm>
#include <iterator>

#include <vector>
#include <list>
#include <sstream>

// using dispatcher function from cppreference

template <class RandomAccess>
void print_walk(RandomAccess begin, RandomAccess end, std::random_access_iterator_tag)
{
  std::random_shuffle(begin,end);
  std::cout << "RandomAccess Iterator:  ";
  for(auto it = begin; it != end; ++it){
      std::cout << *it << " ";
  }
  std::cout << '\n';

}

template <class BiDirectional>
void print_walk(BiDirectional begin, BiDirectional end, std::bidirectional_iterator_tag)
{
  std::reverse(begin, end);
  std::cout << "BiDirectional Iterator: ";
  for(auto it = begin; it != end; ++it)
  {
    std::cout << *it << " ";
  }
  std::cout << '\n';
}

template <class Input>
void print_walk(Input begin, Input end, std::input_iterator_tag)
{
  std::cout << "Input Iterator:         ";
  for(auto it = begin; it != end; ++it)
  {
    std::cout << *it << " ";
  }
  std::cout << '\n';
}

template< class Iter >
void print_walk(Iter first, Iter last)
{
    print_walk(first, last,
        typename std::iterator_traits<Iter>::iterator_category());
}


int main(int argc, char const *argv[])
{
  std::vector<int>       v  { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
  std::list<int>         l  { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };

  std::istringstream s("0123456789");
  std::istream_iterator<char> eos;
  std::istream_iterator<char> isi(s);

  std::cout << "Vector          is a  "; 
  print_walk(v.begin(), v.end());
  std::cout << "List            is a  ";
  print_walk(l.begin(), l.end());
  std::cout << "IStreamIterator is an ";
  print_walk(isi, eos);

  return 0;
}