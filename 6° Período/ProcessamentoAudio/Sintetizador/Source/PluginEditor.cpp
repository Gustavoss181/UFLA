    /*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
SintetizadorAudioProcessorEditor::SintetizadorAudioProcessorEditor (SintetizadorAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (700, 500);

    //using SliderAttachment = juce::AudioProcessorValueTreeState::SliderAttachment;

    //addAndMakeVisible
    
    atackAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.apvts, "ATACK", atackSlider);
    sustainAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.apvts, "SUSTAIN", sustainSlider);
    releaseAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.apvts, "RELEASE", realeseSlider);
    decayAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.apvts, "DECAY", decaySlider);
    oscSelAttachment = std::make_unique<juce::AudioProcessorValueTreeState::ComboBoxAttachment>(audioProcessor.apvts, "OSC", oscSelector);

    SetSliderParams(atackSlider);
    SetSliderParams(decaySlider);
    SetSliderParams(sustainSlider);
    SetSliderParams(realeseSlider);

}

SintetizadorAudioProcessorEditor::~SintetizadorAudioProcessorEditor()
{
}

//==============================================================================
void SintetizadorAudioProcessorEditor::paint (juce::Graphics& g)
{
    g.fillAll(juce::Colours::bisque);
}

void SintetizadorAudioProcessorEditor::resized()
{

    //int rightAtack;
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
    const auto bounds = getLocalBounds().reduced(10);
    const auto padding = 10;
    const auto sliderWidth = bounds.getWidth() / 4 - padding;
    const auto sliderHeight = bounds.getHeight() / 4 - padding;
    const auto sliderStartX = 0;
    const auto sliderstartY = bounds.getHeight() / 2;

    atackSlider.setBounds(sliderStartX, sliderstartY, sliderWidth, sliderHeight);
   // rightAtack = atackSlider.getRight();



    decaySlider.setBounds(atackSlider.getRight() + padding, sliderstartY, sliderWidth, sliderHeight);
    sustainSlider.setBounds(decaySlider.getRight() + padding, sliderstartY, sliderWidth, sliderHeight);
    realeseSlider.setBounds(sustainSlider.getRight() + padding, sliderstartY, sliderWidth, sliderHeight);






}


void SintetizadorAudioProcessorEditor ::  SetSliderParams(juce::Slider& slider)
{

    slider.setSliderStyle(juce::Slider::SliderStyle::LinearVertical);
    slider.setTextBoxStyle(juce::Slider::TextBoxBelow,true, 50,25);
    addAndMakeVisible(slider);
    
}