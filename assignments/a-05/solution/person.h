#ifndef CPPPC__A05__PERSON_H
#define CPPPC__A05__PERSON_H

#include <numeric>
#include <algorithm>
#include <string>
#include <atomic>
#include <thread>
#include <unordered_map>
#include <chrono>

namespace cpppc {

class Shop;

class Person
{
  typedef int         person_id_t;
  typedef std::string article_name_t;

  public:

    Person(std::vector<const Shop *> shop_list
         , const person_id_t person_id)
    : _shop_list(shop_list)
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

    const person_id_t & get_id() const
    {
      return _person_id;
    }

    void timeout(int seconds) const;

    void leave_store();

    void enter_store(const Shop * shop);

  private:

    void run()
    {
      // policy here
      // if _cur_shop !has_value && _needs.size() > 0 then do something
      // else quit
    }

  private:

    std::vector<const Shop *>               _shop_list;
    const person_id_t                       _person_id;
    std::unordered_map<article_name_t, int> _needs;
    std::pair<const Shop *, bool>           _cur_shop; // optional only since c++17

};


} // namespace cpppc

#endif
