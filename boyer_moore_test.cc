#include "boyer_moore.h"
#include <gtest/gtest.h>
#include "benchmark/benchmark.h"

TEST(BoyerMoore, Basic) {
  BoyerMooreSearch s("foo");
  EXPECT_EQ(-1, s.Search("bar"));
  EXPECT_EQ(0, s.Search("foo"));
  EXPECT_EQ(2, s.Search("oofoo"));
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  bool run_benchmark = false;
  for (int i = 1; i < argc; ++i) {
    if (strncmp(argv[i], "--benchmark", 11) == 0) {
      run_benchmark = true;
    }
  }
  if (run_benchmark) {
    ::benchmark::Initialize(&argc, argv);
    ::benchmark::RunSpecifiedBenchmarks();
    return 0;
  }
  return RUN_ALL_TESTS();
}
