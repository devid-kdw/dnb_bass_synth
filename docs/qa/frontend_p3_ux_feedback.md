# Frontend P3 UX Feedback & Visual Feedback Map

Date: 2026-02-21  
Context: Feedback for Backend P3 (Osc/Filter/Nonlinear DSP) and prep for P5 wiring.

## 1. Visual Feedback Map (UI -> DSP Requests)

To deliver the "industry-grade" UX outlined in the supplementary spec (dark theme, macro animations, oscilloscope, real-time FFT), the UI requires specific data streams from the DSP/Engine layer.

### 1.1 Oscilloscope & Spectrum Analyzer (Real-Time Streams)
- **Sub Channel Wave & FFT**: We need a way to read the clean 'Sub' sine/triangle output independently from the Character channel.
- **Character Channel Wave & FFT**: We need access to the heavily driven wavetable/FM/wavefold signal.
- **Request**: Please expose a lock-free ringbuffer or FIFO (e.g., `juce::AudioBuffer` queue) for both the Sub and Character distinct paths before the Master output limits.

### 1.2 Macro Modulation Response (Neuro-Formant & Foghorn)
- The UI will visualize notch filter movements across the FFT when `macro.neuro_formant` is turned.
- **Request**: We need the `ConstraintEngine` to expose the active/computed cutoff frequencies for the notch filters, or we need to recreate the formant trajectory math strictly in the UI solely for rendering. (Preference: Backend exposes `read_only` APVTS parameters for visual state, e.g., `visual.notch1_khz`, `visual.notch2_khz`, or provides an interface to query current DSP state). 

### 1.3 Style Mode State Indicators
- **Style Mode Morph**: The spec requires a 50-100ms morphing interpolation when switching styles.
- **Request**: Expose a read-only variable or parameter (e.g., `style.morph_progress`) ranging `0.0` to `1.0` so the UI can animate the color transitions smoothly (e.g., fading from Tech Blue to Neuro Green) without guessing the backend timing.

## 2. Parameter Naming/Range Ergonomics (Without Constraint Logic Change)

- **Parameter Resolution**: Ensure macros (`0.0 - 1.0` internally) are mapped to skewed output ranges if linear feels unnatural. E.g., `macro.fm_metal` depth should probably skew exponentially so the lower ranges (`1.41`) have wider knob travel than the extreme (`8.23`).
- **LFO Sync Names**: Map BPM sync LFO rate parameter text to strings like "1/4", "1/8D", "1/16" directly in the APVTS parameter formatting lambda. This saves the UI from having to maintain a duplicate text array for LFO divisions.
- **Naming Context**: For the 4 active P1 MVP macros, keep the UI label mapping to the conceptual workflow (Squelch, Foghorn, Wobble, Warmth) but keep the codebase APVTS IDs strictly schema-frozen (`macro.neuro_formant`, `macro.fm_metal`, etc.).

## 3. Next Steps
UI layout placeholders are now completely prepared. No runtime bypass was created. UI waits for Backend P3 / P4 completion to receive stable parameter bindings and visual FIFO data streams before final P5 wiring.
