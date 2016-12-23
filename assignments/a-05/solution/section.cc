#include "section.h"
#include "person.h"

namespace cpppc {

Section::Section(std::string name
        , std::unordered_map<article_name_t, int> section_goods);
        : _name(name)
        , _section_goods(section_goods)
  {
    _workers.reserve(_section_goods.size());
    std::transform(_section_goods.begin(), _section_goods.end()
               , _workers.begin(), [this](const std::pair<article_name_t, int> & e
               {
                  return Worker(e.first + " worker", e.first, this);
               });
  }

void Section::enque(Person & person)
{
   _section_register.insert(person.get_id());
}

void Section::deque(Person & person)
{
  _section_register.erase(person.get_id());
}

}
