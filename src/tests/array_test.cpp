#include <array>

#include "test.h"

template class s21::Array<int, 5>;

TEST(ArrayTest, DefaultConstructor) {
  s21::Array<int, 5> arr;
  // Check that the size is correct
  EXPECT_EQ(arr.size(), 5);

  // Check that all elements are initialized to their default value (0 for int)
  for (size_t i = 0; i < arr.size(); ++i) {
    EXPECT_EQ(arr[i], 0);
  }
}

TEST(ArrayTest, InitListConstructor) {
  s21::Array<int, 5> arr({1, 2, 3, 4, 5});

  // Check that the size is correct
  EXPECT_EQ(arr.size(), 5);

  // Check that each element is initialized correctly
  for (size_t i = 0; i < arr.size(); ++i) {
    EXPECT_EQ(arr[i], static_cast<int>(i) + 1);
  }
}

TEST(ArrayTest, CopyConstructor) {
  s21::Array<int, 5> arr({1, 2, 3, 4, 5});
  s21::Array<int, 5> arrCopy(arr);

  // Check that the size is correct
  EXPECT_EQ(arrCopy.size(), 5);

  // Check that the elements are copied correctly
  for (size_t i = 0; i < arr.size(); ++i) {
    EXPECT_EQ(arrCopy[i], arr[i]);
  }
}

TEST(ArrayTest, MoveConstructor) {
  s21::Array<int, 5> arr({1, 2, 3, 4, 5});
  s21::Array<int, 5> arrMoved(std::move(arr));

  // Check that the size is correct
  EXPECT_EQ(arrMoved.size(), 5);

  // Check that the elements are moved correctly
  for (size_t i = 0; i < arrMoved.size(); ++i) {
    EXPECT_EQ(arrMoved[i], static_cast<int>(i) + 1);
  }
}

TEST(ArrayTest, Begin) {
  s21::Array<int, 5> arr({1, 2, 3, 4, 5});
  auto it = arr.begin();
  EXPECT_EQ(*it, 1);
  // Modify the data through the iterator and check if the array is updated
  *it = 10;
  EXPECT_EQ(arr[0], 10);
}

TEST(ArrayTest, End) {
  s21::Array<int, 5> arr({1, 2, 3, 4, 5});
  auto it = arr.end();
  // end() iterator should not be dereferenced; comparing it to another iterator
  // should work
  auto beginIt = arr.begin();
  EXPECT_EQ(it, beginIt + 5);
}

TEST(ArrayTest, At_ValidIndex) {
  s21::Array<int, 5> arr({1, 2, 3, 4, 5});
  int value = arr.at(2);
  EXPECT_EQ(value, 3);
}

TEST(ArrayTest, At_OutOfBounds) {
  s21::Array<int, 5> arr({1, 2, 3, 4, 5});
  // Attempting to access an out-of-bounds index using at() should throw an
  // exception
  EXPECT_THROW(arr.at(10), std::out_of_range);
}

TEST(ArrayTest, Front) {
  s21::Array<int, 5> arr({1, 2, 3, 4, 5});
  int value = arr.front();
  EXPECT_EQ(value, 1);
}

TEST(ArrayTest, Back) {
  s21::Array<int, 5> arr({1, 2, 3, 4, 5});
  int value = arr.back();
  EXPECT_EQ(value, 5);
}

TEST(ArrayTest, Empty_NonEmptyArray) {
  s21::Array<int, 5> arr({1, 2, 3, 4, 5});
  EXPECT_FALSE(arr.empty());
}

TEST(ArrayTest, Empty_EmptyArray) {
  s21::Array<int, 0> arr;
  EXPECT_TRUE(arr.empty());
}

TEST(ArrayTest, Size_NonEmptyArray) {
  s21::Array<int, 5> arr({1, 2, 3, 4, 5});
  EXPECT_EQ(arr.size(), 5);
}

TEST(ArrayTest, Size_EmptyArray) {
  s21::Array<int, 0> arr;
  EXPECT_EQ(arr.size(), 0);
}

TEST(ArrayTest, MaxSize) {
  s21::Array<int, 5> arr;
  // The max size of an array with a specified size is the same as its declared
  // size
  EXPECT_EQ(arr.max_size(), 5);
}

TEST(ArrayTest, Swap_1) {
  s21::Array<int, 5> arr1({1, 2, 3, 4, 5});
  s21::Array<int, 5> arr2({6, 7, 8, 9, 10});

  arr1.swap(arr2);

  // Check that the elements of arr1 are now from arr2
  for (size_t i = 0; i < arr1.size(); ++i) {
    EXPECT_EQ(arr1[i], static_cast<int>(i) + 6);
  }

  // Check that the elements of arr2 are now from arr1
  for (size_t i = 0; i < arr2.size(); ++i) {
    EXPECT_EQ(arr2[i], static_cast<int>(i) + 1);
  }
}

TEST(ArrayTest, Swap_2) {
  s21::Array<int, 5> arr1({1, 2, 3, 4, 5});
  EXPECT_NO_THROW(arr1.swap(arr1));
}

// TEST(ArrayTest, Swap_3) {
//   s21::Array<int, 5> arr1({1, 2, 3, 4, 5});
//   s21::Array<int, 6> arr2 = {6, 7, 8, 9, 10, 11};
//   EXPECT_THROW(arr1.swap(arr2), std::runtime_error);
// }

TEST(ArrayTest, Fill) {
  s21::Array<int, 5> arr;
  arr.fill(10);

  // Check that all elements are filled with the specified value
  for (size_t i = 0; i < arr.size(); ++i) {
    EXPECT_EQ(arr[i], 10);
  }
}

TEST(ArrayTest, MoveAssignmentOperator) {
  s21::Array<int, 5> arr1({1, 2, 3, 4, 5});
  s21::Array<int, 5> arr2({6, 7, 8, 9, 10});

  arr1 = std::move(arr2);

  // Check that arr1 now contains the same elements as arr2
  for (size_t i = 0; i < arr1.size(); ++i) {
    EXPECT_EQ(arr1[i], static_cast<int>(i) + 6);
  }
}

TEST(ArrayTest, OperatorBracket) {
  s21::Array<int, 5> arr({1, 2, 3, 4, 5});

  // Check that elements can be accessed using the [] operator
  for (size_t i = 0; i < arr.size(); ++i) {
    EXPECT_EQ(arr[i], static_cast<int>(i) + 1);
  }

  // Modify an element using the [] operator and check if the array is updated
  arr[2] = 10;
  EXPECT_EQ(arr[2], 10);
}

TEST(ArrayTest, Data) {
  s21::Array<int, 5> arr({1, 2, 3, 4, 5});
  auto iter = arr.data();
  for (auto i = 0, c = 0; i < 5; ++i) EXPECT_EQ(*(iter + i), ++c);
}

TEST(ArrayTest, ConstData) {
  const s21::Array<int, 5> arr({1, 2, 3, 4, 5});
  auto iter = arr.data();
  for (auto i = 0, c = 0; i < 5; ++i) EXPECT_EQ(*(iter + i), ++c);
}
