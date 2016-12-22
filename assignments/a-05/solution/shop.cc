#include "shop.h"
#include "person.h"

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
  _register.erase(person->get_id());
  person -> leave_store();

}

} // namespace cpppc
