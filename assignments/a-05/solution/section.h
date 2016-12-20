#ifndef CPPPC__A05__SECTION_H
#define CPPPC__A05__SECTION_H

#include "worker.h"

#include <numeric>
#include <string>
#include <unordered_map>
#include <vector>


namespace cpppc
{

class Section
{
  typedef int         person_id_t;
  typedef std::string article_name_t;

  public:

    // there are always the exact amount of workers as there are
    // unique items, so they don't block each other
    Section(std::string name
          , std::unordered_map<article_name_t, int> section_goods)
    : _name(name)
    , _section_goods(section_goods)
    {
      _workers.reserve(_section_goods.size());
      std::transform(_section_goods.begin(), _section_goods.end()
                   , _workers.begin(), [](const auto & e)
                   {
                      return Worker(e.first, & _section_goods);
                   }
    }

  private:
    std::name                                _name;
    std::unordered_map<article_name_t, int>  _section_goods;
    std::unordered_map<person_id_t, bool>    _section_register;
    std::vector<Worker>                      _workers;
};


} // namespace cpppc


#endif CPPPC__A05__SECTION_H
