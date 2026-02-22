#pragma once

#include <cmath>

#if defined(__x86_64__) || defined(_M_X64) || defined(__i386__) || defined(_M_IX86)
#include <immintrin.h>
#endif

namespace dnb::dsp::core {

// Scoped RAII class to enforce Flush-To-Zero (FTZ) and Denormals-Are-Zero (DAZ)
// Critical for RT-safe DSP loops to prevent CPU spikes from subnormal numbers.
class ScopedDenormalFlush {
public:
  ScopedDenormalFlush() {
#if defined(__x86_64__) || defined(_M_X64) || defined(__i386__) || defined(_M_IX86)
    originalMxcsr = _mm_getcsr();
    // Set FZ (bit 15) and DAZ (bit 6)
    _mm_setcsr(originalMxcsr | 0x8040);
#endif
  }

  ~ScopedDenormalFlush() {
#if defined(__x86_64__) || defined(_M_X64) || defined(__i386__) || defined(_M_IX86)
    _mm_setcsr(originalMxcsr);
#endif
  }

  // Explicit flush for individual scalar values (if needed outside scoped
  // loops)
  static inline void flush(float &value) {
    if (std::abs(value) < 1e-15f) {
      value = 0.0f;
    }
  }

private:
#if defined(__x86_64__) || defined(_M_X64) || defined(__i386__) || defined(_M_IX86)
  unsigned int originalMxcsr;
#endif
};

} // namespace dnb::dsp::core
