/*
  ==============================================================================

    NotchFilter.cpp
    Created: 24 Jan 2024 4:58:34pm
    Author:  dhira

  ==============================================================================
*/

#include "NotchFilter.h"

NotchFilter::NotchFilter() {
    factor = 1;
}

NotchFilter::~NotchFilter() {
}

void NotchFilter::setGain(float dbGain) {
    G = dbGain;
}

void NotchFilter::setCutoff(float fHz) {
    Wc = 2 * fHz / sampleRate;
}

void NotchFilter::setBandwidth(float bHz) {
    Wb = 2 * bHz / sampleRate; //Wb is in radians, so converting it to radians
}

void NotchFilter::setSampleRate(float sampleRate) {
    this->sampleRate = sampleRate; 
}

void NotchFilter::updateCoefficients() {
    float V0 = powf(10, G / 20);
    H0 = V0 - 1.0f;
    const float pi = juce::MathConstants<float>::pi;
    c = (std::tan(pi * Wb / 2.0f) - (G >= 0 ? 1 : V0)) / (std::tan(pi * Wb / 2.0f) + (G >= 0 ? 1 : V0));
    d = -std::cos(juce::MathConstants<float>::pi * Wc);
}

void NotchFilter::processBlock(juce::AudioBuffer<float>& buffer) {
    const int numChannels = buffer.getNumChannels();
    const int numSamples = buffer.getNumSamples();

    xh0.resize(buffer.getNumChannels(), 0.0f);
    xh1.resize(buffer.getNumChannels(), 0.0f);

    for (auto channel = 0; channel < numChannels; ++channel) {
        float* samplePointer = buffer.getWritePointer(channel);
        for (auto i = 0; i < numSamples; ++i) {
            const float inputSample = samplePointer[i];
            samplePointer[i] = processSample(inputSample, channel);
            
        }
    }
}

float NotchFilter::processSample(float input, int channel) {
    return input * factor;
}

void NotchFilter::setAudioFactor(float factor) {
    this->factor = factor;
}
