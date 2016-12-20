#ifndef CPPPC__A05__WORKER_H
#define CPPPC__A05__WORKER_H

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

  public:

    Worker(std::string name
         , article_name_t article_name
         , std::unordered_map<article_name_t, int> & section_goods)
    : _name(name)
    , _article_name(article_name)
    , _section_goods(section_goods)
    { }

    void kick_person(const Person & person)
    {
      _que.remove(person);
    }

    article_name_t supported_article()
    {
      return _article_name;
    }

  private:

    std::list<Person>                         _que;
    article_name_t                            _article_name;
    std::unordered_map<article_name_t, int> & _section_goods;

};

} // namespace cpppc

#endif CPPPC__A05__WORKER_H
