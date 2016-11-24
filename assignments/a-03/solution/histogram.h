#ifndef CPPPC__S03__HISTOGRAM_H__INCLUDED
#define CPPPC__S03__HISTOGRAM_H__INCLUDED

// Some headers you might find useful:
#include <unordered_map>
#include <set>
#include <algorithm>
#include <iterator>
#include <functional>

// if an element is found, the supplied function will take this element as the first argument
// and the value as the second
template <typename K, typename V>
void insertWith(K key, V value, std::unordered_map<K,V> umap, std::function<V (V,V)> f) {

    auto miter = umap.find(key);
    if(miter == umap.end()) {
        umap[key] = value;
    } else {
        umap[key] = f(miter->first, value);
    }
}

template <class Iter>
inline Iter histogram(Iter first, Iter last) {
    typedef typename std::iterator_traits<Iter>::value_type      value_t;
    typedef typename std::iterator_traits<Iter>::difference_type index_t;

    std::unordered_map<int,value_t> umap;
    std::vector<value_t>            res;

    for(auto iter = first; iter != last; ++iter){
        insertWith(*iter, 1, umap,
            [](int a, int b) -> int { return a + b; }
        );
    }

   for(auto iter = first; iter != last; ++iter){
      auto miter = umap.find(*iter);
      if(miter != umap.end()){
          res.push_back(miter->first);
          umap.erase(miter);
      }
   }

   // with this solution we should return the begin & end
   return res.end();
}

#endif // CPPPC__S03__HISTOGRAM_H__INCLUDED
