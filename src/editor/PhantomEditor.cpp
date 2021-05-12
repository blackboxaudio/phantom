/*
  ==============================================================================
    This file was auto-generated!
    It contains the basic framework code for a JUCE plugin editor.
  ==============================================================================
*/

#include "PhantomEditor.h"

#include "../utils/PhantomData.h"
#include "../utils/PhantomUtils.h"

PhantomAudioProcessorEditor::PhantomAudioProcessorEditor(PhantomAudioProcessor& p, AudioProcessorValueTreeState& vts) : AudioProcessorEditor(&p), m_processor(p), m_parameters(vts)
{
    m_phantomAmplifier = std::make_unique<PhantomAmplifierComponent>(m_lookAndFeel, vts);
    addAndMakeVisible(m_phantomAmplifier.get());

    m_phantomOscillators = std::make_unique<PhantomOscillatorComponent>(m_lookAndFeel, vts);
    addAndMakeVisible(m_phantomOscillators.get());

    m_phantomPhasors = std::make_unique<PhantomPhasorComponent>(m_lookAndFeel, vts);
    addAndMakeVisible(m_phantomPhasors.get());

    m_phantomMixer = std::make_unique<PhantomMixerComponent>(m_lookAndFeel, vts);
    addAndMakeVisible(m_phantomMixer.get());

    m_phantomFilter = std::make_unique<PhantomFilterComponent>(m_lookAndFeel, vts);
    addAndMakeVisible(m_phantomFilter.get());

    m_phantomLFOs = std::make_unique<PhantomLFOComponent>(m_lookAndFeel, vts);
    addAndMakeVisible(m_phantomLFOs.get());

    m_phantomAmpEg = std::make_unique<PhantomEnvelopeComponent>(EnvelopeType::AMP, m_lookAndFeel, vts);
    addAndMakeVisible(m_phantomAmpEg.get());

    m_phantomPhasorEg = std::make_unique<PhantomEnvelopeComponent>(EnvelopeType::PHASOR, m_lookAndFeel, vts);
    addAndMakeVisible(m_phantomPhasorEg.get());

    m_phantomFilterEg = std::make_unique<PhantomEnvelopeComponent>(EnvelopeType::FILTER, m_lookAndFeel, vts);
    addAndMakeVisible(m_phantomFilterEg.get());

    m_phantomModEg = std::make_unique<PhantomEnvelopeComponent>(EnvelopeType::MOD, m_lookAndFeel, vts);
    addAndMakeVisible(m_phantomModEg.get());

    m_phantomAnalyzer = std::make_unique<PhantomAnalyzerComponent>(m_lookAndFeel, vts);
    addAndMakeVisible(m_phantomAnalyzer.get());

    m_phantomOscilloscope = std::make_unique<PhantomOscilloscopeComponent>(m_lookAndFeel, vts);
    addAndMakeVisible(m_phantomOscilloscope.get());

    m_phantomPreset = std::make_unique<PhantomPresetComponent>(m_lookAndFeel, m_processor.getPresetManager(), vts);
    addAndMakeVisible(m_phantomPreset.get());

    init();
}

PhantomAudioProcessorEditor::~PhantomAudioProcessorEditor()
{
    setLookAndFeel(nullptr);

    m_phantomAmplifier = nullptr;
    m_phantomOscillators = nullptr;
    m_phantomPhasors = nullptr;
    m_phantomMixer = nullptr;
    m_phantomFilter = nullptr;

    m_phantomLFOs = nullptr;
    
    m_phantomAmpEg = nullptr;
    m_phantomPhasorEg = nullptr;
    m_phantomFilterEg = nullptr;
    m_phantomModEg = nullptr;
    
    m_phantomPreset = nullptr;
    
    m_phantomAnalyzer = nullptr;
    m_phantomOscilloscope = nullptr;
}

void PhantomAudioProcessorEditor::init()
{
    setLookAndFeel(&m_lookAndFeel);

    float ratio = 16.0f / 9.0f;
    setResizable(true, true);
    setResizeLimits(720 * ratio, 720, 2160 * ratio, 2160); // 720p - 4K
    getConstrainer()->setFixedAspectRatio(ratio);
    setSize(960 * ratio, 960);
}

void PhantomAudioProcessorEditor::reset()
{
    m_phantomAmplifier->reset();
    m_phantomOscillators->reset();
    m_phantomPhasors->reset();
    m_phantomMixer->reset();
    m_phantomFilter->reset();

    m_phantomLFOs->reset();
    
    m_phantomAmpEg->reset();
    m_phantomPhasorEg->reset();
    m_phantomFilterEg->reset();
    m_phantomModEg->reset();
}

void PhantomAudioProcessorEditor::paint(Graphics& g)
{
    Image backgroundImage = ImageCache::getFromMemory(PhantomData::background_png, PhantomData::background_pngSize);
    g.drawImage(backgroundImage, getLocalBounds().toFloat());
}

void PhantomAudioProcessorEditor::resized()
{
    Rectangle<int> canvas = getLocalBounds();

    const int width = canvas.getWidth();
    const int height = canvas.getHeight();

    const int margin = width * PhantomLookAndFeel::_MARGIN_PER_WIDTH;

    const int sectionHeight = height * PhantomLookAndFeel::_SECTION_PER_HEIGHT;

    const int sliderDiameter = width * PhantomLookAndFeel::_SLIDER_PER_WIDTH;

    const int buttonHeight = height * PhantomLookAndFeel::_BUTTON_PER_HEIGHT;

    canvas.removeFromTop(margin);
    canvas.removeFromRight(margin);
    canvas.removeFromBottom(margin);
    canvas.removeFromLeft(margin);

    // TOP
    Rectangle<int> topSection = canvas.removeFromTop(sectionHeight + margin);
    canvas.removeFromTop(margin);

    Rectangle<int> oscillatorArea = topSection.removeFromRight(width * (93.0f / 128.0f));
    m_phantomOscillators->update(margin, sliderDiameter, width, height, oscillatorArea);

    // MIDDLE TOP
    Rectangle<int> middleTopSection = canvas.removeFromTop(sectionHeight);
    canvas.removeFromTop(margin);

    Rectangle<int> amplifierArea = middleTopSection.removeFromLeft(width * (61.0f / 256.0f));
    middleTopSection.removeFromLeft(margin);
    m_phantomAmplifier->update(margin, sliderDiameter, width, height, amplifierArea);

    Rectangle<int> phasorArea = middleTopSection.removeFromLeft(width * (61.0f / 128.0f));
    Rectangle<int> presetArea(phasorArea);
    middleTopSection.removeFromLeft(margin);
    m_phantomPhasors->update(margin, sliderDiameter, width, height, phasorArea);

    presetArea.expand(0, margin);
    presetArea.removeFromBottom(margin * 0.75f);
    m_phantomPreset->update(margin, presetArea.removeFromBottom(margin * 2));

    Rectangle<int> graphArea = middleTopSection.removeFromLeft(width * (61.0f / 256.0f) - 4);

    Rectangle<int> oscilloscopeArea = graphArea.removeFromTop(graphArea.getHeight() / 2.0f);
    m_phantomOscilloscope->update(margin, sliderDiameter, width, height, oscilloscopeArea);

    Rectangle<int> analyzerArea = graphArea;
    m_phantomAnalyzer->update(margin, sliderDiameter, width, height, analyzerArea);

    // MIDDLE BOTTOM
    Rectangle<int> middleBottomSection = canvas.removeFromTop(sectionHeight);
    canvas.removeFromTop(margin);

    Rectangle<int> mixerArea = middleBottomSection.removeFromLeft(width * (10457.0f / 38400.0f));
    middleBottomSection.removeFromLeft(margin);
    m_phantomMixer->update(margin, sliderDiameter, width, height, mixerArea);

    Rectangle<int> filterArea = middleBottomSection.removeFromLeft(width * (7843.0f / 19200.0f));
    middleBottomSection.removeFromLeft(margin);
    m_phantomFilter->update(margin, sliderDiameter, width, height, filterArea);

    Rectangle<int> lfoArea = middleBottomSection;
    m_phantomLFOs->update(margin, sliderDiameter, width, height, lfoArea);

    // BOTTOM
    Rectangle<int> bottomSection = canvas.removeFromBottom(sectionHeight);

    int egHeight = bottomSection.getHeight() / 2;
    int egWidth = (bottomSection.getWidth() - margin) / 2;

    Rectangle<int> bottomLeftSection = bottomSection.removeFromLeft(egWidth);
    m_phantomAmpEg->update(margin, sliderDiameter, width, height, bottomLeftSection.removeFromTop(egHeight));
    bottomLeftSection.removeFromTop(margin);
    m_phantomPhasorEg->update(margin, sliderDiameter, width, height, bottomLeftSection);

    Rectangle<int> bottomRightSection = bottomSection.removeFromRight(egWidth);
    m_phantomFilterEg->update(margin, sliderDiameter, width, height, bottomRightSection.removeFromTop(egHeight));
    bottomRightSection.removeFromTop(margin);
    m_phantomModEg->update(margin, sliderDiameter, width, height, bottomRightSection);
}
