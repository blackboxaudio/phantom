/*
  ==============================================================================
    This file was auto-generated!
    It contains the basic framework code for a JUCE plugin processor.
  ==============================================================================
*/

#ifndef _PHANTOM_PROCESSOR_H
#define _PHANTOM_PROCESSOR_H

#include "JuceHeader.h"

#include "../effects/PhantomAmplifier.h"
#include "PhantomSynth.h"
#include "../utils/PhantomUtils.h"

/**
 * The audio processor component, containing the important JUCE boilerplate 
 * code for the plugin.
 */
class PhantomAudioProcessor : public AudioProcessor
{
public:
    PhantomAudioProcessor();
    ~PhantomAudioProcessor() override;

    /**
     * Called before playback starts, to let the processor prepare itself (i.e. initialize the synth)
     */
    void prepareToPlay(double sampleRate, int samplesPerBlock) override;

    /**
     * Called after playback has stopped, to let the object free up any resources
     * it no longer needs.
     */
    void releaseResources() override;

#ifndef JucePlugin_PreferredChannelConfigurations
    /**
     * Callback to query if the `AudioProcessor` supports a specific layout.
     */
    bool isBusesLayoutSupported(const BusesLayout &layouts) const override;
#endif

    /**
     * Renders the next block.
     */
    void processBlock(AudioBuffer<float> &, MidiBuffer &) override;

    /**
     * Returns true if the processor has a corresponding editor.
     */
    bool hasEditor() const override;

    /**
     * Creates the processor's GUI.
     */ 
    AudioProcessorEditor *createEditor() override;

    /**
     * Gets the name of the plugin, which is defined in the utilities header file.
     */
    const String getName() const override;

    /**
     * Returns true if the processor wants MIDI messages.
     */
    bool acceptsMidi() const override;

    /**
     * Returns true if the processor produces MIDI messages.
     */
    bool producesMidi() const override;
    
    /**
     * Returns true if this is a MIDI effect plugin and does not process audio.
     */
    bool isMidiEffect() const override;

    /**
     * Returns the length of the processor's tail, in seconds.
     */
    double getTailLengthSeconds() const override;

    /**
     * Returns the number of preset programs the processor supports.
     * NOTE: I designed a cross-platform system so this isn't that relevant.
     */
    int getNumPrograms() override;

    /**
     * Returns the number of the currently active program.
     */
    int getCurrentProgram() override;
    
    /**
     * Called by the host to change the current program.
     */
    void setCurrentProgram(int index) override;
    
    /**
     * Returns the name of a given program.
     */
    const String getProgramName(int index) override;
    
    /**
     * Called by the host to rename a program.
     */
    void changeProgramName(int index, const String &newName) override;

    /**
     * Stores state information (XML data) in a binary format.
     * @param destData The reference to the block of memory to store the data.
     */
    void getStateInformation(MemoryBlock &destData) override;

    /**
     * Retrieves state information from binary data.
     * @param data The block of memory to read from.
     * @param sizeInBytes The size of the block of memory in bytes.
     */
    void setStateInformation(const void *data, int sizeInBytes) override;

    /**
     * Loads plugin state from the XML element.
     * @param xml The XML object to load state data from.
     * @returns The same pointer provided to the method.
     */
    std::unique_ptr<XmlElement> loadStateFromXml(std::unique_ptr<XmlElement> xml);

    /**
     * Saves all plugin metadata data to the XML element (i.e. version, preset name).
     * @param xml The reference to the XML object to save to.
     * @returns The same pointer provided to the method.
     */
    std::unique_ptr<XmlElement> saveMetadataToXml(std::unique_ptr<XmlElement> xml);

    /**
     * Saves all plugin metadata data to the XML element (i.e. version, preset name).
     * @param xml The reference to the XML object to save to.
     * @param presetName The preset name to use.
     * @returns The same pointer provided to the method.
     */
    std::unique_ptr<XmlElement> saveMetadataToXml(std::unique_ptr<XmlElement> xml, String& presetName);

    /**
     * Saves XML data in string format to memory at specified reference.
     * @returns Pointer to the `String` object containing all of the state data.
     */ 
    std::unique_ptr<String> saveStateToText();
    
    /**
     * Loads XML data in string format from memory at specified reference.
     * @param stateStr The reference to the memory of the string-formatted XML data.
     */ 
    void loadStateFromText(const String& stateStr);

    /**
     * Creates or overwrites preset file containing the plugin state data in XML format.
     * @param file The reference to the file to save data to.
     * @returns `true` if the file was saved successfully.
     */
    bool saveStateToFile(File& file);

    /**
     * Creates or overwrites preset file data from XML.
     * @param xml The pointer to the XmlElement to write as a file.
     * @param dir The reference to the directory to save the file.
     * @returns `true` if the file was saved successfully.
     */
    bool saveXmlToFile(std::unique_ptr<XmlElement> xml, File& dir);
    
    /**
     * Loads the plugin state data from a preset file.
     */
    void loadStateFromFile(File& file);

    /**
     * Retrieves the appropriate preset directory for the user, whether it exists or not.
     * @returns The file object representing the preset folder on the user's machine.
     */
    File getPresetDirectory();

    /**
     * Retrieves all of the preset files (*.xml) within the presets folder.
     */
    Array<File> getPresetFiles();

    /**
     * Writes all of the (XML) binary data resources
     * to files the app data directory on the user's computer.
     * CAUTION: Be sure to precompile the binary resources if you've added more stock presets.
     * @returns `true` if the file was saved successfully.
     */
    void writePresetFiles(); 

    /**
     * Re-initializes variables relevant variables for
     * plugin state data.
     */
    void resetState();

    /**
     * Calculates the skew factor given a start, end, and desired center point.
     * @param start The start value to use.
     * @param end The end value to use.
     * @param center The value to skew to the middle.
     */
    float getSkewFactor(float start, float end, float center);

    /**
     * The name of the currently selected preset.
     */
    String m_presetName = String("Init");

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(PhantomAudioProcessor)

    AudioProcessorValueTreeState m_parameters;
    AudioProcessorValueTreeState::ParameterLayout createParameterLayout();

    /**
     * The synthesizer object pointer that renders blocks from the processor.
     */
    std::unique_ptr<PhantomSynth> m_synth;

    /**
     * The amplifier that applies gain to the buffer after the synthesizer 
     * has written its data.
     */
    std::unique_ptr<PhantomAmplifier> m_amp;
};

#endif