/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
NewProjectAudioProcessorEditor::NewProjectAudioProcessorEditor (NewProjectAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    button.setClickingTogglesState(true);

    button.onClick = [&]() {  //lambda function to callback everytime a button is clicked
        const auto message = button.getToggleState() ? "Power On" : "Power Off";
        printf(message);
        std::cout << "I've been clicked" << std::endl; 
        audioProcessor.setFilterAudioFactor(button.getToggleState() ? 1 : 0);
        button.setButtonText(message);
    };

    button.setButtonText("Power On");
    addAndMakeVisible(button); //to make UI components visible
    setSize (400, 400);
}

NewProjectAudioProcessorEditor::~NewProjectAudioProcessorEditor()
{

}

//==============================================================================
void NewProjectAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (juce::Colours::white);

    g.setColour (juce::Colours::black);
    g.setFont (15.0f);
    g.drawFittedText ("Filter Plugin", getLocalBounds(), juce::Justification::centred, 1);
}

void NewProjectAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..

    button.setBounds(getWidth() / 2 - 25, getHeight() / 2 - 12, 100, 50);
}