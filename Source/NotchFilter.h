/*
  ==============================================================================

    NotchFilter.h
    Created: 24 Jan 2024 4:58:34pm
    Author:  dhira

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>


class NotchFilter {
public:
    NotchFilter();
    ~NotchFilter();

    void setGain(float dbGain);
    void setCutoff(float fHz);
    void setBandwidth(float bHz);
    void setSampleRate(float sampleRate);
    void updateCoefficients();
    void processBlock(juce::AudioBuffer<float>& buffer);
    float processSample(float input, int channel);
    void setAudioFactor(float factor);
private:
       //filter coefficints and params

    float G, Wc, Wb, H0, c, d; 
    //   gain, cutoff freq, bandwidth, coefficient of filger (h, c, d)
    float sampleRate;
    float cutoffFrequency;

    std::vector<float> xh0; //xh(n-2)
    std::vector<float> xh1; //xh(n-1)

    float factor;
 
    //state variables, used for getting sample values for current, and before 

};