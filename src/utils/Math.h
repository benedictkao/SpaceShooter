#pragma once

template <typename T>
constexpr const T& max(const T& a, const T& b) {
  return a > b ? a : b;
}

template <typename T>
constexpr const T& min(const T& a, const T& b) {
  return a < b ? a : b;
}

template <typename T>
constexpr void coerceAtLeast(T& value, const T& min) {
  value = value > min ? value : min;
}

template <typename T>
constexpr void coerceAtMost(T& value, const T& max) {
  value = value < max ? value : max;
}

template <typename T>
constexpr void coercePositive(T& value) noexcept {
  coerceAtLeast(value, static_cast<T>(0));
}

template <typename T>
constexpr void coerceNegative(T& value) noexcept {
  coerceAtMost(value, static_cast<T>(0));
}

template <typename T>
constexpr void coerceBetween(T& value, const T& min, const T& max) noexcept {
  if (value < min)
    value = min;
  else if (value > max)
    value = max;
}