#include <gsl/gsl.h>

#include <memory>

#include "gtest/gtest.h"

namespace {

  struct Dummy {
    Dummy(int x_value) : x(x_value) { }

    int x;
  };
}

TEST(NotNullTest, PointerWhenNotNull) {
  int x = 3;
  EXPECT_NO_THROW({ gsl::not_null<int*> ptr(&x); });
}

TEST(NotNullTest, PointerWhenNull) {
  int* ref = nullptr;
  EXPECT_THROW({ gsl::not_null<int*> ptr(ref); }, std::logic_error);
}

// unique_ptr

TEST(NotNullTest, UniqueWhenNotNull) {
  auto ref = std::make_unique<int>(3);
  EXPECT_NO_THROW({ gsl::not_null<std::unique_ptr<int>> ptr(std::move(ref)); });
}

TEST(NotNullTest, UniqueWhenNull) {
  std::unique_ptr<int> ref = nullptr;
  EXPECT_THROW({ gsl::not_null<std::unique_ptr<int>> ptr(std::move(ref)); }, std::logic_error);
}

TEST(NotNullTest, UniqueWhenDereferencing) {
  gsl::not_null<std::unique_ptr<Dummy>> ptr(std::make_unique<Dummy>(3));

  Dummy d = *ptr;
  EXPECT_EQ(d.x, 3);
}

TEST(NotNullTest, UniqueWhenAccessing) {
  gsl::not_null<std::unique_ptr<Dummy>> ptr(std::make_unique<Dummy>(3));

  EXPECT_EQ(ptr->x, 3);
}

// shared_ptr

TEST(NotNullTest, SharedWhenNotNull) {
  auto ref = std::make_shared<int>(3);
  EXPECT_NO_THROW({ gsl::not_null<std::shared_ptr<int>> ptr(ref); });
}

TEST(NotNullTest, SharedWhenNull) {
  std::shared_ptr<int> ref = nullptr;
  EXPECT_THROW({ gsl::not_null<std::shared_ptr<int>> ptr(ref); }, std::logic_error);
}

TEST(NotNullTest, SharedWhenDereferencing) {
  gsl::not_null<std::shared_ptr<Dummy>> ptr(std::make_shared<Dummy>(3));

  Dummy d = *ptr;
  EXPECT_EQ(d.x, 3);
}

TEST(NotNullTest, SharedWhenAccessing) {
  gsl::not_null<std::shared_ptr<Dummy>> ptr(std::make_shared<Dummy>(3));

  EXPECT_EQ(ptr->x, 3);
}

// owner

TEST(NotNullTest, OwnerWhenNotNull) {
  auto ref = gsl::owner<int*>(new int(3));
  EXPECT_NO_THROW({ gsl::not_null<gsl::owner<int*>> ptr(ref); });
  delete ref;
}

TEST(NotNullTest, OwnerWhenNull) {
  auto ref = gsl::owner<int*>(nullptr);
  EXPECT_THROW({ gsl::not_null<gsl::owner<int*>> ptr(ref); }, std::logic_error);
  delete ref;
}

TEST(NotNullTest, OwnerWhenDereferencing) {
  gsl::not_null<gsl::owner<Dummy*>> ptr(new Dummy(3));

  Dummy d = *ptr;
  EXPECT_EQ(d.x, 3);
  delete ptr;
}

TEST(NotNullTest, OwnerWhenAccessing) {
  gsl::not_null<gsl::owner<Dummy*>> ptr(new Dummy(3));

  EXPECT_EQ(ptr->x, 3);
  delete ptr;
}
