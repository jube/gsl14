#include <gsl/gsl.h>

#include <memory>

#include "gtest/gtest.h"

TEST(NotNullTest, PointerWhenNotNull) {
  int x = 3;
  EXPECT_NO_THROW({ gsl::not_null<int*> ptr(&x); });
}

TEST(NotNullTest, PointerWhenNull) {
  int* ref = nullptr;
  EXPECT_THROW({ gsl::not_null<int*> ptr(ref); }, std::logic_error);
}

TEST(NotNullTest, UniqueWhenNotNull) {
  auto ref = std::make_unique<int>(3);
  EXPECT_NO_THROW({ gsl::not_null<std::unique_ptr<int>> ptr(std::move(ref)); });
}

TEST(NotNullTest, UniqueWhenNull) {
  std::unique_ptr<int> ref = nullptr;
  EXPECT_THROW({ gsl::not_null<std::unique_ptr<int>> ptr(std::move(ref)); }, std::logic_error);
}

TEST(NotNullTest, SharedWhenNotNull) {
  auto ref = std::make_shared<int>(3);
  EXPECT_NO_THROW({ gsl::not_null<std::shared_ptr<int>> ptr(ref); });
}

TEST(NotNullTest, SharedWhenNull) {
  std::shared_ptr<int> ref = nullptr;
  EXPECT_THROW({ gsl::not_null<std::shared_ptr<int>> ptr(ref); }, std::logic_error);
}
