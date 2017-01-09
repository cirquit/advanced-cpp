#include <vector>
#include <algorithm>
#include <iostream>
#include <string>

class BaseFrequentFlyer {
public:

  BaseFrequentFlyer()
  : _name("")
  , _number(0)
  , _miles(0) { }

  BaseFrequentFlyer(std::string name, int number, int miles)
  : _name(name)
  , _number(number)
  , _miles(miles) { }

  void addMiles ( int realMiles ) { _miles += realMiles; }
  void printData ()
  {
      std::cout << "Name: " << _name << std::endl;
      std::cout << "Number: " << _number << std::endl;
      std::cout << "Miles: " << _miles << std::endl;
  }

protected:
  std::string _name;
  int         _number;
  int         _miles;

};

class FrequentFlyer : public BaseFrequentFlyer {
public:
  FrequentFlyer(std::string name, int number, int miles)
  : BaseFrequentFlyer(name, number, miles) { }
};

class SilverFrequentFlyer : public FrequentFlyer {
public:
  SilverFrequentFlyer(std::string name, int number, int miles, int years)
  : FrequentFlyer(name, number, miles), _years(years) { }

private:
  int _years;
};

class GoldFrequentFlyer : public FrequentFlyer {
public:
  GoldFrequentFlyer(std::string name, int number, int miles, int years)
  : FrequentFlyer(name, number, miles), _years(years) { }

private:
  int _years;
};


int main()
{
    std::vector<BaseFrequentFlyer> f { FrequentFlyer ("Cornelius Doe", 23166841, 100)
                                     , SilverFrequentFlyer ("Lucius Doe", 94565432, 100, 5)
                                     , GoldFrequentFlyer("Rufus Doe", 32155994, 100, 100) };

    for_each(f.begin()
           , f.end()
           , [](BaseFrequentFlyer & flyer)
           {
             flyer.addMiles(100);
             flyer.printData();
           });
}