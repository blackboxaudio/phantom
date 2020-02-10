/*
  ==============================================================================

    PhantomVoice.h
    Created: 1 Feb 2020 8:35:21am
    Author:  Matthew Maxwell

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"

//==============================================================================
class PhantomSound : public SynthesiserSound
{
public:
    //==========================================================================
    bool appliesToNote(int midiNoteNumber) override
    {
        return true;
    }
    bool appliesToChannel(int midiChannel) override
    {
        return true;
    }
};

//==============================================================================
class PhantomPhasor
{
public:
    //==========================================================================
    PhantomPhasor(AudioProcessorValueTreeState& vts)     
        : parameters(vts)
    {
        // update phase distortion parameters
        phaseId = parameters.getRawParameterValue("phaseId");
        phaseIntensity = parameters.getRawParameterValue("phaseIntensity");
    };

    ~PhantomPhasor()    
    {

    };

    //==========================================================================
    void setPhaseDelta(float frequency, float sampleRate)
    {
        auto cyclesPerSample = frequency / sampleRate;
        phaseDelta = cyclesPerSample * MathConstants<float>::twoPi;
    }

    forcedinline float getNextSample(float envelope) noexcept
    {
        // get current position in float from 0.0f to 1.0f
        auto currentPhase = phase / MathConstants<float>::twoPi;

        // update phaseOffset according to DCW envelope (see Casio CZ-101 manual)
        phaseOffset = *phaseIntensity * envelope * -0.5f + 0.5f;

        switch ((int) *phaseId)
        {
            // SAWTOOTH WAVE
            default:
            case 0:
                phasor = Sawtooth(currentPhase, phaseOffset);
                break;

            // SQUARE WAVE 
            case 1:
                phasor = Square(currentPhase, phaseOffset);
                break;
        }

        phase = fmod(phase + phaseDelta, MathConstants<float>::twoPi);

        phasor *= MathConstants<float>::twoPi;

        return phasor;
    }

private:
    //==========================================================================
    float Sawtooth(float currentPhase, float phaseOffset)
    {
        float m;
        if (currentPhase < phaseOffset)
        {
            m = 0.5f / phaseOffset;
            phasor = m * currentPhase;
        }
        else
        {
            m = 0.5f / (1.0f - phaseOffset);
            float b = 1.0f - m;
            phasor = m * currentPhase + b;
        }
        return phasor;
    };

    float Square(float currentPhase, float phaseOffset)
    {
        float m;
        if (currentPhase < phaseOffset)
        {
            m = 0.5f / phaseOffset;
            phasor = m * currentPhase;
        }
        else
        {
            m = 0.1f / (1.0f - phaseOffset);
            float b = 0.6f;
            phasor = m * currentPhase + b;
        }
        return phasor;
    }

    //==========================================================================
    AudioProcessorValueTreeState& parameters;

    // phase distortion parameters
    std::atomic<float>* phaseId;
    std::atomic<float>* phaseIntensity;

    // phase distortion variables
    float phasor = 0.0f;
    float phase = 0.0f;
    float phaseDelta = 0.0f;
    float phaseOffset = 0.5f;
};

//==============================================================================
class PhantomVoice : public SynthesiserVoice
{
public:
    //==========================================================================
    PhantomVoice(AudioProcessorValueTreeState& vts)
        : parameters(vts), envelope(), phasor(vts)
    {
        // update adsr parameters
        attack = parameters.getRawParameterValue("attack");
        decay = parameters.getRawParameterValue("decay");
        sustain = parameters.getRawParameterValue("sustain");
        release = parameters.getRawParameterValue("release");
    }

    ~PhantomVoice() 
    {
    
    };

    //==========================================================================
    bool canPlaySound(SynthesiserSound* sound) override
    {
        // return if casting sound to my phantom defined sound is successful
        return dynamic_cast<PhantomSound*> (sound) != nullptr;
    }

    void startNote(int midiNoteNumber, float velocity, SynthesiserSound* sound, int currentPitchWheelPosition = 0) override
    {
        phasor.setPhaseDelta(MidiMessage::getMidiNoteInHertz(midiNoteNumber), getSampleRate());

        envelope.setSampleRate(getSampleRate());
        envelope.noteOn();
    }

    void stopNote(float velocity, bool allowTailOff) override
    {
        envelope.noteOff();
        clearCurrentNote();
    }

    //==========================================================================
    void pitchWheelMoved(int newPitchWheel)                             override {}
    void controllerMoved(int controllerNumber, int newControllerValue)  override {}

    //==========================================================================
    void renderNextBlock(AudioBuffer<float>& buffer, int startSample, int numSamples)
    {
        // first update adsr parameters struct and pass to envelope
        updateEnvelopeParameters();
        envelope.setParameters(envelopeParameters);

        // processing loop for samples
        for (int sample = 0; sample < numSamples; sample++)
        {            
            auto envelopeValue = envelope.getNextSample();
            auto sampleValue = cosf(phasor.getNextSample(envelopeValue));

            sampleValue *= envelopeValue;

            for (int channel = 0; channel < buffer.getNumChannels(); channel++)
                buffer.setSample(channel, startSample, sampleValue);

            startSample++;
        }
    }

private:

    //==========================================================================
    forcedinline void updateEnvelopeParameters() noexcept
    {
        envelopeParameters.attack   = *attack;
        envelopeParameters.decay    = *decay;
        envelopeParameters.sustain  = powf(2, *sustain / 6);
        envelopeParameters.release  = *release;
    }

    //==========================================================================
    AudioProcessorValueTreeState& parameters;

    // ADSR parameters
    std::atomic<float>* attack;
    std::atomic<float>* decay;
    std::atomic<float>* sustain;
    std::atomic<float>* release;

    // synth variables
    ADSR envelope;
    ADSR::Parameters envelopeParameters;
    PhantomPhasor phasor;
};