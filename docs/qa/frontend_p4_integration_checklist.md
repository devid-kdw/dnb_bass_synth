# Frontend P4 Integration Checklist (Pre-P5 Wiring)

Date: 2026-02-21  
Context: Frontend prep for P5 (App Wiring + Macro UI) referencing the Engine Orchestration built in P4.

## 1. UI Test Scenarios (Prep)

To ensure the macro-first restriction design is maintained during Voice/Engine orchestration, the UI must visualize and react to the following engine states:

### 1.1 Legato/Retrigger Indications
- **Scenario**: When playing overlapping notes in Liquid Roller or Ragga mode (where Legato/Portamento is expected), the UI should visually indicate that the envelope did not retrigger (anti-click protection active, unbroken flow).
- **Scenario**: When playing staccato notes in Jump Up or Tech mode (Retrigger), the UI should clearly show envelope restarts (snappy attack).
- **Requirement**: The UI needs a visual representation of the active `Voice` envelope (e.g., an animated envelope curve or an LED indicator that flashes on hard retrigger).

### 1.2 Style Mode Transition UX Signaling
- **Scenario**: The user switches from `Tech` (Value 1) to `Dark` (Value 3).
- **Behavior**: The backend interpolates parameters over 50-100ms. 
- **Validation**: UI must not instantly snap the visual state to "Dark". The UI elements (colors, FFT outlines) must smoothly interpolate during this 50-100ms window to match the audio experience.

## 2. Event/State Surface Requirements (Backend -> Frontend)

Before P5 runtime binding can succeed, the backend must expose the following state surfaces to the frontend (via `juce::AudioProcessorValueTreeState` or custom FIFO/Lock-free mechanisms):

### 2.1 Engine States
1. **Active Voices Count**: `int` representing current active voices (0 to N, or 1 for strictly mono). Useful for UI diagnostics.
2. **Current Portamento Target**: Which note is currently being glided to.
3. **Style Morph Progress**: A normalized `0.0` to `1.0` value indicating the progress of the `StyleModeMorph` interpolation block. 
   *(Updated per P4 Remediation)*: The UI now specifically expects the backend `SynthEngine` to expose data driven by its new `updateStyleMorphProgress()` standard block-level calls. The UI will read from this exact state surface to animate the transition between Tech/Neuro/Dark visually.

### 2.2 DSP Data Streams (Reiterating P3 Feedback)
1. **Sub/Character Oscilloscope**: Raw audio float buffer per block.
2. **FFT Data**: Computed spectrum bins or raw block for UI-side FFT over the Master, Sub, and Character channels.

### 2.3 Parameter ID Frozen Contract (Recap)
The frontend binds strictly to:
- `style.mode` (Tech, Neuro, Dark)
- `macro.neuro_formant`
- `macro.fm_metal`
- `macro.roller_dynamics`
- `macro.liquid_depth`
- `env.amp.att` (ms)
- `env.amp.rel` (ms)

## 3. P5 Integration Readiness
The `BindingLayerScaffold` created in P2 is ready to be replaced with actual `juce::AudioProcessorValueTreeState::SliderAttachment` and `ComboBoxAttachment` instances once the `PluginProcessor` initializes this APVTS tree in P5.

**DoD Check**: The P5 integration requirements are fully defined and ready before full implementation.
