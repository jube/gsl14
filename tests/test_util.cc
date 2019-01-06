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

TEST(FinallyTest, ThrowingLambda) {
  int x = 0;

  {
    auto defer = gsl::finally([&]() { x = 1; throw std::runtime_error(""); });
    EXPECT_EQ(x, 0);
  }

  EXPECT_EQ(x, 1);
}

TEST(FinallyTest, Discarded) {
  int x = 0;

  {
    gsl::finally([&]() { x = 1; });
    EXPECT_EQ(x, 1);
  }

  EXPECT_EQ(x, 1);
}

/*
 * narrow
 */

TEST(NarrowTest, ValidLongToShort) {
  long x = 3;
  short y = 3;

  EXPECT_NO_THROW({ y = gsl::narrow<short>(x); });
  EXPECT_FLOAT_EQ(y, 3);
}

TEST(NarrowTest, InvalidLongToShort) {
  long x = LONG_MAX;
  short y = 0;

  EXPECT_THROW({ y = gsl::narrow<short>(x); }, gsl::narrowing_error);
  EXPECT_FLOAT_EQ(y, 0);
}

TEST(NarrowTest, ValidIntToFloat) {
  int x = 3;
  float y = 0.0f;

  EXPECT_NO_THROW({ y = gsl::narrow<float>(x); });
  EXPECT_FLOAT_EQ(y, 3.0f);
}


TEST(NarrowTest, InvalidIntToFloat) {
  int x = 2147483644;
  float y = 0.0f;

  EXPECT_THROW({ y = gsl::narrow<float>(x); }, gsl::narrowing_error);
  EXPECT_FLOAT_EQ(y, 0.0f);
}

TEST(NarrowTest, ValidIntToUnsigned) {
  int x = 3;
  unsigned y = 0;

  EXPECT_NO_THROW({ y = gsl::narrow<unsigned>(x); });
  EXPECT_EQ(y, 3u);
}

TEST(NarrowTest, InvalidIntToUnsigned) {
  int x = -1;
  unsigned y = 0;

  EXPECT_THROW({ y = gsl::narrow<unsigned>(x); }, gsl::narrowing_error);
  EXPECT_EQ(y, 0u);
}

TEST(NarrowTest, ValidUnsignedToInt) {
  unsigned x = UINT_MAX;
  int y = 0;

  EXPECT_THROW({ y = gsl::narrow<int>(x); }, gsl::narrowing_error);
  EXPECT_EQ(y, 0);
}
