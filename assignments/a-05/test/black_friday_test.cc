
#include "black_friday_test.h"
#include "solution/shop.h"
#include "solution/section.h"
#include "solution/worker.h"
#include "solution/person.h"

#include <gtest/gtest.h>

#include <iostream>
#include <list>
#include <algorithm>
#include <iterator>
#include <thread>
#include <mutex>
#include <cstdlib>
#include <unordered_map>

TEST_F(BlackFridayTest, HordeTest)
{
  LOG_MESSAGE("BlackFridayTest.RandomAccessIterators");

  std::unordered_map<std::string, int> walmart_goods = {
     {"Couch",         100}
   , {"FlatscreenTV",  100}
   , {"Hammock",       100}
   , {"CoffeeMachine", 100}
   , {"Ammunition",    100}
  };

  std::unordered_map<std::string, int> kmart_goods = {
     {"Diesel",      100}
   , {"Fertilizer",  100}
   , {"Bleach",      100}
   , {"RubberGlove", 100}
   , {"Soap",        100}
  };

  std::unordered_map<std::string, int> toys_r_us_goods = {
     {"Pikachu",         100}
   , {"DoraTheExplorer", 100}
   , {"TrumpActionToy",  100}
   , {"Firetruck",       100}
   , {"TickleMeElmo",    100}
  };

  cpppc::Shop walmart   = cpppc::Shop("Walmart", walmart_goods, 5);
  cpppc::Shop kmart     = cpppc::Shop("Kmart", kmart_goods, 5);
  cpppc::Shop toys_r_us = cpppc::Shop("ToysRUs", toys_r_us_goods, 5);

}


/*
enum WalmartProduct : int {
  Couch,
  FlatscreenTV,
  Hammock,
  CoffeeMachine,
  Ammunition
};

enum ToysRUsProduct : int {
  Pikachu,
  DoraTheExplorer,
  TrumpActionToy,
  Firetruck,
  TickleMeElmo
};

enum KmartProduct : int {
  Diesel,
  Fertilizer,
  Bleach,
  RubberGlove,
  Soap
};

template<typename ProductT>
std::pair<ProductT, int> make() {
  return std::make_pair(
                static_cast<ProductT>(std::rand() % 5),
                std::rand() % 100);
}


TEST_F(BlackFridayTest, HordeTest)
{
  LOG_MESSAGE("BlackFridayTest.RandomAccessIterators");

  static const int horde_size       =    1000;
  static const int walmart_capacity = 1000000;
  static const int toysrus_capacity =  400000;
  static const int kmart_capacity   =  500000;

  // The shopping centers:
  std::unordered_map<WalmartProduct, int> walmart;
  std::unordered_map<ToysRUsProduct, int> toysrus;
  std::unordered_map<KmartProduct,   int> kmart;

  // The dear customers:
  std::vector<std::thread> horde;

  //std::generate_n(std::inserter(walmart, walmart.end()), walmart_capacity, make<WalmartProduct>);
  //std::generate_n(std::inserter(toysrus, toysrus.end()), toysrus_capacity, make<ToysRUsProduct>);
  //std::generate_n(std::inserter(kmart,   kmart.end()),   kmart_capacity,   make<KmartProduct>);

  //int num_total_products = walmart.size() + toysrus.size() + kmart.size();
  //std::cout << num_total_products << std::endl;
}
*/
