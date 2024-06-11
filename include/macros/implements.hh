#ifndef UCPP_DISPLAY_HPP
#define UCPP_DISPLAY_HPP

namespace ucpp {
#define UCPP_IMPLEMENTS(method)                                                \
  template <typename C> struct has_##method {                                  \
  private:                                                                     \
    template <typename T>                                                      \
    static constexpr auto check(T *) -> decltype(std::declval<T>().method(),   \
                                                 std::true_type());            \
    template <typename> static constexpr std::false_type check(...);           \
    typedef decltype(check<C>(0)) type;                                        \
                                                                               \
  public:                                                                      \
    static constexpr bool value = type::value;                                 \
  };

} // namespace ucpp

#endif