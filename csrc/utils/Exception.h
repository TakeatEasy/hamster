#pragma once

#include <cstddef>
#include <exception>
#include <ostream>
#include <sstream>
#include <string>
#include <vector>

#include "StringUtil.h"

namespace hamster {

/// The primary ATen error class.
/// Provides a complete error message with source location information via
/// `what()`, and a more concise message via `what_without_backtrace()`. Should
/// primarily be used with the `AT_ERROR` macro.
///
/// NB: c10::Error is handled specially by the default torch to suppress the
/// backtrace, see torch/csrc/Exceptions.h
class Error: public std::exception {
    std::vector<std::string> msg_stack_;
    std::string backtrace_;

  // These two are derived fields from msg_stack_ and backtrace_, but we need
  // fields for the strings so that we can return a const char* (as the
  // signature of std::exception requires).
  std::string msg_;
  std::string msg_without_backtrace_;

    // This is a little debugging trick: you can stash a relevant pointer
  // in caller, and then when you catch the exception, you can compare
  // against pointers you have on hand to get more information about
  // where the exception came from.  In Caffe2, this is used to figure
  // out which operator raised an exception.
  const void* caller_;

  public:
  Error(
      const std::string& msg,
      const std::string& backtrace,
      const void* caller = nullptr);
  Error(SourceLocation source_location, const std::string& msg);
  Error(
      const char* file,
      const int line,
      const char* condition,
      const std::string& msg,
      const std::string& backtrace,
      const void* caller = nullptr);

  void AppendMessage(const std::string& msg);

  // Compute the full message from msg_ and msg_without_backtrace_
  // TODO: Maybe this should be private
  std::string msg() const;
  std::string msg_without_backtrace() const;

  const std::vector<std::string>& msg_stack() const {
    return msg_stack_;
  }

  /// Returns the complete error message, including the source location.
  const char* what() const noexcept override {
    return msg_.c_str();
  }

  const void* caller() const noexcept {
    return caller_;
  }

  /// Returns only the error message string, without source location.
  const char* what_without_backtrace() const noexcept {
    return msg_without_backtrace_.c_str();
  }
};

class Warning {
using handler_t =
      void (*)(const SourceLocation& source_location, const char* msg);

 public:
  /// Issue a warning with a given message. Dispatched to the current
  /// warning handler.
  static void warn(SourceLocation source_location, std::string msg);
  /// Sets the global warning handler. This is not thread-safe, so it should
  /// generally be called once during initialization.
  static void set_warning_handler(handler_t handler);
  /// The default warning handler. Prints the message to stderr.
  static void print_warning(
      const SourceLocation& source_location,
      const char* msg);

 private:
  static handler_t warning_handler_;
};

} // namespace hamster


#define AT_ERROR(...) \
  throw hamster::Error({__func__, __FILE__, __LINE__}, hamster::str(__VA_ARGS__))

#define AT_WARN(...) \
  hamster::Warning::warn({__func__, __FILE__, __LINE__}, hamster::str(__VA_ARGS__))

#define AT_ASSERT(cond)                       \
  if (!(cond)) {                              \
    AT_ERROR(                                 \
        #cond " ASSERT FAILED at ",           \
        __FILE__,                             \
        ":",                                  \
        __LINE__,                             \
        ", please report a bug to PyTorch."); \
  }

#define AT_ASSERTM(cond, ...)                 \
  if (!(cond)) {                              \
    AT_ERROR(hamster::str(                      \
        #cond,                                \
        " ASSERT FAILED at ",                 \
        __FILE__,                             \
        ":",                                  \
        __LINE__,                             \
        ", please report a bug to PyTorch. ", \
        __VA_ARGS__));                        \
  }

#define AT_CHECK(cond, ...)            \
  if (!(cond)) {                       \
    AT_ERROR(hamster::str(__VA_ARGS__)); \
  }