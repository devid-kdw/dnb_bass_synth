#pragma once

#include <cmath>

namespace dnb::dsp::filters {

// Cascaded 2nd order Butterworths forming a 4th order (24dB/oct) LR Crossover.
// Perfectly sums to a flat response, used to split Sub and Character bands
// safely.
class CrossoverLR4 {
public:
  CrossoverLR4() = default;

  void prepare(double newSampleRate) {
    sampleRate = newSampleRate;
    reset();
  }

  void reset() {
    for (int i = 0; i < 4; ++i) {
      z1_lp[i] = z2_lp[i] = 0.0f;
      z1_hp[i] = z2_hp[i] = 0.0f;
    }
  }

  // Set crossover split frequency (typically 120Hz based on DnBLimits.h)
  void setFrequency(float freq) {
    // Simple direct-form biquad coeff generation for matched 2nd-order
    // butterworths
    const float w0 = static_cast<float>(2.0 * M_PI * freq / sampleRate);
    const float alpha = std::sin(w0) / (2.0f * 0.70710678f); // Q = 1/sqrt(2)
    const float cosw0 = std::cos(w0);

    // Lowpass
    const float b0_lp = (1.0f - cosw0) / 2.0f;
    const float b1_lp = 1.0f - cosw0;
    const float b2_lp = (1.0f - cosw0) / 2.0f;
    const float a0_lp = 1.0f + alpha;
    const float a1_lp = -2.0f * cosw0;
    const float a2_lp = 1.0f - alpha;

    c_b0_lp = b0_lp / a0_lp;
    c_b1_lp = b1_lp / a0_lp;
    c_b2_lp = b2_lp / a0_lp;
    c_a1_lp = a1_lp / a0_lp;
    c_a2_lp = a2_lp / a0_lp;

    // Highpass
    const float b0_hp = (1.0f + cosw0) / 2.0f;
    const float b1_hp = -(1.0f + cosw0);
    const float b2_hp = (1.0f + cosw0) / 2.0f;

    c_b0_hp = b0_hp / a0_lp; // a0 is identical
    c_b1_hp = b1_hp / a0_lp;
    c_b2_hp = b2_hp / a0_lp;
    c_a1_hp = a1_lp / a0_lp;
    c_a2_hp = a2_lp / a0_lp;
  }

  // Process a single sample, splitting into sub and character bands
  inline void process(float input, float &outLow, float &outHigh) {
    // Stage 1 LP
    float lp1 = c_b0_lp * input + c_b1_lp * z1_lp[0] + c_b2_lp * z2_lp[0] - c_a1_lp * z1_lp[1] -
                c_a2_lp * z2_lp[1];
    z2_lp[0] = z1_lp[0];
    z1_lp[0] = input;
    z2_lp[1] = z1_lp[1];
    z1_lp[1] = lp1;

    // Stage 2 LP
    float lp2 = c_b0_lp * lp1 + c_b1_lp * z1_lp[2] + c_b2_lp * z2_lp[2] - c_a1_lp * z1_lp[3] -
                c_a2_lp * z2_lp[3];
    z2_lp[2] = z1_lp[2];
    z1_lp[2] = lp1;
    z2_lp[3] = z1_lp[3];
    z1_lp[3] = lp2;

    outLow = lp2;

    // Stage 1 HP
    float hp1 = c_b0_hp * input + c_b1_hp * z1_hp[0] + c_b2_hp * z2_hp[0] - c_a1_hp * z1_hp[1] -
                c_a2_hp * z2_hp[1];
    z2_hp[0] = z1_hp[0];
    z1_hp[0] = input;
    z2_hp[1] = z1_hp[1];
    z1_hp[1] = hp1;

    // Stage 2 HP
    float hp2 = c_b0_hp * hp1 + c_b1_hp * z1_hp[2] + c_b2_hp * z2_hp[2] - c_a1_hp * z1_hp[3] -
                c_a2_hp * z2_hp[3];
    z2_hp[2] = z1_hp[2];
    z1_hp[2] = hp1;
    z2_hp[3] = z1_hp[3];
    z1_hp[3] = hp2;

    // LR4 HP output requires flipping phase to sum perfectly flat with LP
    outHigh = -hp2;
  }

private:
  double sampleRate = 44100.0;

  float c_b0_lp = 0.f, c_b1_lp = 0.f, c_b2_lp = 0.f, c_a1_lp = 0.f, c_a2_lp = 0.f;
  float c_b0_hp = 0.f, c_b1_hp = 0.f, c_b2_hp = 0.f, c_a1_hp = 0.f, c_a2_hp = 0.f;

  // Biquad histories (x1, y1, x2, y2)
  float z1_lp[4] = {0.f};
  float z2_lp[4] = {0.f};
  float z1_hp[4] = {0.f};
  float z2_hp[4] = {0.f};
};

} // namespace dnb::dsp::filters
