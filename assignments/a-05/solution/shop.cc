#include "shop.h"
#include "person.h"
#include "section.h"

namespace cpppc {

void Shop::enter(Person * person)
{
  static std::mutex enter_mx;
  std::lock_guard<std::mutex> io_lg(enter_mx);

  person -> timeout(1);
  _register.insert(person -> get_id();

}

void Shop::leave(Person * person)
{
  static std::mutex leave_mx;
  std::lock_guard<std::mutex> io_lg(leave_mx);

  _register.erase(person->get_id());
  person -> leave_store();
}

std::vector<Section> Shop::distribute_goods(int section_count)
{
//      _sections.reserve(section_count);
//    std::transform(_sections.begin(), _sections.end(), _sections.begin()
//                 ,[this, &section_count](Section & s){
//                   std::unordered_map<article_name_t, int> section_goods;
//                   section_goods.reserve(_goods.size());
//                     std::transform(_goods.begin(), _goods.end(), section_goods.begin()
//                                  ,[section_count](std::pair<article_name_t, int> & e)
//                                  {
//                                    e.second /= section_count;
//                                    return e;
//                                  });
//                     return section_goods;
//                   return Section("", std::unordered_map<std::string, int>());
//                   });
  return { };
}

} // namespace cpppc
