/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
A1StarterAudioProcessorEditor::A1StarterAudioProcessorEditor (A1StarterAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (200, 200);
    // these define the parameters of our slider object
    arpLabel.setText("Speed:", NotificationType::dontSendNotification);
    arpLabel.setJustificationType(juce::Justification::centredRight);
    arpLabel.attachToComponent(&arpSlider, true);
    addAndMakeVisible(speedLabel);

    arpSlider.setSliderStyle (juce::Slider::SliderStyle::LinearHorizontal);
    arpSlider.setRange (0.0, 1.0, 0.05);
    arpSlider.setTextBoxStyle (juce::Slider::TextEntryBoxPosition::NoTextBox, true, 90, 20);
    arpSlider.setPopupDisplayEnabled (true, true, this);
    arpSlider.setValue(0.5);
    addAndMakeVisible (&speedSlider);
    arpSlider.onValueChange = [this] {updateSpeed(); };

    durationLabel.setText("1st note Duration:", NotificationType::dontSendNotification);
    durationLabel.setJustificationType(juce::Justification::centredRight);
    durationLabel.attachToComponent(&durationSlider, true);
    addAndMakeVisible(durationLabel);

    durationSlider.setSliderStyle(juce::Slider::SliderStyle::LinearHorizontal);
    durationSlider.setRange(0.25, 4.0, 0.25);
    durationSlider.setTextBoxStyle(juce::Slider::TextEntryBoxPosition::NoTextBox, true, 90, 20);
    durationSlider.setPopupDisplayEnabled(true, true, this);
    durationSlider.setValue(1.0);
    addAndMakeVisible(&durationSlider);
    durationSlider.onValueChange = [this] {updateDuration(); };

    ascendingToggle.setToggleState(true, NotificationType::dontSendNotification);
    addAndMakeVisible(ascendingToggle);
    ascendingToggle.onClick = [this] {updateAscending(); };

    sequenceLabel.setText("Sequence:", NotificationType::dontSendNotification);
    addAndMakeVisible(sequenceLabel);

    linearToggle.setToggleState(true, NotificationType::dontSendNotification);
    addAndMakeVisible(linearToggle);
    linearToggle.onClick = [this] {updateSequence(); };
    linearToggle.setRadioGroupId(1);

    randomizeToggle.setToggleState(false, NotificationType::dontSendNotification);
    addAndMakeVisible(randomizeToggle);
    randomizeToggle.onClick = [this] {updateSequence(); };
    randomizeToggle.setRadioGroupId(1);

    retakeToggle.setToggleState(false, NotificationType::dontSendNotification);
    addAndMakeVisible(retakeToggle);
    retakeToggle.onClick = [this] {updateSequence(); };
    retakeToggle.setRadioGroupId(1);

    addAndMakeVisible(octaveCombo);
    octaveCombo.addItem("1 Octave", 1);
    octaveCombo.addItem("2 Octaves", 2);
    octaveCombo.addItem("3 Octaves", 3);
    octaveCombo.onChange = [this] {updateOctaves(); };
    octaveCombo.setSelectedId(1);

    // this function adds the slider to the editor
    addAndMakeVisible (&arpSlider);
    arpSlider.addListener (this);
}

A1StarterAudioProcessorEditor::~A1StarterAudioProcessorEditor()
{
}

//==============================================================================
void A1StarterAudioProcessorEditor::paint (juce::Graphics& g)
{
   // fill the whole window white
    g.fillAll (juce::Colours::white);

    // set the current drawing colour to black
    g.setColour (juce::Colours::black);

    // set the font size and draw text to the screen
    g.setFont (15.0f);

    g.drawFittedText ("Arpeggiator", 0, 0, getWidth(), 30, juce::Justification::centred, 1);
}

void A1StarterAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
    // sets the position and size of the slider with arguments (x, y, width, height)
    arpSlider.setBounds (40, 30, 20, getHeight() - 60);
    durationSlider.setBounds(40, 30, 20, getHeight() - 60);
    ascendingToggle.setBounds(130, 40, 100, 20);
    octaveCombo.setBounds(130, 110, 100, 20);
    sequenceLabel.setBounds(10, 40, 100, 20);
    linearToggle.setBounds(10, 60, 100, 20);
    randomizeToggle.setBounds(10, 80, 100, 20);
    retakeToggle.setBounds(10, 100, 100, 20);
}
void A1StarterAudioProcessorEditor::updateDuration(){
    audioProcessor.duration = durationSlider.getValue();
}
void A1StarterAudioProcessorEditor::updateSpeed(){
    audioProcessor.speed = arpSlider.getValue()
}
void A1StarterAudioProcessorEditor::updateAscending(){
    audioProcessor.ascending = ascendingToggle.getToggleState();
}
void A1StarterAudioProcessorEditor::updateSequence(){
    audioProcessor.randomize = randomizeToggle.getToggleState();
    audioProcessor.retake = retakeToggle.getToggleState();
}
void A1StarterAudioProcessorEditor::sliderValueChanged (juce::Slider* slider)
{
    audioProcessor.arpSpeed = arpSlider.getValue();
}
