/*
  ==============================================================================

    SynthVoice.h
    Created: 8 Apr 2024 1:49:21pm
    Author:  thoma

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "synthSound.h"

class SynthVoice : public juce::SynthesiserVoice
{
public:

    bool canPlaySound(juce::SynthesiserSound* sound) override;

    void startNote(int	midiNoteNumber, float	velocity, juce::SynthesiserSound* sound, int	currentPitchWheelPosition) override;

    void stopNote(float	velocity, bool	allowTailOff) override;

    void controllerMoved(int	controllerNumber, int	newControllerValue) override;

    void    renderNextBlock(juce::AudioBuffer< float >& outputBuffer, int	startSample, int	numSamples) override;

    void pitchWheelMoved(int	newPitchWheelValue) override;



    void prepareToPlay(double sampleRate, int samplesPerBlock, int outputChannels);

    bool isPrepared{ false };

    void updateADSR (const float atackUpdate, const float decayUpdate, const float sustainUpdate,  const float releaseUpdate) ;

    void teste123();

private:

    juce::dsp::Oscillator<float> osc();
    juce::dsp::Oscillator<double> osc2{ [](double x) {return std::sin(x); } }; // funcao matematica dente de serra

    juce::dsp::Gain<double> gainOsc;

    juce::ADSR adsr;

    juce::ADSR::Parameters adsrParams;


    juce::AudioBuffer<float> synthBuffer;

    //bool isPreapared{ false };




};
