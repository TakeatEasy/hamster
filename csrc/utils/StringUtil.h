#pragma once

#include "Macros.h"

#include <cstddef>
#include <ostream>
#include <sstream>
#include <string>
#include <vector>

namespace hamster {

// Obtains the base name from a full path.
std::string StripBasename(const std::string& full_path);

inline std::ostream& _str(std::ostream& ss) {
  return ss;
}

template<typename T>
inline std::ostream& _str(std::ostream& ss, const T& t) {
    ss << t;
    return ss;
}

template<typename T, typename... Args>
inline std::ostream& _str(std::ostream& ss, const T& t, const Args&... args) {
    return _str(_str(ss, t), args...);
}

// Convert a list of string-like arguments into a single string.
template <typename... Args>
inline std::string str(const Args&... args) {
  std::ostringstream ss;
  _str(ss, args...);
  return ss.str();
}

// Specializations for already-a-string types.
template <>
inline std::string str(const std::string& str) {
  return str;
}
inline std::string str(const char* c_str) {
  return c_str;
}

template <class Container>
inline std::string Join(const std::string& delimiter, const Container& v) {
  std::stringstream s;
  int cnt = static_cast<int64_t>(v.size()) - 1;
  for (auto i = v.begin(); i != v.end(); ++i, --cnt) {
    s << (*i) << (cnt ? delimiter : "");
  }
  return s.str();
}

// Replace all occurrences of "from" substring to "to" string.
// Returns number of replacements
size_t ReplaceAll(std::string& s, const char* from, const char* to);

/// Represents a location in source code (for debugging).
struct SourceLocation {
  const char* function;
  const char* file;
  uint32_t line;
};

std::ostream& operator<<(std::ostream& out, const SourceLocation& loc);

} // namespace hamster