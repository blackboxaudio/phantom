/*
  ==============================================================================

    PhantomSynth.cpp
    Created: 21 Jan 2021 10:45:00
    Author:  Matthew Maxwell

  ==============================================================================
*/

#include "PhantomSynth.h"
#include "PhantomSound.h"
#include "PhantomVoice.h"

PhantomSynth::PhantomSynth(AudioProcessorValueTreeState& vts)
    :   m_parameters(vts)
{

}

PhantomSynth::~PhantomSynth()
{
    clear();
}

void PhantomSynth::init(float sampleRate, int samplesPerBlock, int numChannels, AudioPlayHead* playHead)
{
    clear();

    setCurrentPlaybackSampleRate(sampleRate);

    m_processSpec = {
        (double) sampleRate,
        static_cast<uint32>(samplesPerBlock),
        static_cast<uint32>(1)
    };

    addVoices(playHead);
    addSounds();
}

void PhantomSynth::clear()
{
    clearSounds();
    clearVoices();
}

void PhantomSynth::addVoices(AudioPlayHead* playHead)
{
    for(int i = 0; i < k_numVoices; i++)
    {
        PhantomVoice* voice = new PhantomVoice(m_parameters, m_processSpec, playHead);
        addVoice(voice);
    }
}

void PhantomSynth::addSounds()
{
    PhantomSound* sound = new PhantomSound();
    addSound(sound);
}
