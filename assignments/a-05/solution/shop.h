#ifndef CPPPC__A05__SHOP_H
#define CPPPC__A05__SHOP_H

#include <numeric>
#include <string>
#include <unordered_map>
#include <vector>
#include <mutex>

namespace cpppc
{

class Person;
class Section;

class Shop
{
  typedef int         person_id_t;
  typedef std::string article_name_t;

  public:

    Shop(std::string name
     , std::unordered_map<std::string, int> goods
     , int section_count)
    : _name(name)
    , _goods(goods)
    {
      _sections = distribute_goods(section_count);
    }

    void enter(Person * person);

    void leave(Person * person);

  private:

    std::vector<Section> distribute_goods(int section_count)
    {
      // TODO
      return std::vector<Section>();
    }


  private:

    std::string                             _name;
    std::unordered_map<article_name_t, int> _goods;
    std::vector<Section>                    _sections;
    std::set<person_id_t>                   _register;
};

} // namespace cpppc


#endif 
