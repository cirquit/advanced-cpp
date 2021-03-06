#ifndef CPPPC__A05__WORKER_H
#define CPPPC__A05__WORKER_H

#include <numeric>
#include <string>
#include <unordered_map>
#include <vector>
#include <list>
#include <functional>

namespace cpppc
{

class Section;
class Person;

class Worker
{
  typedef std::string article_name_t;
  typedef int         person_id_t;
  typedef Worker      self_t;

  public:

    Worker(std::string name
         , article_name_t article_name
         , Section * my_section)
    : _name(name)
    , _article_name(article_name)
    , _my_section(my_section)
    { }

    void kick_person(const Person * person)
    {
      _que.remove(person);
      // _que.remove(std::cref(person));
      // TODO notify person
    }

    void enque_person(const Person * person)
    {
      _que.push_back(person);  // FIFO
//      _que.push_back(std::cref(person));  // FIFO
//      _que.push_front(person.get_id()); // LIFO
    // TODO notify person
    }

    const article_name_t supported_article() const
    {
      return _article_name;
    }

  private:
    std::string                 _name;
    std::list<const Person *>   _que;
    article_name_t              _article_name;
    Section *                   _my_section;
};

} // namespace cpppc

#endif 
