#include <cmath>
#include <fstream>
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

    const std::string fileName = "Trianglewave.wav";

    const int sampleRate = 44100;
    const int channelSize = 1;
    const int dataSize = 0;
    
    const int bitsPerByte = 8;
    const int byteRate = sampleRate * channelSize * (bitDepth / bitsPerByte);

    // How many bytes are in a single sample frame? 
    // A sample frame means all channels (in mono: L, in stereo: L + R) at a single point in time.
    const int blockAlign = channelSize * (bitDepth / bitsPerByte);

    std::ofstream file(fileName, std::ios::binary);

    // Every RIFF file starts with these 4 ASCII letters.
    file.write("RIFF", 4);

    // The next 4 bytes are the size of the entire file.
    // That makes up 8 bytes in total. Then, there must be at least the word "WAVE" following it.
    // Also, there must be at least a single (in this case empty) chunk.
    // That makes up a total of 4 ("RIFF") + 4 (chunkSize) + 4 ("WAVE") + 24 ("fmt ") + 8 ("data") + 0 (dataSize) bytes.
    const int chunkSize = 4 + 4 + 24 + 8 + dataSize;

    return 0;
}