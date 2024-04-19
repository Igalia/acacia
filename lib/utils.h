#pragma once

#include <algorithm>
#include <string>
#include <vector>

inline std::string lower(const std::string& str) {
  std::string result(str);
  std::transform(result.begin(), result.end(), result.begin(),
                 [](unsigned char c) { return std::tolower(c); });
  return result;
}

inline std::string StringVectorToString(std::vector<std::string> strings) {
  std::sort(strings.begin(), strings.end());
  std::string result;
  for (auto string : strings)
    result += string + ", ";
  size_t pos = result.find_last_not_of(", ");
  if (pos != std::string::npos)
    result = result.substr(0, pos + 1);
  return result;
}
