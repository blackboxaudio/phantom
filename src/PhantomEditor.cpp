/*
  ==============================================================================
    This file was auto-generated!
    It contains the basic framework code for a JUCE plugin editor.
  ==============================================================================
*/

#include "PhantomEditor.h"
#include "PhantomProcessor.h"

//==============================================================================
PhantomAudioProcessorEditor::PhantomAudioProcessorEditor(PhantomAudioProcessor& p)
    : AudioProcessorEditor(&p), audioProcessor(p)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize(400, 300);
}

PhantomAudioProcessorEditor::~PhantomAudioProcessorEditor()
{
}

//==============================================================================
void PhantomAudioProcessorEditor::paint(Graphics& g)
{
    // Our component is opaque, so we must completely fill the background with a solid colour
    g.fillAll(getLookAndFeel().findColour(ResizableWindow::backgroundColourId));

    g.setColour(Colours::white);
    g.setFont(15.0f);
   
    g.drawFittedText("Phantom", getLocalBounds(), Justification::centred, 1);
}

void PhantomAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
}
