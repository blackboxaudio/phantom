/*
  ==============================================================================
    This file was auto-generated!
    It contains the basic framework code for a JUCE plugin editor.
  ==============================================================================
*/

#pragma once

#include "JuceHeader.h"

#include "PhantomProcessor.h"

typedef AudioProcessorValueTreeState::SliderAttachment SliderAttachment;

//==============================================================================
/**
*/
class PhantomAudioProcessorEditor : public AudioProcessorEditor
{
public:
    PhantomAudioProcessorEditor(PhantomAudioProcessor&, AudioProcessorValueTreeState&);
    ~PhantomAudioProcessorEditor() override;

    //==========================================================================
    void paint(Graphics&) override;
    void resized() override;

private:
    //==========================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(PhantomAudioProcessorEditor)
    
    //==========================================================================
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    PhantomAudioProcessor& m_audioProcessor;

    AudioProcessorValueTreeState& m_parameters;

    //==========================================================================
    Slider m_oscRangeSlider;
    std::unique_ptr<SliderAttachment> m_oscRangeSliderAttachment;
    Slider m_oscTuneSlider;
    std::unique_ptr<SliderAttachment> m_oscTuneSliderAttachment;
    
    Slider m_ampEgAtkSlider;
    std::unique_ptr<SliderAttachment> m_ampEgAtkSliderAttachment;
    Slider m_ampEgDecSlider;
    std::unique_ptr<SliderAttachment> m_ampEgDecSliderAttachment;
    Slider m_ampEgSusSlider;
    std::unique_ptr<SliderAttachment> m_ampEgSusSliderAttachment;
    Slider m_ampEgRelSlider;
    std::unique_ptr<SliderAttachment> m_ampEgRelSliderAttachment;

    Slider m_levelSlider;
    std::unique_ptr<SliderAttachment> m_levelSliderAttachment; 
};
