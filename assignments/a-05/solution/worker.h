#ifndef CPPPC__A05__WORKER_H
#define CPPPC__A05__WORKER_H

#include "section.h"
#include "person.h"

#include <numeric>
#include <string>
#include <unordered_map>
#include <vector>
#include <list>

namespace cpppc
{

class Worker
{
  typedef std::string article_name_t;
  typedef Worker      self_t;

  public:

    Worker(std::string name
         , article_name_t article_name
         , Section & my_section)
    : _name(name)
    , _article_name(article_name)
    , _my_section(my_section)
    { }

    void kick_person(const Person & person)
    {
      _que.remove(person);
    }

    void enque_person(const Person & person)
    {
      _que.push_back(person);  // FIFO
//      _que.push_front(person); // LIFO
    }


    Worker(const self_t & other) = default;
    self_t & operator=(const self_t & other) = default;

    const article_name_t supported_article() const
    {
      return _article_name;
    }

  private:
    std::string                               _name;
    std::list<Person>                         _que;
    article_name_t                            _article_name;
    Section &                                 _my_section;
};

} // namespace cpppc

#endif 