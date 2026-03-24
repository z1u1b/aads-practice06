#include "top-it-vector.hpp"
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
int main()
{
  using test_t = std::pair< const char*, bool (*)() >;
  test_t tests[] = {{"Empty vector", testEmptyVector},
                    {"Inbound access", testElementInboundAccess},
                    {"Out of bound access", testElementOutOfBoundAccess},
                    {"Inbound access", testElementInboundConstAccess},
                    {"Out of bound access", testElementOutOfBoundConstAccess}};
  const size_t count = sizeof(tests) / sizeof(test_t);
  std::cout << std::boolalpha;
  bool pass = true;
  for (size_t i = 0; i < count; ++i) {
    bool res = tests[i].second();
    std::cout << tests[i].first << ": " << res << "\n";
    pass = pass && res;
  }

  std::cout << "RESULT: " << pass << '\n';
  // подсчет пройденных тестов
  // вывод только не пройденных тестов
  // std::cout<<__func__<<'\n'
}
