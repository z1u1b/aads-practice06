#include "top-it-vector.hpp"
#include <initializer_list>
#include <iomanip>
#include <iostream>
bool testEmptyVector()
{
  topit::Vector< int > v;
  return v.isEmpty();
}
bool testElementInboundAccess()
{
  topit::Vector< int > v;
  v.pushBack(1);
  try {
    int& val = v.at(0);
    return val == 1;
  } catch (...) {
    return false;
  }
}
bool testElementOutOfBoundAccess()
{
  topit::Vector< int > v;
  try {
    v.at(0);
    return false;
  } catch (std::out_of_range&) {
    return true;
  } catch (...) {
    return false;
  }
}

bool testElementInboundConstAccess()
{
  topit::Vector< int > v;
  v.pushBack(1);
  const topit::Vector< int >& rv = v;
  try {
    const int& val = rv.at(0);
    return val == 1;
  } catch (...) {
    return false;
  }
}
bool testElementOutOfBoundConstAccess()
{
  const topit::Vector< int > v;
  try {
    v.at(0);
    return false;
  } catch (std::out_of_range&) {
    return true;
  } catch (...) {
    return false;
  }
}
bool testPushback()
{
  topit::Vector< int > v;
  v.pushBack(1);
  v.pushBack(2);
  return v[0] == 1 && v[1] == 2;
}
bool testPopBack()
{
  topit::Vector< int > v;
  v.pushBack(1);
  v.pushBack(2);
  v.popBack();
  return v[0] == 1 && v.getSize() == 1 && v.getCapacity() >= 1;
}
bool testCopyConstructorForEmpty()
{
  topit::Vector< int > v;
  topit::Vector< int > yav = v;
  return v == yav;
}
bool testCopyConstructorForNonEmpty()
{
  topit::Vector< int > v;
  v.pushBack(1);
  topit::Vector< int > yav = v;
  try {
    return yav.at(0) == v.at(0) && yav.getSize() == v.getSize();
  } catch (...) {
    return false;
  }
}

bool testInitializerList()
{
  topit::Vector< int > v{1, 2};
  return v.getSize() == 2 && (v[0] == 1) && (v[1] == 2);
}
bool reserveTest()
{
  topit::Vector< int > vec1{0, 1, 2, 3};
  vec1.reserve(7);
  return vec1.getCapacity() == 7;
}
bool shrinkTest()
{
  topit::Vector< int > vec1{0, 1, 2, 3};
  vec1.reserve(7);
  vec1.shrinkToFit();
  return vec1.getCapacity() == 4 && vec1[3] == 3;
}
bool reserveFailTest()
{
  topit::Vector< int > vec;
  try {
    vec.reserve(std::numeric_limits< size_t >::max());
    return false;
  } catch (const std::bad_alloc&) {
    return true;
  } catch (...) {
    return false;
  }
}
bool shrinkFailTest()
{
  topit::Vector< int > v;
  v.shrinkToFit();
  return v.isEmpty() && v.getCapacity() == 0;
}

bool beginTest()
{
  topit::Vector< int > v{0, 1, 2, 3};
  return *v.begin() == 0;
}
bool endTest()
{
  topit::Vector< int > v{0, 1, 2, 3};
  auto it = v.end();
  --it;
  return *it== 3;
}
bool iteratorTraversalTest()
{
  topit::Vector< int > v{1, 2, 3, 4, 5};
  int sum = 0;
  for (auto it = v.begin(); it != v.end(); ++it) {
    sum += *it;
  }
  return sum == 15;
}
bool constIteratorTest()
{
  const topit::Vector< int > v{100, 200};
  auto it = v.cbegin();
  return *it == 100;
}
bool iteratorArithmeticTest()
{
  topit::Vector< int > v{1, 2, 3, 4, 5};
  auto it = v.begin();
  it = it + 2;

  return *it == 3;
}
bool iteratorComparisonTest()
{
  topit::Vector< int > v{1, 2, 3, 4, 5};
  auto it1 = v.begin();
  auto it2 = v.begin() + 1;

  return it1 != it2;
}

bool pushBackCountTest()
{
  topit::Vector< int > v{1, 2, 3};
  v.pushBackCount(2, 5);
  return v.getSize() == 5 && v[v.getSize() - 1] == 5 && v[v.getSize() - 2] == 5 && v[v.getSize() - 3] == 3;
}
bool pushBackRangeTest()
{
  topit::Vector< int > v{1, 2, 3};
  topit::Vector< int > vLoad{4, 5, 6};
  auto it = vLoad.begin();
  v.pushBackRange(it, vLoad.getSize());
  if (v.getSize() != 6) return false;
  for (size_t i = 0; i < 3; ++i) {
    if (v[i] != static_cast<int>(i) + 1) return false;
  }
  for (size_t i = 3; i < 6; ++i) {
    if (v[i] != static_cast<int>(i) + 1) return false;
  }
  return true;
}
bool unsafePushBackTest()
{
  topit::Vector< int > v;
  v.reserve(3);
  v.unsafePushBack(1);
  v.unsafePushBack(2);
  v.unsafePushBack(3);
  return v.getSize() == 3 && v[0] == 1 && v[2] == 3;
}
bool pushBackGrowTest()
{
  topit::Vector< int > v;
  for (int i = 0; i < 100; ++i) {
    v.pushBack(i);
  }
  if (v.getSize() != 100) return false;
  if (v.getCapacity() < 100) return false;
  for (int i = 0; i < 100; ++i) {
    if (v[i] != i) return false;
  }
  return true;
}
bool pushBackEmptyTest()
{
  topit::Vector< int > v;
  v.pushBack(43);
  return v.getCapacity() >= 1 && v.getSize() == 1 && v[0] == 43;
}

bool insertElTest()
{
  topit::Vector< int > v{1, 2, 4};
  v.insert(2, 3);
  bool flag = true;
  for (size_t i = 0; i < v.getSize(); ++i) {
    flag = flag && (v[i] == static_cast<int>(i) + 1);
  }
  return flag;
}
bool insertAtBeginTest()
{
  topit::Vector< int > v{0, 1, 2, 3, 4};
  v.insert(v.cbegin(), 2);
  return v.getSize() == 6 && v[0] == 2 && v[1] == 0;
}
bool insertAtEndTest()
{
  topit::Vector< int > v{0, 1, 2, 3, 4};
  v.insert(v.cend(), 5);
  return v.getSize() == 6 && v[v.getSize() - 1] == 5;
}
bool insertRangeTest()
{
  topit::Vector< int > v{0, 1, 2, 3, 4};
  topit::Vector< int > vLoad{5, 6, 7, 8};
  v.insert(v.getSize(), vLoad, 0, 1);
  return v.getSize() == 6 && v[v.getSize() - 1] == 5;
}
bool insertEmptyVectorTest()
{
  topit::Vector< int > v;
  v.insert(0, 2);
  return v.getSize() == 1 && v[0] == 2;
}
bool insertLargeCountTest()
{
  topit::Vector< int > v{1, 2, 3};
  const size_t count = 1000;
  const int value = 42;
  auto it = v.insert(v.cbegin() + 1, count, value);
  if (it != v.begin() + 1) return false;
  if (v.getSize() != 3 + count) return false;
  if (v[0] != 1) return false;
  for (size_t i = 1; i <= count; ++i) {
    if (v[i] != value) return false;
  }
  if (v[count + 1] != 2) return false;
  if (v[count + 2] != 3) return false;
  if (v.getCapacity() < v.getSize()) return false;
  return true;
}

bool eraseIterTest()
{
  topit::Vector< int > v{0, 1, 2, 3, 4};
  auto it = v.cbegin();
  v.erase(it);
  return v.getSize() == 4 && v[0] == 1;
}
bool eraseIterCountTest()
{
  topit::Vector< int > v{0, 1, 2, 3, 4};
  auto it = v.cbegin();
  v.erase(it, 2);
  return v.getSize() == 3 && v[0] == 2;
}
bool eraseIterRangeTest()
{
  topit::Vector< int > v{0, 1, 2, 3, 4};
  auto it1 = v.cbegin() + 1;
  auto it2 = v.cbegin() + 3;
  v.erase(it1, it2);
  return v.getSize() == 3 && v[0] == 0 && v[2] == 4;
}
bool eraseIterBeginEndTest()
{
  topit::Vector< int > v{0, 1, 2, 3, 4};

  v.erase(v.cbegin(), v.cend());
  return v.getSize() == 0;
}

bool testMoveConstructor()
{
  topit::Vector< int > v{0, 1, 2, 3, 4};
  topit::Vector< int > vMove(std::move(v));
  return v.getSize() == 0 && v.getCapacity() == 0 && vMove[0] == 0 && vMove.getSize() == 5;
}
bool testMoveAssignment()
{
  topit::Vector< int > v{0, 1, 2, 3, 4};
  topit::Vector< int > vMove;
  vMove = std::move(v);
  return v.getSize() == 0 && v.getCapacity() == 0 && vMove[0] == 0 && vMove.getSize() == 5;
}
bool testSelfAssignment()
{
  topit::Vector< int > v{0, 1, 2, 3, 4};
  v = v;
  return v.getSize() == 5;
}
bool testCopyAssignment()
{
  topit::Vector< int > v{0, 1, 2, 3, 4};
  topit::Vector< int > vCopy;
  vCopy = v;
  return v == vCopy;
}

bool testSwap()
{
  topit::Vector< int > v1{0, 1};
  topit::Vector< int > v2{2};
  v1.swap(v2);
  return v1.getSize() == 1 && v1[0] == 2 && v2.getSize() == 2 && v2[0] == 0;
}
bool testSwapEmpty()
{
  topit::Vector< int > v1;
  topit::Vector< int > v2{2};
  v1.swap(v2);
  return v1.getSize() == 1 && v1[0] == 2 && v2.getSize() == 0;
}
bool testSwapWithSelf()
{
  topit::Vector< int > v1;
  v1.swap(v1);
  return v1.getSize() == 0 && v1.getCapacity() == 0;
}

int main()
{
  using test_t = std::pair< const char*, bool (*)() >;
  test_t tests[] = {{"Empty vector", testEmptyVector},
                    {"Inbound access", testElementInboundAccess},
                    {"Out of bound access", testElementOutOfBoundAccess},
                    {"Const inbound access", testElementInboundConstAccess},
                    {"Const out of bound access", testElementOutOfBoundConstAccess},
                    {"Push back", testPushback},
                    {"Pop back", testPopBack},
                    {"Copy constructor for empty", testCopyConstructorForEmpty},
                    {"Copy constructor for non-empty", testCopyConstructorForNonEmpty},
                    {"Initializer list", testInitializerList},
                    {"Reserve", reserveTest},
                    {"Shrink to fit", shrinkTest},
                    {"Reserve fail", reserveFailTest},
                    {"Shrink fail", shrinkFailTest},
                    {"Begin", beginTest},
                    {"End", endTest},
                    {"Iterator traversal", iteratorTraversalTest},
                    {"Const iterator", constIteratorTest},
                    {"Iterator arithmetic", iteratorArithmeticTest},
                    {"Iterator comparison", iteratorComparisonTest},
                    {"Push back count", pushBackCountTest},
                    {"Push back range", pushBackRangeTest},
                    {"Unsafe push back", unsafePushBackTest},
                    {"Push back grow", pushBackGrowTest},
                    {"Push back empty", pushBackEmptyTest},
                    {"Insert element", insertElTest},
                    {"Insert at begin", insertAtBeginTest},
                    {"Insert at end", insertAtEndTest},
                    {"Insert range", insertRangeTest},
                    {"Insert empty vector", insertEmptyVectorTest},
                    {"Insert large count", insertLargeCountTest},
                    {"Erase iter", eraseIterTest},
                    {"Erase iter count", eraseIterCountTest},
                    {"Erase iter range", eraseIterRangeTest},
                    {"Erase iter begin end", eraseIterBeginEndTest},
                    {"Move constructor", testMoveConstructor},
                    {"Move assignment", testMoveAssignment},
                    {"Self assignment", testSelfAssignment},
                    {"Copy assignment", testCopyAssignment},
                    {"Swap", testSwap},
                    {"Swap empty", testSwapEmpty},
                    {"Swap with self", testSwapWithSelf}};

  const size_t countTests = sizeof(tests) / sizeof(test_t);
  std::cout << std::boolalpha;
  bool pass = true;
  size_t trueTests = 0;
  for (size_t i = 0; i < countTests; ++i) {
    bool res = tests[i].second();
    if (!res) {
      std::cout << "❌ " << tests[i].first << ": " << res << "\n";
    } else {
      trueTests++;
    }

    pass = pass && res;
  }

std::cout << "RESULT: " << pass << (pass ? " ✅" : " ❌") << '\n';
  std::cout << "Пройдено тестов: " << trueTests << "/" << countTests << '\n';
}
