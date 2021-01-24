/*
  ==============================================================================

    PhantomFilter.h
    Created: 23 Jan 2021 21:22:03
    Author:  Matthew Maxwell

    ** This filter implementation was taken from 

  ==============================================================================
*/

#pragma once

#include "JuceHeader.h"

#include "PhantomEnvelopeGenerator.h"

//==============================================================================
/**
*/
class PhantomFilter
{
public:
    //==========================================================================
    PhantomFilter(AudioProcessorValueTreeState&, PhantomEnvelopeGenerator&, dsp::ProcessSpec&);
    ~PhantomFilter();

    //==========================================================================
    void update() noexcept;

    //==========================================================================
    float evaluate(float sample) noexcept;

private:
    //==========================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(PhantomFilter)

    //==========================================================================
    AudioProcessorValueTreeState& m_parameters;

    std::atomic<float>* p_cutoff;
    std::atomic<float>* p_resonance;

    //==========================================================================
    dsp::StateVariableTPTFilter<float>* m_filter;
    dsp::StateVariableTPTFilterType m_type = dsp::StateVariableTPTFilterType::lowpass;

    PhantomEnvelopeGenerator* m_eg;
};