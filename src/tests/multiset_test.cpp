#include <set>

#include "test.h"

template class s21::multiset<int>;

TEST(multiset, ConstructorDefaultSet) {
  s21::multiset<int> myEmptySet;
  std::multiset<int> origEmptySet;
  EXPECT_EQ(myEmptySet.empty(), origEmptySet.empty());
}

TEST(multiset, ConstructorInitializerSet) {
  s21::multiset<int> mySet({6, 2, 2, 9, 9, 9, 7, 7, 7, 7});
  std::multiset<int> origSet({6, 2, 2, 9, 9, 9, 7, 7, 7, 7});
  EXPECT_EQ(mySet.size(), origSet.size());
  auto myIt = mySet.begin();
  auto origIt = origSet.begin();
  for (size_t i = 0, n = origSet.size(); i < n; ++i, ++myIt, ++origIt) {
    EXPECT_TRUE(*origIt == *myIt);
  }
}

TEST(multiset, ConstructorInitializer2Set) {
  s21::multiset<int> mySet = {};
  std::multiset<int> origSet = {};
  EXPECT_EQ(mySet.size(), origSet.size());
  auto myIt = mySet.begin();
  auto origIt = origSet.begin();
  for (size_t i = 0, n = origSet.size(); i < n; ++i, ++myIt, ++origIt) {
    EXPECT_TRUE(*origIt == *myIt);
  }
}

TEST(multiset, ConstructorCopySet) {
  const s21::multiset<int> mySet({1, 1, 1, 2, 3, 3, 4, 5, 5});
  const std::multiset<int> origSet({1, 1, 1, 2, 3, 3, 4, 5, 5});
  s21::multiset<int> mySetCopy = mySet;
  std::multiset<int> origSetCopy = origSet;
  EXPECT_EQ(mySetCopy.size(), origSetCopy.size());
  auto myIt = mySetCopy.begin();
  auto origIt = origSetCopy.begin();
  for (size_t i = 0, n = origSet.size(); i < n; ++i, ++myIt, ++origIt) {
    // std::cout << *origIt << " " << *myIt << std::endl;
    EXPECT_TRUE(*origIt == *myIt);
  }
}

TEST(multiset, OperatorCopySet) {
  const s21::multiset<int> mySet({1, 1, 1, 2, 3, 3, 4, 5, 5});
  const std::multiset<int> origSet({1, 1, 1, 2, 3, 3, 4, 5, 5});
  s21::multiset<int> mySetCopy;
  std::multiset<int> origSetCopy;
  mySetCopy = mySet;
  origSetCopy = origSet;
  EXPECT_EQ(mySetCopy.size(), origSetCopy.size());
  auto myIt = mySetCopy.begin();
  auto origIt = origSetCopy.begin();
  for (size_t i = 0, n = origSet.size(); i < n; ++i, ++myIt, ++origIt) {
    EXPECT_TRUE(*origIt == *myIt);
  }
}

TEST(multiset, ConstructorMoveSet) {
  s21::multiset<int> mySet({1, 1, 1, 2, 3, 3, 4, 5, 5});
  std::multiset<int> origSet({1, 1, 1, 2, 3, 3, 4, 5, 5});
  s21::multiset<int> mySetCopy = std::move(mySet);
  std::multiset<int> origSetCopy = std::move(origSet);
  EXPECT_EQ(mySet.size(), origSet.size());
  EXPECT_EQ(mySetCopy.size(), origSetCopy.size());
  auto myIt = mySetCopy.begin();
  auto origIt = origSetCopy.begin();
  for (size_t i = 0, n = origSetCopy.size(); i < n; ++i, ++myIt, ++origIt) {
    EXPECT_TRUE(*origIt == *myIt);
  }
}

TEST(multiset, OperatorMoveSet) {
  s21::multiset<int> mySet({1, 1, 1, 2, 3, 3, 4, 5, 5});
  std::multiset<int> origSet({1, 1, 1, 2, 3, 3, 4, 5, 5});
  s21::multiset<int> mySetCopy;
  std::multiset<int> origSetCopy;
  mySetCopy = std::move(mySet);
  origSetCopy = std::move(origSet);
  EXPECT_EQ(mySet.size(), origSet.size());
  EXPECT_EQ(mySetCopy.size(), origSetCopy.size());
  auto myIt = mySetCopy.begin();
  auto origIt = origSetCopy.begin();
  for (size_t i = 0, n = origSetCopy.size(); i < n; ++i, ++myIt, ++origIt) {
    EXPECT_TRUE(*origIt == *myIt);
  }
}

TEST(multiset, SetIteratorsSet) {
  s21::multiset<int> mySet({1, 1, 1, 2, 3, 3, 4, 5, 5});
  std::multiset<int> origSet({1, 1, 1, 2, 3, 3, 4, 5, 5});
  auto myIt = mySet.begin();
  auto origIt = origSet.begin();
  EXPECT_TRUE(*origIt == *myIt);
}

TEST(multiset, CapacitySet) {
  s21::multiset<int> myEmptySet;
  std::multiset<int> origEmptySet;
  EXPECT_EQ(myEmptySet.empty(), origEmptySet.empty());
  EXPECT_EQ(myEmptySet.size(), origEmptySet.size());
  myEmptySet.insert('b');
  origEmptySet.insert('c');
  EXPECT_EQ(myEmptySet.empty(), origEmptySet.empty());
  EXPECT_EQ(myEmptySet.size(), origEmptySet.size());
}

TEST(multiset, ClearSet) {
  s21::multiset<int> myEmptySet;
  std::multiset<int> origEmptySet;
  myEmptySet.clear();
  origEmptySet.clear();
  EXPECT_EQ(myEmptySet.empty(), origEmptySet.empty());
  EXPECT_EQ(myEmptySet.size(), origEmptySet.size());
  myEmptySet.insert('a');
  origEmptySet.insert('b');
  EXPECT_EQ(myEmptySet.empty(), origEmptySet.empty());
  EXPECT_EQ(myEmptySet.size(), origEmptySet.size());
  myEmptySet.clear();
  origEmptySet.clear();
  EXPECT_EQ(myEmptySet.empty(), origEmptySet.empty());
  EXPECT_EQ(myEmptySet.size(), origEmptySet.size());
}

TEST(multiset, InsertSet) {
  s21::multiset<int> mySet({1, 1, 1, 2, 3, 3, 4, 5, 5});
  std::multiset<int> origSet({1, 1, 1, 2, 3, 3, 4, 5, 5});
  auto myIt = mySet.insert(6);
  auto origIt = origSet.insert(6);
  EXPECT_TRUE(*myIt == *origIt);
  myIt = mySet.insert(7);
  origIt = origSet.insert(7);
  EXPECT_TRUE(*myIt == *origIt);
}

TEST(multiset, EraseSet) {
  s21::multiset<int> mySet({5, 5, 4, 4, 4, 3, 2, 2, 7, 7, 7, 8, 9, 9});
  std::multiset<int> origSet({5, 5, 4, 4, 4, 3, 2, 2, 7, 7, 7, 8, 9, 9});
  auto size = mySet.size();
  mySet.erase(mySet.end());
  auto new_size = mySet.size();
  EXPECT_EQ(size, new_size);
  auto myIt = mySet.begin();
  auto origIt = origSet.begin();
  for (size_t i = 0; i < 4; ++i, ++myIt, ++origIt)
    ;
  mySet.erase(myIt);
  origSet.erase(origIt);
  EXPECT_EQ(mySet.size(), origSet.size());
  myIt = mySet.begin();
  origIt = origSet.begin();
  for (size_t i = 0, n = origSet.size(); i < n; ++i, ++myIt, ++origIt) {
    EXPECT_TRUE(*origIt == *myIt);
  }
}

TEST(multiset, SwapSet) {
  s21::multiset<int> mySet({1, 1, 1});
  s21::multiset<int> mySwapSet({3, 3, 3, 4, 4, 5});

  mySet.swap(mySwapSet);
  EXPECT_EQ(mySet.size(), 6);
  EXPECT_EQ(mySwapSet.size(), 3);
  auto mySetIt = mySet.begin();
  auto mySwapSet_it = mySwapSet.begin();
  EXPECT_EQ(*mySetIt, 3);
  EXPECT_EQ(*mySwapSet_it, 1);
}

TEST(multiset, MergeSet) {
  s21::multiset<int> mySet({1, 1, 1});
  s21::multiset<int> myMergeSet({3, 3, 3, 4, 4, 5});
  mySet.merge(myMergeSet);

  std::multiset<int> origSet({1, 1, 1});
  std::multiset<int> origMergeSet({3, 3, 3, 4, 4, 5});
  origSet.merge(origMergeSet);

  auto myIt = mySet.begin();
  auto origIt = origSet.begin();
  EXPECT_EQ(myMergeSet.size(), origMergeSet.size());
  ASSERT_EQ(origSet.size(), mySet.size());
  for (size_t i = 0, n = origSet.size(); i < n; ++i, ++myIt, ++origIt)
    EXPECT_TRUE(*origIt == *myIt);
}

TEST(multiset, FindSet) {
  s21::multiset<int> mySet({1, 1, 1, 2, 3, 3, 4, 5, 5});
  std::multiset<int> origSet({1, 1, 1, 2, 3, 3, 4, 5, 5});
  auto myIt = mySet.find(4);
  auto origIt = origSet.find(4);
  EXPECT_TRUE(*origIt == *myIt);
}

TEST(multiset, ContainsSet) {
  s21::multiset<int> mySet({1, 1, 1, 2, 3, 3, 4, 5, 5});
  EXPECT_FALSE(mySet.contains(8));
  EXPECT_TRUE(mySet.contains(2));
}

TEST(multiset, Find) {
  s21::multiset<int> s1({1, 1, 1, 2, 3, 3, 4, 5, 5});
  auto itEnd = s1.end();
  auto itAns = s1.begin();
  for (size_t i = 0; i < 4; ++i, ++itAns)
    ;
  auto it1 = s1.find(3);
  EXPECT_FALSE(it1 == itEnd);
  EXPECT_TRUE(it1 == itAns);
  it1 = s1.find(6);
  EXPECT_TRUE(it1 == itEnd);
}

TEST(multiset, ConstFind) {
  const s21::multiset<int> s1({1, 1, 1, 2, 3, 3, 4, 5, 5});
  auto itEnd = s1.end();
  auto itAns = s1.begin();
  for (size_t i = 0; i < 4; ++i, ++itAns)
    ;
  auto it1 = s1.find(3);
  EXPECT_FALSE(it1 == itEnd);
  EXPECT_TRUE(it1 == itAns);
  it1 = s1.find(6);
  EXPECT_TRUE(it1 == itEnd);
}

TEST(multiset, Count) {
  s21::multiset<int> mySet({1, 1, 1, 2, 3, 3, 4, 5, 5});
  std::multiset<int> origSet({1, 1, 1, 2, 3, 3, 4, 5, 5});
  EXPECT_EQ(mySet.count(1), origSet.count(1));
  EXPECT_EQ(mySet.count(2), origSet.count(2));
  EXPECT_EQ(mySet.count(3), origSet.count(3));
  EXPECT_EQ(mySet.count(4), origSet.count(4));
  EXPECT_EQ(mySet.count(5), origSet.count(5));
  EXPECT_EQ(mySet.count(8), origSet.count(8));
}

TEST(multiset, EqualRange_1) {
  const s21::multiset<int> ms1({1, 1, 1, 2, 3, 3, 4, 5, 5});
  auto range1 = ms1.equal_range(3);
  auto itAns1 = ms1.begin();
  for (size_t i = 0; i < 4; ++i, ++itAns1)
    ;
  auto itAns2 = ms1.begin();
  for (size_t i = 0; i < 6; ++i, ++itAns2)
    ;
  EXPECT_TRUE(range1.first == itAns1);
  EXPECT_TRUE(range1.second == itAns2);
}

TEST(multiset, EqualRange_2) {
  s21::multiset<int> ms1({1, 1, 1, 2, 3, 3, 4, 5, 5});
  auto range1 = ms1.equal_range(5);
  auto itAns1 = ms1.begin();
  for (size_t i = 0; i < 7; ++i, ++itAns1)
    ;
  EXPECT_TRUE(range1.first == itAns1);
  EXPECT_TRUE(range1.second == ms1.end());
}

TEST(multiset, EqualRange_3) {
  const s21::multiset<int> ms1({1, 1, 1, 2, 3, 3, 4, 5, 5});
  auto range1 = ms1.equal_range(1);
  auto itAns2 = ms1.begin();
  for (size_t i = 0; i < 3; ++i, ++itAns2)
    ;
  EXPECT_TRUE(range1.first == ms1.begin());
  EXPECT_TRUE(range1.second == itAns2);
}

TEST(multiset, LowerBound_1) {
  const s21::multiset<int> ms1({1, 1, 1, 2, 3, 3, 4, 5, 5});
  auto itRes = ms1.lower_bound(3);
  auto itAns = ms1.begin();
  for (size_t i = 0; i < 4; ++i, ++itAns)
    ;
  EXPECT_TRUE(itRes == itAns);
}

TEST(multiset, LowerBound_2) {
  s21::multiset<int> ms1({1, 1, 1, 2, 3, 3, 4, 5, 5});
  auto itRes = ms1.lower_bound(1);
  auto itAns = ms1.begin();
  EXPECT_TRUE(itRes == itAns);
}

TEST(multiset, UpperBound_1) {
  const s21::multiset<int> ms1({1, 1, 1, 2, 3, 3, 4, 5, 5});
  auto itRes = ms1.upper_bound(3);
  auto itAns = ms1.begin();
  for (size_t i = 0; i < 6; ++i, ++itAns)
    ;
  EXPECT_TRUE(itRes == itAns);
}

TEST(multiset, UpperBound_2) {
  s21::multiset<int> ms1({1, 1, 1, 2, 3, 3, 4, 5, 5});
  auto itRes = ms1.upper_bound(1);
  auto itAns = ms1.begin();
  for (size_t i = 0; i < 3; ++i, ++itAns)
    ;
  EXPECT_TRUE(itRes == itAns);
}

TEST(multiset, UpperBound_3) {
  s21::multiset<int> ms1({1, 1, 1, 2, 3, 3, 4, 5, 5});
  auto itRes = ms1.upper_bound(5);
  auto itAns = ms1.end();
  EXPECT_TRUE(itRes == itAns);
}

TEST(multiset, MaxSize) {
  s21::multiset<int> ms1({1, 1, 1, 2, 3, 3, 4, 5, 5});
  s21::multiset<int> ms2({1, 1, 1, 2, 3, 3, 4, 5, 5});
  EXPECT_EQ(ms1.max_size(), ms2.max_size());
}
