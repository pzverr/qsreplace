#ifndef PRINT_H
#define PRINT_H

#include <ostream>
#include <sstream>
#include <utility>
#include <vector>
#include <map>
#include <set>

template <typename First, typename Second>
std::ostream& operator<<(std::ostream& out, const std::pair<First, Second>& p);

template <typename T>
std::ostream& operator<<(std::ostream& out, const std::vector<T>& v);

template <typename T>
std::ostream& operator<<(std::ostream& out, const std::set<T>& s);

template <typename Key, typename Value>
std::ostream& operator<<(std::ostream& out, const std::map<Key, Value>& m);

template <typename Collection> std::string Join(const Collection& c, char d) {
  std::stringstream ss;

  bool first = true;

  for (const auto& i : c) {
    if (!first) {
      ss << d;
    }
    first = false;
    ss << i;
  }

  return ss.str();
}

template <typename First, typename Second>
std::ostream& operator<<(std::ostream& out, const std::pair<First, Second>& p) {
  return out << '(' << p.first << ',' << p.second << ')';
}

template <typename T>
std::ostream& operator<<(std::ostream& out, const std::vector<T>& v) {
  return out << '[' << Join(v, ',') << ']';
}

template <typename T>
std::ostream& operator<<(std::ostream& out, const std::set<T>& s) {
  return out << '{' << Join(s, ',') << '}';
}

template <typename Key, typename Value>
std::ostream& operator<<(std::ostream& out, const std::map<Key, Value>& m) {
  return out << '{' << Join(m, ',') << '}';
}

#endif
