#pragma once

#include <algorithm>
#include <cmath>
#include <numbers>
#include <vector>

namespace dnb::dsp::core {

// Polyphase FIR Oversampler.
// Replaces placeholder with true windowed Sinc anti-aliasing.
class Oversampler {
public:
  enum class Factor { x2 = 2, x4 = 4, x8 = 8 };

  Oversampler() = default;
  ~Oversampler() = default;

  void prepare(double baseSampleRate, Factor factorEnum, size_t maxBlockSize) {
    this->factor = static_cast<int>(factorEnum);
    this->currentSampleRate = baseSampleRate;
    upSampledBuffer.resize(maxBlockSize * this->factor, 0.0f);

    // Create an FIR lowpass kernel for anti-aliasing (Blackman-windowed Sinc)
    int numTaps = 31; // Must be odd
    firKernel.resize(numTaps, 0.0f);
    stateUp.resize(numTaps, 0.0f);
    stateDown.resize(numTaps, 0.0f);

    float cutoff = 0.5f / this->factor; // Nyquist limit of original signal relative to OS
    float sum = 0.0f;
    int center = numTaps / 2;
    for (int i = 0; i < numTaps; ++i) {
      if (i == center) {
        firKernel[i] = 2.0f * cutoff;
      } else {
        float x = kPi * static_cast<float>(i - center);
        firKernel[i] = std::sin(2.0f * cutoff * x) / x;
      }
      // Blackman window
      float window = 0.42f - 0.5f * std::cos(2.0f * kPi * static_cast<float>(i) / (numTaps - 1)) +
                     0.08f * std::cos(4.0f * kPi * static_cast<float>(i) / (numTaps - 1));
      firKernel[i] *= window;
      sum += firKernel[i];
    }

    // Normalize to preserve DC gain
    for (int i = 0; i < numTaps; ++i) {
      firKernel[i] /= sum;
    }

    // Up-sampling requires gain compensation by factor, as zero stuffing
    // dilutes energy
    for (int i = 0; i < numTaps; ++i) {
      firKernel[i] *= this->factor;
    }
  }

  void reset() {
    std::fill(upSampledBuffer.begin(), upSampledBuffer.end(), 0.0f);
    std::fill(stateUp.begin(), stateUp.end(), 0.0f);
    std::fill(stateDown.begin(), stateDown.end(), 0.0f);
  }

  size_t getCapacity() const {
    if (factor == 0)
      return 0;
    return upSampledBuffer.size() / factor;
  }

  // Access OS buffer directly when generating inside the oversampled domain
  float *getUpBuffer() {
    return upSampledBuffer.data();
  }

  // Up-samples an input block. Returns a pointer to the oversampled buffer.
  float *processUp(const float *input, size_t numSamples) {
    size_t safeSamples = std::min(numSamples, getCapacity());

    int taps = firKernel.size();
    for (size_t i = 0; i < safeSamples; ++i) {
      // Zero stuff
      for (int f = 0; f < factor; ++f) {
        float sample = (f == 0) ? input[i] : 0.0f;

        // Shift state
        for (int k = taps - 1; k > 0; --k) {
          stateUp[k] = stateUp[k - 1];
        }
        stateUp[0] = sample;

        // FIR filter
        float out = 0.0f;
        for (int k = 0; k < taps; ++k) {
          out += stateUp[k] * firKernel[k];
        }
        upSampledBuffer[i * factor + f] = out;
      }
    }
    return upSampledBuffer.data();
  }

  // Down-samples back into the output block.
  void processDown(float *output, size_t numSamples) {
    size_t safeSamples = std::min(numSamples, getCapacity());
    int taps = firKernel.size();
    float downGain = 1.0f / factor; // Revert the upsampling multiplier scale

    for (size_t i = 0; i < safeSamples; ++i) {
      float filteredOut = 0.0f;
      for (int f = 0; f < factor; ++f) {
        float sample = upSampledBuffer[i * factor + f];

        // Shift state
        for (int k = taps - 1; k > 0; --k) {
          stateDown[k] = stateDown[k - 1];
        }
        stateDown[0] = sample;

        // Filter
        float filterAcc = 0.0f;
        for (int k = 0; k < taps; ++k) {
          filterAcc += stateDown[k] * firKernel[k];
        }

        // Decimate
        if (f == factor - 1) {
          filteredOut = filterAcc * downGain;
        }
      }
      output[i] = filteredOut;
    }

    // Graceful degradation: zero-pad if block size exceeded prepared capacity
    for (size_t i = safeSamples; i < numSamples; ++i) {
      output[i] = 0.0f;
    }
  }

private:
  static constexpr float kPi = std::numbers::pi_v<float>;

  int factor = 4;
  double currentSampleRate = 44100.0;
  std::vector<float> upSampledBuffer;
  std::vector<float> firKernel;
  std::vector<float> stateUp;
  std::vector<float> stateDown;
};

} // namespace dnb::dsp::core
