#ifndef CPPPC__S03__HISTOGRAM_H__INCLUDED
#define CPPPC__S03__HISTOGRAM_H__INCLUDED

// Some headers you might find useful:
#include <unordered_map>
#include <set>
#include <algorithm>
#include <iterator>
#include <functional>

# if 0
template <typename K, typename V, class BinaryFunction>
void insertWith(K key, V value, std::unordered_map<K,V> & umap, BinaryFunction f) {

    auto miter = umap.find(key);
    if(miter == umap.end()) {
        umap[key] = value;
    } else {
        umap[key] = f(miter->first, value);
    }
}
#endif

template <class Iter>
inline Iter histogram(Iter first, Iter last) {
    typedef typename std::iterator_traits<Iter>::value_type      value_t;
//    typedef typename std::iterator_traits<Iter>::difference_type index_t;

    std::unordered_map<value_t,int> umap;
    std::vector<value_t>            res;

    std::for_each(first, last, [&](value_t & x) { umap[x] += 1; });

    std::remove_if(first, last,
        [&](value_t & x){
          auto miter = umap.find(x);
          if (miter != umap.end()){
            x = miter->second;
            return true;
          } else {
            return false;
          }
        });
    return last;
}

#endif // CPPPC__S03__HISTOGRAM_H__INCLUDED
