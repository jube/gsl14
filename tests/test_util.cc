#include <gsl/gsl.h>

#include <climits>

#include "gtest/gtest.h"

/*
 * finally
 */

TEST(FinallyTest, Lambda) {
  int x = 0;

  {
    auto defer = gsl::finally([&]() { x = 1; });
    EXPECT_EQ(x, 0);
  }

  EXPECT_EQ(x, 1);
}

static void variableChanger(int& x) {
  x = 1;
}

TEST(FinallyTest, Bind) {
  int x = 0;

  {
    auto defer = gsl::finally(std::bind(&variableChanger, std::ref(x)));
    EXPECT_EQ(x, 0);
  }

  EXPECT_EQ(x, 1);
}

static int g_variable = 0;
static void variableModifier() {
  g_variable = 1;
}

TEST(FinallyTest, Function) {
  g_variable = 0;

  {
    auto defer = gsl::finally(&variableModifier);
    EXPECT_EQ(g_variable, 0);
  }

  EXPECT_EQ(g_variable, 1);
}


/*
 * narrow
 */

TEST(NarrowTest, ValidIntToFloat) {
  int x = 3;
  float y = 0.0f;

  EXPECT_NO_THROW({ y = gsl::narrow<float>(x); });
  EXPECT_FLOAT_EQ(y, 3.0f);
}


TEST(NarrowTest, InvalidIntToFloat) {
  int x = INT_MAX;
  float y = 0.0f;

  EXPECT_THROW({ y = gsl::narrow<float>(x); }, gsl::narrowing_error);
}

TEST(NarrowTest, ValidIntToUnsigned) {
  int x = 3;
  unsigned y = 0;

  EXPECT_NO_THROW({ y = gsl::narrow<unsigned>(x); });
  EXPECT_EQ(y, 3);
}

TEST(NarrowTest, InvalidIntToUnsigned) {
  int x = -1;
  unsigned y = 0;

  EXPECT_THROW({ y = gsl::narrow<unsigned>(x); }, gsl::narrowing_error);
}

TEST(NarrowTest, ValidUnsignedToInt) {
  unsigned x = UINT_MAX;
  int y = 0;

  EXPECT_THROW({ y = gsl::narrow<int>(x); }, gsl::narrowing_error);
}
