#ifndef __COMMONC_MEMORY_HH__
#define __COMMONC_MEMORY_HH__

#include "../macro.hh"

#if IS_CPP
#include <memory>
namespace commonc {
template <typename T>
using Box = std::unique_ptr<T>;
template <typename T>
using Ref = std::shared_ptr<T>;
template <typename T>
using Raw = T*;

template <typename T>
constexpr Box<std::remove_reference_t<T>> make_box(T&& value) {
  return std::make_unique<std::remove_reference_t<T>>(std::forward<T>(value));
}
template <typename T, typename... Args>
constexpr Box<T> make_box(Args&&... args) {
  return std::make_unique<T>(std::forward<Args>(args)...);
}

template <typename T, typename... Args>
constexpr Ref<T> make_ref(Args&&... args) {
  return std::make_shared<T>(std::forward<Args>(args)...);
}
}  // namespace commonc
#endif

#endif