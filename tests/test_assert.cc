#include <gsl/gsl.h>

#include "gtest/gtest.h"

TEST(AssertTest, ExpectsWhenSuccess) {
  EXPECT_NO_THROW(gsl::Expects(true));
}

TEST(AssertTest, ExpectsWhenFailure) {
  EXPECT_THROW(gsl::Expects(false), std::logic_error);
}

TEST(AssertTest, EnsuresWhenSuccess) {
  EXPECT_NO_THROW(gsl::Ensures(true));
}

TEST(AssertTest, EnsuresWhenFailure) {
  EXPECT_THROW(gsl::Ensures(false), std::logic_error);
}
