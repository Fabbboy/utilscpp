#ifndef UCPP_RESULT_HPP
#define UCPP_RESULT_HPP

#include <stdexcept>
#include <utility>

namespace ucpp {
struct ValueTag {};
struct ErrorTag {};

template <typename T, typename E> class Result {
private:
  union {
    T value;
    E error;
  };
  bool hasValue;

public:
  Result(ValueTag, T v) : value(std::move(v)), hasValue(true) {}
  Result(ErrorTag, E e) : error(std::move(e)), hasValue(false) {}
  ~Result() {
    if (hasValue) {
      value.~T();
    } else {
      error.~E();
    }
  }

  static Result Ok(T v) { return Result(ValueTag{}, std::move(v)); }
  static Result Err(E e) { return Result(ErrorTag{}, std::move(e)); }

  bool is_ok() const { return hasValue; }
  bool is_err() const { return !hasValue; }

  T unwrap() const {
    if (hasValue)
      return value;
    throw std::runtime_error("No value present");
  }

  E unwrap_err() const {
    if (!hasValue)
      return error;
    throw std::runtime_error("No error present");
  }
};

} // namespace ucpp

#endif // UCPP_RESULT_HPP
