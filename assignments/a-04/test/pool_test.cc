#include "pool_test.h"

#include <solution/pool.h>

#include <gtest/gtest.h>
#include <thread>
#include <iostream>
#include <list>
#include <algorithm>
#include <numeric>
#include <iterator>
#include <stdexcept>

using cpppc::Pool;

TEST_F(PoolTest, SequentialDefaultConstructed)
{
  LOG_MESSAGE("PoolTest.SequentialDefaultConstructed");

  Pool<int> pool(3);

  EXPECT_FALSE(pool.empty());

  auto e1 = pool.acquire();
  auto e2 = pool.acquire();
  auto e3 = pool.acquire();

  // Default-constructed ints have value 0:
  EXPECT_EQ(0, e1);
  EXPECT_EQ(0, e2);
  EXPECT_EQ(0, e3);

  pool.release(e1);

  auto e1_2 = pool.acquire();

  EXPECT_EQ(0, e1_2);

  try { pool.release(e1_2); }
  catch(std::invalid_argument const & err) {
    EXPECT_EQ(err.what()
           , std::string("cpppc::Pool::release - duplicate element insertion"));
  }

  try { pool.release(e2); }
  catch(std::invalid_argument const & err) {
    EXPECT_EQ(err.what()
           , std::string("cpppc::Pool::release - duplicate element insertion"));
  }

  try { pool.release(e3); }
  catch(std::invalid_argument const & err) {
    EXPECT_EQ(err.what()
          , std::string("cpppc::Pool::release - duplicate element insertion"));
  }

}

TEST_F(PoolTest, SequentialRangeConstructed)
{
  LOG_MESSAGE("PoolTest.SequentialRangeConstructed");
  std::array<int, 5> pool_elems {{ 10, 20, 30, 40, 50 }};

  Pool<int> p(pool_elems.begin(), pool_elems.end());

  EXPECT_FALSE(p.empty());
  EXPECT_EQ(pool_elems.size(), p.size());

  std::vector<int> acquired;
  for (size_t i = 0; i < p.size(); i++) {
    acquired.push_back(p.acquire());
  }

  EXPECT_EQ(acquired.size(), p.size());
  EXPECT_EQ(acquired.size(), pool_elems.size());

  EXPECT_NE(std::find(acquired.begin(), acquired.end(), 10), acquired.end());
  EXPECT_NE(std::find(acquired.begin(), acquired.end(), 20), acquired.end());
  EXPECT_NE(std::find(acquired.begin(), acquired.end(), 30), acquired.end());
  EXPECT_NE(std::find(acquired.begin(), acquired.end(), 40), acquired.end());
  EXPECT_NE(std::find(acquired.begin(), acquired.end(), 50), acquired.end());

  // Make one element available in pool:
  p.release(30);
  // Acquired element should be only element available:
  EXPECT_EQ(30, p.acquire());
}

template <class PoolT, class AcquiredContainer>
void acquire_n(PoolT & pool, size_t n_acquire, AcquiredContainer & cont) {
  for (size_t i = 0; i < n_acquire; i++) {
    cont.push_back(pool.acquire());
  }
}

TEST_F(PoolTest, Parallel)
{
  LOG_MESSAGE("PoolTest.Parallel");

  const int POOL_SIZE   = 10240;
  const int NUM_THREADS = 10;

  std::vector<int> elems(POOL_SIZE);
  std::iota(elems.begin(), elems.end(), 1000);

  Pool<int> p(elems.begin(), elems.end());

  EXPECT_FALSE(p.empty());
  EXPECT_EQ(elems.size(), p.size());

  std::array<std::vector<int>, NUM_THREADS> acq_in_thread;

  std::vector<std::thread> threads;
  for (int t = 0; t < NUM_THREADS; t++) {
    threads.push_back(
      std::thread(
        acquire_n<Pool<int>, std::vector<int>>,
        std::ref(p),
        POOL_SIZE / NUM_THREADS,
        std::ref(acq_in_thread[t]))
    );
  }
  for (auto & t : threads) {
    t.join();
  }

  int acq_total = 0;
  for (auto & t_acq : acq_in_thread) {
    acq_total += t_acq.size();
  }

  EXPECT_EQ(POOL_SIZE, acq_total);

  // Check that no element has been acquired by more than one thread:
  for (int a = 0; a < NUM_THREADS; a++) {
    for (int b = 0; b < NUM_THREADS; b++) {
      if (a == b) { continue; }
      std::vector<int> acq_intersect;
      auto & acq_a = acq_in_thread[a];
      auto & acq_b = acq_in_thread[b];
      std::set_intersection(acq_a.begin(), acq_a.end(),
                            acq_b.begin(), acq_b.end(),
                            std::back_inserter(acq_intersect));
      EXPECT_EQ(static_cast<size_t>(0), acq_intersect.size());
    }
  }
}

