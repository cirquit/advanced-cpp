#ifndef CPPPC__A04__POOL_TEST_H__INCLUDED
#define CPPPC__A04__POOL_TEST_H__INCLUDED

#include <gtest/gtest.h>
#include "TestBase.h"

class PoolTest : public ::testing::Test {

public:

  PoolTest() {
    LOG_MESSAGE("Opening test suite: PoolTest");
  }

  virtual ~PoolTest() {
    LOG_MESSAGE("Closing test suite: PoolTest");
  }

  virtual void SetUp() {
  }

  virtual void TearDown() {
  }

};

#endif // CPPPC__A04__POOL_TEST_H__INCLUDED
