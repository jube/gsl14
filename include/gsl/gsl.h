#ifndef GSL14_GSL_H
#define GSL14_GSL_H

#include <array>
#include <exception>
#include <memory>
#include <type_traits>
#include <utility>
#include <vector>

namespace gsl {

  // GSL.assert

  inline
  void Expects(bool predicate) {
    if (!predicate) {
      throw std::logic_error("Precondition violation");
    }
  }

  inline
  void Ensures(bool predicate) {
    if (!predicate) {
      throw std::logic_error("Postcondition violation");
    }
  }

  // GSL.view

  template<typename T, class = std::enable_if_t<std::is_pointer<T>::value>>
  using owner = T;


  template<typename T>
  class not_null {
  public:
    static_assert(std::is_assignable<T&, std::nullptr_t>::value, "T is not a pointer like type");
    static_assert(!std::is_same<T, std::nullptr_t>::value, "T is nullptr_t");

    template <typename U, typename = std::enable_if_t<std::is_convertible<U, T>::value>>
    constexpr explicit not_null(U&& u)
    : m_ptr(std::forward<U>(u))
    {
      Expects(m_ptr != nullptr);
    }

    template <typename U, typename = std::enable_if_t<std::is_convertible<U, T>::value>>
    constexpr not_null(const not_null<U>& other)
    : not_null(other.get())
    {

    }

    not_null(const not_null& other) = default;
    not_null& operator=(const not_null& other) = default;

    not_null(not_null&& other) = default;
    not_null& operator=(not_null&& other) = default;

    constexpr T get() const {
        Ensures(m_ptr != nullptr);
        return m_ptr;
    }

    constexpr operator T() const { return get(); }
    constexpr T operator->() const { return get(); }
    constexpr decltype(auto) operator*() const { return *get(); }

    not_null(std::nullptr_t) = delete;
    not_null& operator=(std::nullptr_t) = delete;

    not_null& operator++() = delete;
    not_null& operator--() = delete;
    not_null operator++(int) = delete;
    not_null operator--(int) = delete;
    not_null& operator+=(std::ptrdiff_t) = delete;
    not_null& operator-=(std::ptrdiff_t) = delete;
    void operator[](std::size_t) const = delete;

  private:
    T m_ptr;
  };

  using zstring = char*;
  using czstring = const char*;


  // GSL.owner

  using std::unique_ptr;
  using std::shared_ptr;

  template<typename T, std::size_t N>
  using stack_array = std::array<T, N>;

  template<typename T>
  using dyn_array = std::vector<T>;


  // GSL.util

  template<typename Func>
  class final_action {
  public:
    explicit
    final_action(Func func) noexcept
    : m_func(std::move(func))
    , m_invoke(true)
    {

    }

    ~final_action() {
      if (m_invoke) {
        m_func();
      }
    }

    final_action(const final_action&) = delete;
    final_action& operator=(const final_action&) = delete;

    final_action(final_action&& other)
    : m_func(std::move(other.m_func))
    , m_invoke(std::exchange(other.m_invoke, false))
    {

    }

    final_action& operator=(final_action&& other) = delete;

  private:
    Func m_func;
    bool m_invoke;
  };

  template<typename Func>
  inline
  final_action<Func> finally(const Func& f) noexcept {
    return final_action<Func>(f);
  }

  template<typename Func>
  inline
  final_action<Func> finally(Func&& f) noexcept {
    return final_action<Func>(std::forward<Func>(f));
  }


  struct narrowing_error : public std::exception {
  };

  template<typename Out, typename In>
  inline
  Out narrow_cast(In&& x) {
    return static_cast<Out>(std::forward<In>(x));
  }

  template<typename Out, typename In>
  inline
  Out narrow(In x) {
    Out y = narrow_cast<Out>(x);

    if (static_cast<In>(y) != x) {
      throw narrowing_error();
    }

    if (std::is_signed<In>::value != std::is_signed<Out>::value) {
      if ((x < In()) != (y < Out())) {
        throw narrowing_error();
      }
    }

    return y;
  }


}

#endif // GSL14_GSL_H
