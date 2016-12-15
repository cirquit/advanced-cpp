#ifndef CPPPC__A04__BLACK_FRIDAY_TEST_H__INCLUDED
#define CPPPC__A04__BLACK_FRIDAY_TEST_H__INCLUDED

#include <gtest/gtest.h>
#include "TestBase.h"

class BlackFridayTest : public ::testing::Test {

public:

  BlackFridayTest() {
    LOG_MESSAGE("Opening test suite: BlackFridayTest");
  }

  virtual ~BlackFridayTest() {
    LOG_MESSAGE("Closing test suite: BlackFridayTest");
  }

  virtual void SetUp() {
  }

  virtual void TearDown() {
  }

};

#endif // CPPPC__A04__BLACK_FRIDAY_TEST_H__INCLUDED
