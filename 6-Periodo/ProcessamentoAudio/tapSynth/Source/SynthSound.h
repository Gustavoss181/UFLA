/*
  ==============================================================================

    SynthSound.h
    Created: 4 May 2024 8:07:07pm
    Author:  gusta

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

class SynthSound : public juce::SynthesiserSound
{
public:
    bool appliesToNote(int midiNoteNumber) override { return true; };
    bool appliesToChannel(int midChannel) override { return true; };
};