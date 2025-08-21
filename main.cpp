#include <cmath>
#include <iostream>

int main() {
    // The bit depth determines the values the sample can take. 
    // In this case, I use 16-bit audio which has a range of -32768 to 32767.
    // I want to create a simple triangle wave, so I use the bit rate four times.
    const int bitDepth = 16;
    const int amplitudeRange = std::pow(2, bitDepth);
    const int maximumAmplitude = amplitudeRange / 2;
    const int numberOfSamples = amplitudeRange * 2;

    int audioSamples[numberOfSamples];

    std::cout << "Generating audio samples..." << std::endl;

    for(int sampleIndex = 0; sampleIndex < maximumAmplitude; sampleIndex++) {
        audioSamples[sampleIndex] = sampleIndex;
    }

    for(int sampleIndex = maximumAmplitude; sampleIndex < maximumAmplitude * 2; sampleIndex++) {
        audioSamples[sampleIndex] = maximumAmplitude - (sampleIndex - maximumAmplitude);
    }

    for(int sampleIndex = maximumAmplitude * 2; sampleIndex < maximumAmplitude * 3; sampleIndex++) {
        audioSamples[sampleIndex] = maximumAmplitude * 2 - sampleIndex;
    }

    for(int sampleIndex = maximumAmplitude * 3; sampleIndex < maximumAmplitude * 4; sampleIndex++) {
        audioSamples[sampleIndex] = sampleIndex - maximumAmplitude * 4;
    }

    for(int sampleIndex = 0; sampleIndex < numberOfSamples; sampleIndex++) {
        std::cout << audioSamples[sampleIndex] << std::endl;
    }

    return 0;
}