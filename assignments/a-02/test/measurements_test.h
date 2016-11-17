#ifndef CPPPC__A02__MEASUREMENTS_TEST_H__INCLUDED
#define CPPPC__A02__MEASUREMENTS_TEST_H__INCLUDED

#include <gtest/gtest.h>
#include <cmath>
#include "TestBase.h"

class MeasurementsTest : public ::testing::Test {

public:

  MeasurementsTest() {
    LOG_MESSAGE("Opening test suite: MeasurementsTest");
  }

  virtual ~MeasurementsTest() {
    LOG_MESSAGE("Closing test suite: MeasurementsTest");
  }

  virtual void SetUp() {
  }

  virtual void TearDown() {
  }

  // round to 2 decimal places for the tests
  inline double round2(double d) {
    return std::roundf(d * 100) / 100;
  }


};

#endif // CPPPC__A02__MEASUREMENTS_TEST_H__INCLUDED
