/*
  ==============================================================================

    SynthSound.h
    Created: 8 Apr 2024 1:49:00pm
    Author:  thoma

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

class SynthSound :public juce::SynthesiserSound
{
    bool 	appliesToNote(int midiNoteNumber) override { return  true; }
    bool   appliesToChannel(int midiChannel) override { return true; }
};
