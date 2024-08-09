#include <fizzbuzz.h>
#include <gtest/gtest.h>

namespace {

// 通常の数字のテスト
TEST(FizzBuzzTest, NormalNumbers) {
  EXPECT_EQ("1", fizzbuzz(1));
  EXPECT_EQ("2", fizzbuzz(2));
  EXPECT_EQ("4", fizzbuzz(4));
}

// 3の倍数のテスト
TEST(FizzBuzzTest, MultiplesOfThree) {
  EXPECT_EQ("Fizz", fizzbuzz(3));
  EXPECT_EQ("Fizz", fizzbuzz(6));
  EXPECT_EQ("Fizz", fizzbuzz(9));
}

// 5の倍数のテスト
TEST(FizzBuzzTest, MultiplesOfFive) {
  EXPECT_EQ("Buzz", fizzbuzz(5));
  EXPECT_EQ("Buzz", fizzbuzz(10));
  EXPECT_EQ("Buzz", fizzbuzz(20));
}

// 3と5の両方の倍数のテスト
TEST(FizzBuzzTest, MultiplesOfThreeAndFive) {
  EXPECT_EQ("FizzBuzz", fizzbuzz(15));
  EXPECT_EQ("FizzBuzz", fizzbuzz(30));
  EXPECT_EQ("FizzBuzz", fizzbuzz(45));
}

}  // namespace
