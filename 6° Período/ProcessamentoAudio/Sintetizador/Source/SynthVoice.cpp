/*
  ==============================================================================

    SynthVoice.cpp
    Created: 8 Apr 2024 1:49:21pm
    Author:  thoma

  ==============================================================================
*/

#include "SynthVoice.h"





bool SynthVoice::canPlaySound(juce::SynthesiserSound* sound)
{
    return dynamic_cast<juce::SynthesiserSound*>(sound) != nullptr;

}

void SynthVoice::startNote(int	midiNoteNumber, float	velocity, juce::SynthesiserSound* sound, int	currentPitchWheelPosition)
{
    osc2.setFrequency(juce::MidiMessage::getMidiNoteInHertz(midiNoteNumber));
    adsr.noteOn();

}

void  SynthVoice::stopNote(float	velocity, bool	allowTailOff)
{
    adsr.noteOff();

    if (!adsr.isActive() || !allowTailOff)
        clearCurrentNote();

}

void SynthVoice::controllerMoved(int	controllerNumber, int	newControllerValue)
{



}

void SynthVoice::renderNextBlock(juce::AudioBuffer< float > &outputBuffer, int	startSample, int	numSamples)
{
    jassert(isPrepared);

    if (!isVoiceActive())
        return;

    synthBuffer.setSize(outputBuffer.getNumChannels(), numSamples, false, false, true);
    synthBuffer.clear();


    juce::dsp::AudioBlock<float> audioBlock{ synthBuffer };
    osc2.process(juce::dsp::ProcessContextReplacing<float>(audioBlock));
    //  gainOsc.process(juce::dsp::ProcessContextReplacing<double>(audioBlock));
     // float x = sin(x);

    adsr.applyEnvelopeToBuffer(synthBuffer, 0, synthBuffer.getNumSamples());

    for (int channel = 0; channel < outputBuffer.getNumChannels(); ++channel)
    {
        outputBuffer.addFrom(channel, startSample, synthBuffer, channel, 0  , numSamples);

        if (!adsr.isActive())
            clearCurrentNote();

        


    }

}

void SynthVoice::pitchWheelMoved(int	newPitchWheelValue)
{


}

void SynthVoice::prepareToPlay(double sampleRate, int samplesPerBlock, int outputChannels)


{

    adsr.reset();
    adsr.setSampleRate(sampleRate);
    juce::dsp::ProcessSpec specs;

    juce::dsp::ProcessSpec specs2;


    specs2.maximumBlockSize = samplesPerBlock;
    specs2.numChannels = outputChannels;
    specs2.sampleRate = sampleRate;

    specs.maximumBlockSize = samplesPerBlock;
    specs.numChannels = specs2.numChannels = outputChannels;
    specs.sampleRate = sampleRate;


    osc2.prepare(specs);
    gainOsc.prepare(specs);
   // osc2.setFrequency(440.0f);

   // gainOsc.setGainLinear(0.1f);
   
    adsrParams.attack = 0.5f;
    adsrParams.decay = 0.3f;
    adsrParams.release = 0.4f;
    adsrParams.sustain = 0.6f;


    isPrepared = true;

}

void SynthVoice::updateADSR (const float atackUpdate, const float decayUpdate, const float sustainUpdate, const float releaseUpdate)
{   
    
    adsrParams.attack = atackUpdate;
    adsrParams.decay = decayUpdate;
    adsrParams.release = releaseUpdate;
    adsrParams.sustain = sustainUpdate;

    
    /*
    adsrParams.attack = 0.8f;
    adsrParams.decay = 0.8f;
    adsrParams.release = 1.0f;
    adsrParams.sustain = 1.5f;
    */


    adsr.setParameters(adsrParams);


}

void SynthVoice::teste123()
{}