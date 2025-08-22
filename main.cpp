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

    for(int sampleIndex = 0; sampleIndex < numberOfSamples / 8; sampleIndex++) {
        audioSamples[sampleIndex * 8] = - maximumAmplitude;
        audioSamples[sampleIndex * 8 + 1] = - maximumAmplitude / 2;
        audioSamples[sampleIndex * 8 + 2] = 0;
        audioSamples[sampleIndex * 8 + 3] = maximumAmplitude / 2;
        audioSamples[sampleIndex * 8 + 4] = maximumAmplitude;
        audioSamples[sampleIndex * 8 + 5] = maximumAmplitude / 2;
        audioSamples[sampleIndex * 8 + 6] = 0;
        audioSamples[sampleIndex * 8 + 7] = - maximumAmplitude / 2;
    }

    for(int sampleIndex = 0; sampleIndex < numberOfSamples; sampleIndex++) {
        // std::cout << audioSamples[sampleIndex] << std::endl;
    }

    const std::string fileName = "Trianglewave.wav";

    const int sampleRate = 44100;
    const int channelSize = 1;
    const int pcmAudioFormat = 1;
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

    // A variable lives in memory. &chunkSize gives the address of the variable chunkSize.
    const int* chunkSizeMemoryAddress = &chunkSize;
    const char* chunkSizeMemoryAddressAsChar = reinterpret_cast<const char*>(chunkSizeMemoryAddress);

    std::cout << "The address of the chunkSize variable is " << chunkSizeMemoryAddress << "." << std::endl;

    // Copy the raw (4) bytes of the chunkSize variable into the file so the RIFF header is complete.
    file.write(chunkSizeMemoryAddressAsChar, 4);
    file.write("WAVE", 4);

    file.write("fmt ", 4);

    // This chunk has a fixed value of 16 bytes.
    const int fmtChunkSize = 16;

    // Copy the raw (4) bytes of the fmtChunkSize variable into the file.
    const int* fmtChunkSizeMemoryAddress = &fmtChunkSize;
    const char* fmtChunkSizeMemoryAddressAsChar = reinterpret_cast<const char*>(fmtChunkSizeMemoryAddress);

    file.write(fmtChunkSizeMemoryAddressAsChar, 4);
    file.write(reinterpret_cast<const char*>(&pcmAudioFormat), 2);
    file.write(reinterpret_cast<const char*>(&channelSize), 2);
    file.write(reinterpret_cast<const char*>(&sampleRate), 4);
    file.write(reinterpret_cast<const char*>(&byteRate), 4);
    file.write(reinterpret_cast<const char*>(&blockAlign), 2);
    file.write(reinterpret_cast<const char*>(&bitDepth), 2);

    // Data subchunk
    file.write("data", 4);

    const int dataChunkSize = numberOfSamples * blockAlign;
    file.write(reinterpret_cast<const char*>(&dataChunkSize), 4);

    for(int sampleIndex = 0; sampleIndex < numberOfSamples; sampleIndex++) {
        const char* sampleMemoryAddress = reinterpret_cast<const char*>(&audioSamples[sampleIndex]);

        file.write(sampleMemoryAddress, bitDepth);
    }

    return 0;
}