/*
  ==============================================================================

    PhantomVoice.cpp
    Created: 20 Jan 2021 20:59:55
    Author:  Matthew Maxwell

  ==============================================================================
*/

#include "PhantomVoice.h"
#include "PhantomSound.h"
#include "PhantomUtils.h"

PhantomVoice::PhantomVoice(AudioProcessorValueTreeState& vts, dsp::ProcessSpec& ps)
    :   m_parameters(vts)
{
    p_oscSync = m_parameters.getRawParameterValue(Consts::_OSC_SYNC_PARAM_ID);
    
    m_ampEg.reset(new PhantomEnvelopeGenerator(m_parameters, EnvelopeGeneratorType::AMP));
    m_phaseEg.reset(new PhantomEnvelopeGenerator(m_parameters, EnvelopeGeneratorType::PHASE));
    m_filterEg.reset(new PhantomEnvelopeGenerator(m_parameters, EnvelopeGeneratorType::FLTR));
    m_modEg.reset(new PhantomEnvelopeGenerator(m_parameters, EnvelopeGeneratorType::MOD));

    m_lfo01.reset(new PhantomLFO(m_parameters, 1));
    m_lfo02.reset(new PhantomLFO(m_parameters, 2));

    m_primaryOsc.reset(new PhantomOscillator(m_parameters, 1));
    m_secondaryOsc.reset(new PhantomOscillator(m_parameters, 2));
    m_mixer.reset(new PhantomMixer(m_parameters));

    m_filter.reset(new PhantomFilter(m_parameters, ps));
}

PhantomVoice::~PhantomVoice()
{
    p_oscSync = nullptr;

    m_ampEg = nullptr;
    m_phaseEg = nullptr;
    m_filterEg = nullptr;
    m_modEg = nullptr;

    m_lfo01 = nullptr;
    m_lfo02 = nullptr;
    
    m_primaryOsc = nullptr;
    m_secondaryOsc = nullptr;
    
    m_mixer = nullptr;

    m_filter = nullptr;
}

bool PhantomVoice::canPlaySound(SynthesiserSound* sound)
{
    return dynamic_cast<PhantomSound*> (sound) != nullptr;
}

void PhantomVoice::startNote(int midiNoteNumber, float velocity, SynthesiserSound* sound, int currentPitchWheelPosition)
{
    m_isNoteOn = true;
    m_isNoteCleared = false;

    const float sampleRate = (float) getSampleRate();

    m_midiNoteNumber = midiNoteNumber;
    m_primaryOsc->update(m_midiNoteNumber, sampleRate);
    m_secondaryOsc->update(m_midiNoteNumber, sampleRate);
    
    m_ampEg->noteOn();
    m_phaseEg->noteOn();
    m_filterEg->noteOn();
    m_modEg->noteOn();
}

void PhantomVoice::stopNote(float velocity, bool allowTailOff)
{
    m_isNoteOn = false;

    m_ampEg->noteOff();
    m_phaseEg->noteOff();
    m_filterEg->noteOff();
    m_modEg->noteOff();
}

void PhantomVoice::clear()
{
    clearCurrentNote();

    m_ampEg->reset();
    m_phaseEg->reset();
    m_filterEg->reset();
    m_modEg->reset();

    m_primaryOsc->reset();
    m_secondaryOsc->reset();

    m_isNoteCleared = true;
}

void PhantomVoice::renderNextBlock(AudioBuffer<float>& buffer, int startSample, int numSamples)
{
    if(m_isNoteOn && !isKeyDown())
        stopNote(0.0f, true);

    const float sampleRate = (float) getSampleRate();

    m_ampEg->update(sampleRate);
    m_phaseEg->update(sampleRate);
    m_filterEg->update(sampleRate);
    m_modEg->update(sampleRate);

    m_lfo01->update(sampleRate);
    m_lfo02->update(sampleRate);

    m_primaryOsc->update(m_midiNoteNumber, sampleRate);
    m_secondaryOsc->update(m_midiNoteNumber, sampleRate);
    
    m_filter->update();

    for (int sampleIdx = startSample; sampleIdx < numSamples; sampleIdx++)
    {
        float ampEgMod = m_ampEg->evaluate();
        float phaseEgMod = m_phaseEg->evaluate();
        float filterEgMod = m_filterEg->evaluate();
        float modEgMod = m_modEg->evaluate();

        float lfo01Mod = m_lfo01->evaluate();
        float lfo02Mod = m_lfo02->evaluate();

        float primaryOscVal = handleOscSync(m_primaryOsc->evaluate(modEgMod, lfo02Mod, phaseEgMod, lfo02Mod));
        float secondaryOscVal = m_secondaryOsc->evaluate(modEgMod, lfo02Mod, phaseEgMod, lfo02Mod);
        float oscVal = m_mixer->evaluate(primaryOscVal, secondaryOscVal);

        float filterVal = m_filter->evaluate(oscVal, filterEgMod, lfo01Mod);
        float ampVal = filterVal * ampEgMod;

        if(m_ampEg->isActive()) m_tailOff = 1.0f;
        float finalVal = ampVal * m_tailOff;

        m_tailOff *= 0.99f;
        if(m_tailOff < 0.00001f && !m_isNoteCleared)
            clear();

        for (int channelIdx = 0; channelIdx < buffer.getNumChannels(); channelIdx++)
            buffer.addSample(channelIdx, sampleIdx, finalVal);
    }
}

float PhantomVoice::handleOscSync(const float valueToRead) noexcept
{
    if(!*p_oscSync) return valueToRead;

    if(std::abs(valueToRead) <= k_oscSyncPhaseThreshold) {
        if(m_oscSyncToggle)
            m_secondaryOsc->updatePhase(valueToRead);

        m_oscSyncToggle = !m_oscSyncToggle;
    }

    return valueToRead;
}
