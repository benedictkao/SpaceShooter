#pragma once

typedef unsigned long long _uint64;

static inline _uint64 maxUnsigned(_uint64 a, _uint64 b) noexcept {
  return a > b ? a : b;
}

static inline _uint64 minUnsigned(_uint64 a, _uint64 b) noexcept {
  return a < b ? a : b;
}

static inline int max(int a, int b) noexcept { return a > b ? a : b; }

static inline int min(int a, int b) noexcept { return a < b ? a : b; }