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
    Label m_oscRangeLabel;
    std::unique_ptr<SliderAttachment> m_oscRangeSliderAttachment;
    Slider m_oscCoarseTuneSlider;
    std::unique_ptr<SliderAttachment> m_oscCoarseTuneSliderAttachment;
    Slider m_oscFineTuneSlider;
    std::unique_ptr<SliderAttachment> m_oscFineTuneSliderAttachment;
    Slider m_oscModDepthSlider;
    std::unique_ptr<SliderAttachment> m_oscModDepthSliderAttachment;
    Slider m_oscModModeSlider;
    std::unique_ptr<SliderAttachment> m_oscModModeSliderAttachment;

    Slider m_phasorShapeSlider;
    std::unique_ptr<SliderAttachment> m_phasorShapeSliderAttachment;
    Slider m_phasorEgIntSlider;
    std::unique_ptr<SliderAttachment> m_phasorEgIntSliderAttachment;
    Slider m_phasorLfoIntSlider;
    std::unique_ptr<SliderAttachment> m_phasorLfoIntSliderAttachment;

    Slider m_filterCutoffSlider;
    std::unique_ptr<SliderAttachment> m_filterCutoffSliderAttachment;
    Slider m_filterResoSlider;
    std::unique_ptr<SliderAttachment> m_filterResoSliderAttachment;
    Slider m_filterEgModDepthSlider;
    std::unique_ptr<SliderAttachment> m_filterEgModDepthSliderAttachment;
    Slider m_filterLfoModDepthSlider;
    std::unique_ptr<SliderAttachment> m_filterLfoModDepthSliderAttachment;

    Slider m_ampEgAtkSlider;
    std::unique_ptr<SliderAttachment> m_ampEgAtkSliderAttachment;
    Slider m_ampEgDecSlider;
    std::unique_ptr<SliderAttachment> m_ampEgDecSliderAttachment;
    Slider m_ampEgSusSlider;
    std::unique_ptr<SliderAttachment> m_ampEgSusSliderAttachment;
    Slider m_ampEgRelSlider;
    std::unique_ptr<SliderAttachment> m_ampEgRelSliderAttachment;

    Slider m_phasorEgAtkSlider;
    std::unique_ptr<SliderAttachment> m_phasorEgAtkSliderAttachment;
    Slider m_phasorEgDecSlider;
    std::unique_ptr<SliderAttachment> m_phasorEgDecSliderAttachment;
    Slider m_phasorEgSusSlider;
    std::unique_ptr<SliderAttachment> m_phasorEgSusSliderAttachment;
    Slider m_phasorEgRelSlider;
    std::unique_ptr<SliderAttachment> m_phasorEgRelSliderAttachment;

    Slider m_filterEgAtkSlider;
    std::unique_ptr<SliderAttachment> m_filterEgAtkSliderAttachment;
    Slider m_filterEgDecSlider;
    std::unique_ptr<SliderAttachment> m_filterEgDecSliderAttachment;
    Slider m_filterEgSusSlider;
    std::unique_ptr<SliderAttachment> m_filterEgSusSliderAttachment;
    Slider m_filterEgRelSlider;
    std::unique_ptr<SliderAttachment> m_filterEgRelSliderAttachment;

    Slider m_modEgAtkSlider;
    std::unique_ptr<SliderAttachment> m_modEgAtkSliderAttachment;
    Slider m_modEgDecSlider;
    std::unique_ptr<SliderAttachment> m_modEgDecSliderAttachment;
    Slider m_modEgSusSlider;
    std::unique_ptr<SliderAttachment> m_modEgSusSliderAttachment;
    Slider m_modEgRelSlider;
    std::unique_ptr<SliderAttachment> m_modEgRelSliderAttachment;

    Slider m_lfoRateSlider;
    std::unique_ptr<SliderAttachment> m_lfoRateSliderAttachment;
    Slider m_lfoShapeSlider;
    std::unique_ptr<SliderAttachment> m_lfoShapeSliderAttachment;

    Slider m_levelSlider;
    std::unique_ptr<SliderAttachment> m_levelSliderAttachment; 
};
