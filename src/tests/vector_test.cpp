#include <vector>

#include "test.h"

template class s21::Vector<int>;

TEST(VectorTest, DefaultConstructor_EmptyVector) {
  s21::Vector<int> v;
  EXPECT_TRUE(v.empty());
  EXPECT_EQ(v.Size(), 0);
}

TEST(VectorTest, SizeConstructor_PositiveSize) {
  const size_t size = 5;
  s21::Vector<int> v(size);
  EXPECT_FALSE(v.empty());
  EXPECT_EQ(v.Size(), size);
  for (size_t i = 0; i < size; ++i) {
    EXPECT_EQ(v[i], 0);
  }
}

TEST(VectorTest, SizeConstructor_ZeroSize) {
  const size_t size = 0;
  s21::Vector<int> v(size);
  EXPECT_TRUE(v.empty());
  EXPECT_EQ(v.Size(), size);
}

TEST(VectorTest, InitializerListConstructor_EmptyList) {
  s21::Vector<int> v = {};
  EXPECT_TRUE(v.empty());
  EXPECT_EQ(v.Size(), 0);
}

TEST(VectorTest, InitializerListConstructor_NonEmptyList) {
  s21::Vector<int> v({1, 2, 3, 4, 5});
  EXPECT_FALSE(v.empty());
  EXPECT_EQ(v.Size(), 5);
  EXPECT_EQ(v[0], 1);
  EXPECT_EQ(v[4], 5);
}

TEST(VectorTest, CopyConstructor_EmptyVector) {
  s21::Vector<int> v1;
  s21::Vector<int> v2(v1);
  EXPECT_TRUE(v2.empty());
  EXPECT_EQ(v2.Size(), 0);
}

TEST(VectorTest, CopyConstructor_NonEmptyVector) {
  s21::Vector<int> v1({1, 2, 3});
  s21::Vector<int> v2(v1);
  EXPECT_EQ(v2.Size(), v1.Size());
  for (size_t i = 0; i < v1.Size(); ++i) {
    EXPECT_EQ(v2[i], v1[i]);
  }
}

TEST(VectorTest, MoveConstructor_EmptyVector) {
  s21::Vector<int> v1;
  s21::Vector<int> v2(std::move(v1));
  EXPECT_TRUE(v2.empty());
  EXPECT_EQ(v2.Size(), 0);
}

TEST(VectorTest, MoveConstructor_NonEmptyVector) {
  s21::Vector<int> v1({1, 2, 3});
  s21::Vector<int> v2(std::move(v1));
  EXPECT_EQ(v2.Size(), 3);
  EXPECT_TRUE(v1.empty());  // Source vector should be empty after move
}

TEST(VectorTest, Destructor_EmptyVector) {
  s21::Vector<int>* v = new s21::Vector<int>();
  delete v;  // Destructor should be called here
  // No specific assertions, but this ensures the destructor is working
}

TEST(VectorTest, Destructor_NonEmptyVector) {
  s21::Vector<int>* v = new s21::Vector<int>{1, 2, 3};
  delete v;  // Destructor should be called here
  // No specific assertions, but this ensures the destructor is working
}

TEST(VectorTest, MoveAssignmentOperator_EmptyToEmpty) {
  s21::Vector<int> v1;
  s21::Vector<int> v2;
  v2 = std::move(v1);
  EXPECT_TRUE(v2.empty());
  EXPECT_EQ(v2.Size(), 0);
}

TEST(VectorTest, MoveAssignmentOperator_NonEmptyToEmpty) {
  s21::Vector<int> v1({1, 2, 3});
  s21::Vector<int> v2;
  v2 = std::move(v1);
  EXPECT_EQ(v2.Size(), 3);
  EXPECT_TRUE(v1.empty());  // Source vector should be empty after move
}

TEST(VectorTest, MoveAssignmentOperator_EmptyToNonEmpty) {
  s21::Vector<int> v1;
  s21::Vector<int> v2({4, 5, 6});
  v2 = std::move(v1);
  EXPECT_TRUE(v2.empty());
  EXPECT_EQ(v2.Size(), 0);
}

TEST(VectorTest, MoveAssignmentOperator_NonEmptyToNonEmpty) {
  s21::Vector<int> v1({1, 2, 3});
  s21::Vector<int> v2({4, 5, 6});
  v2 = std::move(v1);
  EXPECT_EQ(v2.Size(), 3);
  EXPECT_TRUE(v1.empty());  // Source vector should be empty after move
}

TEST(VectorTest, At_ValidIndex) {
  s21::Vector<int> v({1, 2, 3, 4, 5});
  EXPECT_EQ(v.At(0), 1);
  EXPECT_EQ(v.At(2), 3);
  EXPECT_EQ(v.At(4), 5);
}

TEST(VectorTest, At_InvalidIndex) {
  s21::Vector<int> v({1, 2, 3, 4, 5});
  EXPECT_THROW(v.At(5), std::out_of_range);
  EXPECT_THROW(v.At(10), std::out_of_range);
}

TEST(VectorTest, IndexOperator_ValidIndex) {
  s21::Vector<int> v({1, 2, 3, 4, 5});
  EXPECT_EQ(v[0], 1);
  EXPECT_EQ(v[2], 3);
  EXPECT_EQ(v[4], 5);
}

TEST(VectorTest, IndexOperator_InvalidIndex) {
  s21::Vector<int> v({1, 2, 3, 4, 5});
  EXPECT_ANY_THROW(v[5]);
  EXPECT_ANY_THROW(v[10]);
}

TEST(VectorTest, ConstIndexOperator_ValidIndex) {
  const s21::Vector<int> v({1, 2, 3, 4, 5});
  EXPECT_EQ(v[0], 1);
  EXPECT_EQ(v[2], 3);
  EXPECT_EQ(v[4], 5);
}

TEST(VectorTest, ConstIndexOperator_InvalidIndex) {
  const s21::Vector<int> v({1, 2, 3, 4, 5});
  EXPECT_ANY_THROW(v[5]);
  EXPECT_ANY_THROW(v[10]);
}

TEST(VectorTest, FrontConst_ValidVector) {
  const s21::Vector<int> v({1, 2, 3, 4, 5});
  EXPECT_EQ(v.Front(), 1);
}

TEST(VectorTest, FrontConst_EmptyVector) {
  const s21::Vector<int> v;
  EXPECT_THROW(v.Front(), std::out_of_range);
}

TEST(VectorTest, BackConst_ValidVector) {
  const s21::Vector<int> v({1, 2, 3, 4, 5});
  EXPECT_EQ(v.Back(), 5);
}

TEST(VectorTest, BackConst_EmptyVector) {
  const s21::Vector<int> v;
  EXPECT_THROW(v.Back(), std::out_of_range);
}

TEST(VectorTest, Data_ValidVector) {
  s21::Vector<int> v({1, 2, 3, 4, 5});
  int* dataPtr = v.Data();
  EXPECT_EQ(*dataPtr, 1);
  // Modify the data through the pointer and check if the vector is updated
  *dataPtr = 10;
  EXPECT_EQ(v[0], 10);
}

TEST(VectorTest, Data_EmptyVector) {
  s21::Vector<int> v;
  int* dataPtr = v.Data();
  // Data pointer of an empty vector can be anything
  EXPECT_EQ(dataPtr, nullptr);
}

TEST(VectorTest, Begin_ValidVector) {
  s21::Vector<int> v({1, 2, 3, 4, 5});
  auto it = v.Begin();
  EXPECT_EQ(*it, 1);
  // Modify the data through the iterator and check if the vector is updated
  *it = 10;
  EXPECT_EQ(v[0], 10);
}

TEST(VectorTest, Begin_EmptyVector) {
  s21::Vector<int> v;
  auto it = v.Begin();
  // The begin() of an empty vector should be the end() too, so iterator should
  // be equal to end()
  EXPECT_EQ(it, v.End());
}

TEST(VectorTest, End_ValidVector) {
  s21::Vector<int> v({1, 2, 3, 4, 5});
  auto it = v.End();
  // end() iterator should not be dereferenced; comparing it to another iterator
  // should work
  auto beginIt = v.Begin();
  EXPECT_NE(it, beginIt);
}

TEST(VectorTest, End_EmptyVector) {
  s21::Vector<int> v;
  auto it = v.End();
  // The end() of an empty vector should be the begin() too, so iterator should
  // be equal to begin()
  EXPECT_EQ(it, v.Begin());
}

TEST(VectorTest, CBegin_ValidVector) {
  const s21::Vector<int> v({1, 2, 3, 4, 5});
  auto it = v.Cbegin();
  EXPECT_EQ(*it, 1);
  // Modify the data through the iterator and check if the vector is not updated
  // (should be const_iterator) Uncommenting the following line should result in
  // a compilation error. *it = 10;
}

TEST(VectorTest, CBegin_EmptyVector) {
  const s21::Vector<int> v;
  auto it = v.Cbegin();
  // The cbegin() of an empty vector should be the cend() too, so iterator
  // should be equal to cend()
  EXPECT_EQ(it, v.Cend());
}

TEST(VectorTest, CEnd_ValidVector) {
  const s21::Vector<int> v({1, 2, 3});
  auto it = v.Cend();
  // cend() iterator should not be dereferenced; comparing it to another
  // iterator should work
  auto beginIt = v.Cbegin();
  ++beginIt;
  beginIt++;  // cppcheck-suppress postfixOperator
  ++beginIt;
  EXPECT_EQ(it, beginIt);
}

TEST(VectorTest, CEnd_EmptyVector) {
  const s21::Vector<int> v;
  auto it = v.Cend();
  // The cend() of an empty vector should be the cbegin() too, so iterator
  // should be equal to cbegin()
  EXPECT_EQ(it, v.Cbegin());
}

TEST(VectorTest, Empty_EmptyVector) {
  const s21::Vector<int> v;
  EXPECT_TRUE(v.empty());
}

TEST(VectorTest, Empty_NonEmptyVector) {
  const s21::Vector<int> v({1, 2, 3});
  EXPECT_FALSE(v.empty());
}

TEST(VectorTest, Size_EmptyVector) {
  const s21::Vector<int> v;
  EXPECT_EQ(v.Size(), 0);
}

TEST(VectorTest, Size_NonEmptyVector) {
  const s21::Vector<int> v({1, 2, 3});
  EXPECT_EQ(v.Size(), 3);
}

TEST(VectorTest, MaxSize) {
  const s21::Vector<int> v;
  // You can't predict the exact max size, but it should be a very large value
  EXPECT_GT(v.Max_Size(), 0);
}

TEST(VectorTest, Reserve_IncreaseCapacity) {
  s21::Vector<int> v;
  size_t initialCapacity = v.Capacity();
  size_t newCapacity = initialCapacity + 10;
  v.Reserve(newCapacity);
  EXPECT_GE(v.Capacity(), newCapacity);
}

TEST(VectorTest, Reserve_DecreaseCapacity) {
  s21::Vector<int> v({1, 2, 3, 4, 5});
  size_t initialCapacity = v.Capacity();
  size_t newCapacity = initialCapacity - 2;
  v.Reserve(newCapacity);
  // Capacity may not decrease immediately, but it shouldn't exceed the
  // requested value
  EXPECT_LE(v.Capacity(), initialCapacity);
  EXPECT_GE(v.Capacity(), newCapacity);
}

TEST(VectorTest, Capacity_EmptyVector) {
  const s21::Vector<int> v;
  // The capacity of an empty vector should be at least 0
  EXPECT_GE(v.Capacity(), 0);
}

TEST(VectorTest, Capacity_NonEmptyVector) {
  const s21::Vector<int> v({1, 2, 3});
  // The capacity of a non-empty vector might vary, but it should be at least
  // the size of the vector
  EXPECT_GE(v.Capacity(), v.Size());
}

TEST(VectorTest, ShrinkToFit_EmptyVector) {
  s21::Vector<int> v;
  v.Shrink_To_Fit();
  // After shrink_to_fit() on an empty vector, the capacity should still be at
  // least 0
  EXPECT_GE(v.Capacity(), 0);
}

TEST(VectorTest, ShrinkToFit_NonEmptyVector) {
  s21::Vector<int> v({1, 2, 3, 4, 5});
  size_t initialCapacity = v.Capacity();
  v.Pop_Back();  // Simulate a reduction in size
  v.Shrink_To_Fit();
  // After shrink_to_fit(), the capacity should not exceed the new size
  EXPECT_LE(v.Capacity(), v.Size());
  // The capacity may not necessarily decrease, but it should not be larger than
  // the initial capacity
  EXPECT_LE(v.Capacity(), initialCapacity);
}

TEST(VectorTest, Clear_EmptyVector) {
  s21::Vector<int> v;
  v.Clear();
  EXPECT_TRUE(v.empty());
  EXPECT_EQ(v.Size(), 0);
  // Clearing an empty vector should not affect capacity
  EXPECT_GE(v.Capacity(), 0);
}

TEST(VectorTest, Clear_NonEmptyVector) {
  s21::Vector<int> v({1, 2, 3, 4, 5});
  v.Clear();
  EXPECT_TRUE(v.empty());
  EXPECT_EQ(v.Size(), 0);
  // Clearing a vector should not affect capacity immediately
  EXPECT_GE(v.Capacity(), 0);
}

TEST(VectorTest, Insert_Beginning) {
  s21::Vector<int> v({2, 3, 4});
  auto it = v.Insert(v.Begin(), 1);
  EXPECT_EQ(v.Size(), 4);
  EXPECT_EQ(v[0], 1);
  EXPECT_EQ(*it, 1);
}

TEST(VectorTest, Insert_Middle) {
  s21::Vector<int> v({1, 3, 4});
  auto it = v.Insert(v.Begin() + 1, 2);
  EXPECT_EQ(v.Size(), 4);
  EXPECT_EQ(v[1], 2);
  EXPECT_EQ(*it, 2);
}

TEST(VectorTest, Insert_End) {
  s21::Vector<int> v({1, 2, 3});
  auto it = v.Insert(v.End(), 4);
  EXPECT_EQ(v.Size(), 4);
  EXPECT_EQ(v[3], 4);
  EXPECT_EQ(*it, 4);
}

TEST(VectorTest, Erase_Beginning) {
  s21::Vector<int> v({1, 2, 3, 4});
  v.Erase(v.Begin());  // Erase the first element
  EXPECT_EQ(v.Size(), 3);
  EXPECT_EQ(v[0], 2);
}

TEST(VectorTest, Erase_Middle) {
  s21::Vector<int> v({1, 2, 3, 4});
  v.Erase(v.Begin() + 1);
  EXPECT_EQ(v.Size(), 3);
  EXPECT_EQ(v[1], 3);
}

TEST(VectorTest, Erase_End) {
  s21::Vector<int> v({1, 2, 3, 4});
  v.Erase(v.End() - 1);  // Erase the last element
  EXPECT_EQ(v.Size(), 3);
  EXPECT_EQ(v[2], 3);
}

TEST(VectorTest, Erase_Throw) {
  s21::Vector<int> v({1, 2, 3, 4});
  EXPECT_ANY_THROW(v.Erase(v.End()));
}

TEST(VectorTest, PushBack_EmptyVector) {
  s21::Vector<int> v;
  v.Push_Back(1);
  EXPECT_EQ(v.Size(), 1);
  EXPECT_EQ(v[0], 1);
}

TEST(VectorTest, PushBack_NonEmptyVector) {
  s21::Vector<int> v({1, 2, 3});
  v.Push_Back(4);
  EXPECT_EQ(v.Size(), 4);
  EXPECT_EQ(v[3], 4);
}

TEST(VectorTest, PopBack_NonEmptyVector) {
  s21::Vector<int> v({1, 2, 3});
  v.Pop_Back();
  EXPECT_EQ(v.Size(), 2);
  EXPECT_EQ(v.Back(), 2);
}

TEST(VectorTest, PopBack_EmptyVector) {
  s21::Vector<int> v;
  v.Pop_Back();
  EXPECT_TRUE(v.empty());
}

TEST(VectorTest, Swap_NonEmptyVectors) {
  s21::Vector<int> v1({1, 2, 3});
  s21::Vector<int> v2({4, 5, 6});

  v1.Swap(v2);

  EXPECT_EQ(v1.Size(), 3);
  EXPECT_EQ(v2.Size(), 3);

  EXPECT_EQ(v1[0], 4);
  EXPECT_EQ(v1[2], 6);

  EXPECT_EQ(v2[0], 1);
  EXPECT_EQ(v2[2], 3);
}

TEST(VectorTest, Swap_EmptyAndNonEmptyVectors) {
  s21::Vector<int> v1;
  s21::Vector<int> v2({1, 2, 3});

  v1.Swap(v2);

  EXPECT_EQ(v1.Size(), 3);
  EXPECT_FALSE(v1.empty());
  EXPECT_EQ(v2.Size(), 0);
  EXPECT_TRUE(v2.empty());
}

TEST(VectorTest, InsertMany) {
  s21::Vector<int> vec({1, 2, 3, 7, 8});
  s21::Vector<int>::const_iterator pos = vec.Cbegin();
  ++pos;
  pos++;
  ++pos;

  vec.Insert_Many(pos, 4, 5, 6);

  // Check the size of the vector after insertion
  EXPECT_EQ(vec.Size(), 8);

  // Check the elements after insertion
  EXPECT_EQ(vec[0], 1);
  EXPECT_EQ(vec[1], 2);
  EXPECT_EQ(vec[2], 3);
  EXPECT_EQ(vec[3], 4);
  EXPECT_EQ(vec[4], 5);
  EXPECT_EQ(vec[5], 6);
  EXPECT_EQ(vec[6], 7);
  EXPECT_EQ(vec[7], 8);
}

TEST(VectorTest, InsertManyBack) {
  s21::Vector<int> vec({1, 2, 3});

  vec.Insert_Many_Back(4, 5, 6);

  // Check the size of the vector after insertion
  EXPECT_EQ(vec.Size(), 6);

  // Check the elements after insertion
  EXPECT_EQ(vec[0], 1);
  EXPECT_EQ(vec[1], 2);
  EXPECT_EQ(vec[2], 3);
  EXPECT_EQ(vec[3], 4);
  EXPECT_EQ(vec[4], 5);
  EXPECT_EQ(vec[5], 6);
}

TEST(VectorTest, VectorIterator) {
  s21::Vector<int> vec({1, 2, 3});
  s21::Vector<int>::VectorIterator it;
  it = vec.Begin();
  it++;  // cppcheck-suppress postfixOperator
  EXPECT_EQ(*it, 2);
  ++it;
  EXPECT_EQ(*it, 3);
  it--;  // cppcheck-suppress postfixOperator
  EXPECT_EQ(*it, 2);
  --it;
  EXPECT_EQ(*it, 1);
}

TEST(VectorTest, VectorIteratorConst) {
  const s21::Vector<int> vec({1, 2, 3});
  s21::Vector<int>::VectorIteratorConst it;
  it = vec.Cbegin();
  it++;  // cppcheck-suppress postfixOperator
  EXPECT_EQ(*it, 2);
  ++it;
  EXPECT_EQ(*it, 3);
  it--;  // cppcheck-suppress postfixOperator
  EXPECT_EQ(*it, 2);
  --it;
  EXPECT_EQ(*it, 1);
}
