#include <string>
#include <iostream>

#include "url.h"

template <typename ForwardIt, typename T>
void replace(ForwardIt first, ForwardIt last, const T& new_value) {
  for (; first != last; ++first) {
    *first = new_value;
  }
}

int main(int argc, char* argv[]) {
  std::string line;

  while (getline(std::cin, line)) {
    if (line.empty())
      continue;

    url u(line);

    for (auto& [key, value] : u.query) {
      replace(value.begin(), value.end(), argv[1]);
    }

    std::cout << u << "\n";
  }

  return 0;
}
