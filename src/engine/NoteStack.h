#pragma once

#include <algorithm>
#include <array>
#include <cstdint>

namespace dnb::engine {

struct NoteEvent {
  int noteNumber;
  float velocity;
  bool isActive;
};

// Tracks active MIDI notes using LIFO (Latest Note Priority) logic.
// Necessary for monophonic/paraphonic synth control and legato detection.
class NoteStack {
public:
  NoteStack() : count(0) {}

  void pushNote(int noteNumber, float velocity) {
    // If the note is already in the stack, remove it first
    popNote(noteNumber);

    // Shift elements right to make room at the front
    if (count < 16) {
      for (size_t i = count; i > 0; --i) {
        activeNotes[i] = activeNotes[i - 1];
      }
      count++;
    } else {
      for (size_t i = 15; i > 0; --i) {
        activeNotes[i] = activeNotes[i - 1];
      }
    }

    // Add to the front (latest)
    activeNotes[0] = {noteNumber, velocity, true};
  }

  void popNote(int noteNumber) {
    auto it = std::find_if(activeNotes.begin(), activeNotes.begin() + count,
                           [noteNumber](const NoteEvent &n) { return n.noteNumber == noteNumber; });

    if (it != activeNotes.begin() + count) {
      size_t index = std::distance(activeNotes.begin(), it);
      // Shift left
      for (size_t i = index; i < count - 1; ++i) {
        activeNotes[i] = activeNotes[i + 1];
      }
      count--;
    }
  }

  void clear() {
    count = 0;
  }

  [[nodiscard]] bool isEmpty() const {
    return count == 0;
  }

  [[nodiscard]] bool isLegato() const {
    return count > 1;
  }

  [[nodiscard]] NoteEvent getLatestNote() const {
    if (count == 0) {
      return {-1, 0.0f, false};
    }
    return activeNotes[0];
  }

private:
  std::array<NoteEvent, 16> activeNotes;
  size_t count;
};

} // namespace dnb::engine
