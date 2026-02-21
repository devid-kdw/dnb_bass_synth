#pragma once

#include <vector>

namespace dnb::dsp::core {

// Abstract interface for per-module oversampling.
// According to ADR-002 and TechStack rules, nonlinear modules
// (FM, Wavefold, dist) must use their own polyphase FIR oversamplers (via
// HIIR). This class wraps the interface so the DSP code remains clean.
class Oversampler {
public:
  enum class Factor { x2 = 2, x4 = 4, x8 = 8 };

  Oversampler() = default;
  ~Oversampler() = default;

  void prepare(double baseSampleRate, Factor factor, size_t maxBlockSize) {
    this->factor = static_cast<int>(factor);
    this->currentSampleRate = baseSampleRate;
    upSampledBuffer.resize(maxBlockSize * this->factor);
  }

  void reset() {
    std::fill(upSampledBuffer.begin(), upSampledBuffer.end(), 0.0f);
    // HIIR internal state reset would go here
  }

  // Up-samples an input block. Returns a pointer to the oversampled buffer.
  float *processUp(const float *input, size_t numSamples) {
    // Placeholder for real polyphase upsampling using HIIR
    // Simple zero-stuffing / hold for demonstration structure:
    for (size_t i = 0; i < numSamples; ++i) {
      for (int f = 0; f < factor; ++f) {
        upSampledBuffer[i * factor + f] = input[i];
      }
    }
    return upSampledBuffer.data();
  }

  // Down-samples back into the output block.
  void processDown(float *output, size_t numSamples) {
    // Placeholder for real polyphase downsampling using HIIR
    // Simple decimation for structural testing:
    for (size_t i = 0; i < numSamples; ++i) {
      output[i] = upSampledBuffer[i * factor];
    }
  }

private:
  int factor = 2;
  double currentSampleRate = 44100.0;
  std::vector<float> upSampledBuffer;
};

} // namespace dnb::dsp::core
