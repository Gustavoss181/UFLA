/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"



//==============================================================================
SintetizadorAudioProcessor::SintetizadorAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
    : AudioProcessor(BusesProperties()
#if ! JucePlugin_IsMidiEffect
#if ! JucePlugin_IsSynth
        .withInput("Input", juce::AudioChannelSet::stereo(), true)
#endif
        .withOutput("Output", juce::AudioChannelSet::stereo(), true)
#endif
    ), apvts(*this, nullptr, "parameters", createParameters())
#endif
{
    synth.addSound(new SynthSound());
    synth.addVoice(new SynthVoice());
}

SintetizadorAudioProcessor::~SintetizadorAudioProcessor()
{
}

//==============================================================================
const juce::String SintetizadorAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool SintetizadorAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool SintetizadorAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool SintetizadorAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double SintetizadorAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int SintetizadorAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int SintetizadorAudioProcessor::getCurrentProgram()
{
    return 0;
}

void SintetizadorAudioProcessor::setCurrentProgram (int index)
{
}

const juce::String SintetizadorAudioProcessor::getProgramName (int index)
{
    return {};
}

void SintetizadorAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================
void SintetizadorAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    synth.getSampleRate();

    for (int i = 0; i < synth.getNumVoices();i++)
    {
        
        if (auto voice = dynamic_cast<SynthVoice*>(synth.getVoice(i)))
        {
            voice->prepareToPlay(sampleRate, samplesPerBlock, getTotalNumOutputChannels());
        }

        juce::dsp::ProcessSpec spec;
        spec.maximumBlockSize = samplesPerBlock;
        spec.sampleRate = sampleRate;
        spec.numChannels = getTotalNumOutputChannels();

        



    }


}

void SintetizadorAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool SintetizadorAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    juce::ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    // Some plugin hosts, such as certain GarageBand versions, will only
    // load plugins that support stereo bus layouts.
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void SintetizadorAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    

    
    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());

    
    for (int i = 0; i < synth.getNumVoices(); i++)
    {

        auto voice2 = dynamic_cast<SynthVoice*>(synth.getVoice(i));
        voice2->updateADSR(0.5, 0.5, 0.4, 0.5);
        

      
       // voice->updateADSR(0.5, 0.5, 0.4, 0.5);
        if (auto voice = dynamic_cast<SynthVoice*>(synth.getVoice(i)))
        {/*
            auto& atack = *apvts.getRawParameterValue("ATACK");
            auto& decay = *apvts.getRawParameterValue("DECAY");
            auto& sustain = *apvts.getRawParameterValue("SUSTAIN");
            auto& release = *apvts.getRawParameterValue("RELEASE");
            
            
           voice->updateADSR( atack.load(), decay.load(), sustain.load(),   release.load());
           
          */

            voice->updateADSR(0.5, 0.5, 0.4, 0.5);
            //voice->updateADSR(0.5, 0.5, 0.4, 0.5);
        }
    }


    synth.renderNextBlock(buffer, midiMessages, 0, buffer.getNumSamples());

}

//==============================================================================
bool SintetizadorAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* SintetizadorAudioProcessor::createEditor()
{
    return new SintetizadorAudioProcessorEditor (*this);
}

//==============================================================================
void SintetizadorAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void SintetizadorAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new SintetizadorAudioProcessor();
}


juce::AudioProcessorValueTreeState::ParameterLayout SintetizadorAudioProcessor :: createParameters()
{
    //combobox switch oscilator
    //atack float
    //decay 
    //sustain
    //release
      

    std::vector < std::unique_ptr<juce::RangedAudioParameter>>params;


    params.push_back    (std::make_unique <juce::AudioParameterChoice>
        ("OSC", "Oscilator", juce::StringArray{ "Sine", "Saw", "Square" }, 0));


    params.push_back(std::make_unique<juce::AudioParameterFloat>("ATACK", "Atack", juce::NormalisableRange<float>{0.1f, 1.0f, }, 0.1f));

    params.push_back(std::make_unique<juce::AudioParameterFloat>("DECAY", "Decay", juce::NormalisableRange<float>{0.1f, 1.0f}, 0.1f));

    params.push_back(std::make_unique<juce::AudioParameterFloat>("SUSTAIN", "Sustain", juce::NormalisableRange<float>{0.1f, 1.0f}, 1.0f));

    params.push_back(std::make_unique<juce::AudioParameterFloat>("RELEASE", "Release", juce::NormalisableRange<float>{0.1f, 1.0f}, 0.4f));

    return{ params.begin(),params.end() };

    
       
}