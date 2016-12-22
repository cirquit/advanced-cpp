#ifndef CPPPC__A05__SECTION_H
#define CPPPC__A05__SECTION_H

#include <mutex>
#include <set>
#include <numeric>
#include <algorithm>
#include <string>
#include <unordered_map>
#include <vector>

namespace cpppc
{

class Person;
class Worker;

class Section
{
  typedef int         person_id_t;
  typedef std::string article_name_t;

  public:

    Section(std::string name
          , std::unordered_map<article_name_t, int> section_goods);
    : _name(name)
    , _section_goods(section_goods)
    {
      _workers.reserve(_section_goods.size());
      std::transform(_section_goods.begin(), _section_goods.end()
                   , _workers.begin(), [this](const std::pair<article_name_t, int> & e)
                   {
                      return Worker(e.first + " worker", e.first, this);
                   });
    }

    void enque(Person & person);

    void deque(Person & person);

  private:
    std::string                              _name;
    std::unordered_map<article_name_t, int>  _section_goods;
    std::set<person_id_t>                    _section_register;
    std::vector<Worker>                      _workers;
};

} // namespace cpppc

#endif
