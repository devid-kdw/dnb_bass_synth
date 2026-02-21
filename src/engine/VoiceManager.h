#pragma once

#include "../domain/ConstraintEngine.h"
#include "NoteStack.h"
#include "Voice.h"

namespace dnb::engine {

// Manages voice allocation with a strict monophonic/paraphonic policy.
// Follows DnB rules to ensure sub-bass phase lock and latest-note priority.
class VoiceManager {
public:
  VoiceManager() = default;

  void prepare(double sampleRate, size_t maxBlockSize) {
    voice.prepare(sampleRate, maxBlockSize);
    noteStack.clear();
  }

  void setParameters(const domain::ResolvedParams &params) {
    voice.setParameters(params);
  }

  void noteOn(int noteNumber, float velocity) {
    bool wasLegato = noteStack.isLegato() || !noteStack.isEmpty();
    noteStack.pushNote(noteNumber, velocity);

    if (wasLegato && voice.isActive()) {
      // Legato glide (pitch change without envelope reset or phase reset)
      voice.updatePitch(noteNumber);
    } else {
      // Hard trigger
      voice.noteOn(noteNumber, velocity);
    }
  }

  void noteOff(int noteNumber) {
    int currentNote = noteStack.getLatestNote().noteNumber;
    noteStack.popNote(noteNumber);

    if (noteStack.isEmpty()) {
      voice.noteOff();
    } else {
      // Legato revert to previous note
      int prevNote = noteStack.getLatestNote().noteNumber;
      if (currentNote != prevNote) {
        voice.updatePitch(prevNote);
      }
    }
  }

  // Returns true if voice is actively producing sound
  bool processBlock(float *subOut, float *charOut, size_t numSamples) {
    if (!voice.isActive()) {
      return false;
    }
    voice.processBlock(subOut, charOut, numSamples);
    return true;
  }

  void clear() {
    noteStack.clear();
    voice.noteOff(); // Fast release
  }

private:
  Voice voice; // Monophonic strict rule
  NoteStack noteStack;
};

} // namespace dnb::engine
