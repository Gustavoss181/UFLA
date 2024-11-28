/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

//==============================================================================
/**
*/
class SintetizadorAudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    SintetizadorAudioProcessorEditor (SintetizadorAudioProcessor&);
    ~SintetizadorAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

    

private:

    
    void  SetSliderParams(juce::Slider& slider);
    
    SintetizadorAudioProcessor& audioProcessor;
    
    //using sliderAtachment = juce::AudioProcessorValueTreeState::SliderAttachment;

    // Sliders para controle do synth

    juce::Slider atackSlider;
    juce::Slider decaySlider;
    juce::Slider sustainSlider;
    juce::Slider realeseSlider;
    juce::ComboBox oscSelector;

    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment>   atackAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment>   decayAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> sustainAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> releaseAttachment;
    std::unique_ptr <juce::AudioProcessorValueTreeState::ComboBoxAttachment> oscSelAttachment;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(SintetizadorAudioProcessorEditor)

    
};
