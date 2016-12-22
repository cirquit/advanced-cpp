#include "person.h"
#include "shop.h"

namespace cpppc {

void Person::timeout(int seconds) const
{
  std::cout << "Person #" << this->get_id() <<  " waiting for " << seconds << "s!" << std::endl;
  std::chrono::seconds sec(seconds);
  std::this_thread::sleep_for(sec);
}

void Person::leave_store()
{
  _cur_shop.second = false;
}

void Person::enter_store(const Shop * shop)
{
  shop -> enter(this);
  _cur_shop.first = shop;
  _cur_shop.second = true;
}

// void Person::

} // cpppc
