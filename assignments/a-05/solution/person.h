#ifndef CPPPC__A05__PERSON_H
#define CPPPC__A05__PERSON_H

#include "shop.h"

#include <numeric>
#include <algorithm>
#include <string>
#include <atomic>
#include <thread>
#include <unordered_map>


namespace cpppc {

class Person
{
  typedef int         person_id_t;
  typedef std::string article_name_t;

  public:

    Person(const Shop & shop1, const Shop & shop2, const Shop & shop3
         , const person_id_t person_id)
    : _shop1(shop1)
    , _shop2(shop2)
    , _shop3(shop3)
    , _person_id(person_id)
    { }

    std::thread its_go_time()
    {
      return std::thread( [=] { run(); });
    }

    bool operator==(const Person & rhs) const
    {
      return _person_id == rhs._person_id;
    }

    bool operator!=(const Person & rhs) const
    {
      return !(*this == rhs);
    }
  private:

    void run()
    {
      // policy here
    }


  private:

    Shop _shop1;
    Shop _shop2;
    Shop _shop3;
    person_id_t                             _person_id;
    std::unordered_map<article_name_t, int> _needs;
};


} // namespace cpppc

#endif 
