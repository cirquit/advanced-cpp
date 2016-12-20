#ifndef CPPPC__A05__SHOP_H
#define CPPPC__A05__SHOP_H

#include "section.h"

#include <numeric>
#include <string>
#include <unordered_map>
#include <vector>


namespace cpppc
{

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

    void enter(int id)
    {
      // wait for 1 second
      // add to person-map
    }

  private:

    std::vector<Section> distribute_goods(int section_count)
    {
       return std::vector<Section>(); 
    }


  private:

    std::string                             _name;
    std::unordered_map<article_name_t, int> _goods;
    std::vector<Section>                    _sections;
    std::unordered_map<person_id_t, bool>   _register;
};

} // namespace cpppc


#endif CPPPC__A05__SHOP_H
