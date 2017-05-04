#include <iostream>
#include <vector>
#include <map>
#include <AL/alc.h>
#include <AL/al.h>
#include <cmath>
#include <unistd.h>
#include <climits>
#include <algorithm>

#define PI 3.14159265359

enum class MorseEvent {dih, dah, symbolSpace, letterSpace, wordSpace};

std::map<char, std::vector<MorseEvent>> morseCode = {
	{'a', {MorseEvent::dih, MorseEvent::symbolSpace, MorseEvent::dah}},
	{'b', {MorseEvent::dah, MorseEvent::symbolSpace, MorseEvent::dih, MorseEvent::symbolSpace, MorseEvent::dih, MorseEvent::symbolSpace, MorseEvent::dih}},
	{'c', {MorseEvent::dah, MorseEvent::symbolSpace, MorseEvent::dih, MorseEvent::symbolSpace, MorseEvent::dah, MorseEvent::symbolSpace, MorseEvent::dih}},
	{'d', {MorseEvent::dah, MorseEvent::symbolSpace, MorseEvent::dih, MorseEvent::symbolSpace, MorseEvent::dih}},
	{'e', {MorseEvent::dih}},
	{'f', {MorseEvent::dih, MorseEvent::symbolSpace, MorseEvent::dih, MorseEvent::symbolSpace, MorseEvent::dah, MorseEvent::symbolSpace, MorseEvent::dih}},
	{'g', {MorseEvent::dah, MorseEvent::symbolSpace, MorseEvent::dah, MorseEvent::symbolSpace, MorseEvent::dih}},
	{'h', {MorseEvent::dih, MorseEvent::symbolSpace, MorseEvent::dih, MorseEvent::symbolSpace, MorseEvent::dih, MorseEvent::symbolSpace, MorseEvent::dih}},
	{'i', {MorseEvent::dih, MorseEvent::symbolSpace, MorseEvent::dih}},
	{'j', {MorseEvent::dih, MorseEvent::symbolSpace, MorseEvent::dah, MorseEvent::symbolSpace, MorseEvent::dah, MorseEvent::symbolSpace, MorseEvent::dah}},
	{'k', {MorseEvent::dah, MorseEvent::symbolSpace, MorseEvent::dih, MorseEvent::symbolSpace, MorseEvent::dah}},
	{'l', {MorseEvent::dih, MorseEvent::symbolSpace, MorseEvent::dah, MorseEvent::symbolSpace, MorseEvent::dih, MorseEvent::symbolSpace, MorseEvent::dih}},
	{'m', {MorseEvent::dah, MorseEvent::symbolSpace, MorseEvent::dah}},
	{'n', {MorseEvent::dah, MorseEvent::symbolSpace, MorseEvent::dih}},
	{'o', {MorseEvent::dah, MorseEvent::symbolSpace, MorseEvent::dah, MorseEvent::symbolSpace, MorseEvent::dah}},
	{'p', {MorseEvent::dih, MorseEvent::symbolSpace, MorseEvent::dah, MorseEvent::symbolSpace, MorseEvent::dah, MorseEvent::symbolSpace, MorseEvent::dih}},
	{'q', {MorseEvent::dah, MorseEvent::symbolSpace, MorseEvent::dah, MorseEvent::symbolSpace, MorseEvent::dih, MorseEvent::symbolSpace, MorseEvent::dah}},
	{'r', {MorseEvent::dih, MorseEvent::symbolSpace, MorseEvent::dah, MorseEvent::symbolSpace, MorseEvent::dih}},
	{'s', {MorseEvent::dih, MorseEvent::symbolSpace, MorseEvent::dih, MorseEvent::symbolSpace, MorseEvent::dih}},
	{'t', {MorseEvent::dah}},
	{'u', {MorseEvent::dih, MorseEvent::symbolSpace, MorseEvent::dih, MorseEvent::symbolSpace, MorseEvent::dah}},
	{'v', {MorseEvent::dih, MorseEvent::symbolSpace, MorseEvent::dih, MorseEvent::symbolSpace, MorseEvent::dih, MorseEvent::symbolSpace, MorseEvent::dah}},
	{'w', {MorseEvent::dih, MorseEvent::symbolSpace, MorseEvent::dah, MorseEvent::symbolSpace, MorseEvent::dah}},
	{'x', {MorseEvent::dah, MorseEvent::symbolSpace, MorseEvent::dih, MorseEvent::symbolSpace, MorseEvent::dih, MorseEvent::symbolSpace, MorseEvent::dah}},
	{'y', {MorseEvent::dah, MorseEvent::symbolSpace, MorseEvent::dih, MorseEvent::symbolSpace, MorseEvent::dah, MorseEvent::symbolSpace, MorseEvent::dah}},
	{'z', {MorseEvent::dah, MorseEvent::symbolSpace, MorseEvent::dah, MorseEvent::symbolSpace, MorseEvent::dih, MorseEvent::symbolSpace, MorseEvent::dih}},
	{' ', {MorseEvent::wordSpace}}
};

std::vector<MorseEvent> stringToMorseCode(std::string str) {
	std::vector<MorseEvent> result;
	for (char c : str) {
		result.push_back(MorseEvent::letterSpace);
		result.insert(result.end(), morseCode.at(c).begin(), morseCode.at(c).end());
	}

	return result;
}

void init_al() {
    ALCdevice *dev = NULL;
    ALCcontext *ctx = NULL;

    const char *defname = alcGetString(NULL, ALC_DEFAULT_DEVICE_SPECIFIER);
    std::cout << "Default device: " << defname << std::endl;

    dev = alcOpenDevice(defname);
    ctx = alcCreateContext(dev, NULL);
    alcMakeContextCurrent(ctx);
}

void exit_al() {
    ALCdevice *dev = NULL;
    ALCcontext *ctx = NULL;
    ctx = alcGetCurrentContext();
    dev = alcGetContextsDevice(ctx);

    alcMakeContextCurrent(NULL);
    alcDestroyContext(ctx);
    alcCloseDevice(dev);
}

int main() {
	init_al();

	ALuint buffer;
	alGenBuffers(1, &buffer);
	
	while (true) {
	std::string input;
	std::getline(std::cin, input);
	std::for_each(input.begin(), input.end(), [](char& c){c = std::tolower(c);});

	auto output = stringToMorseCode(input);

	std::vector<short> samples;
	double freq = 440;
	double sampleRate = 44100;
	double wpm = 20;
	double dotDuration = 1.2/wpm;
	
	for (auto event : output) {
		double eventDuration;
		
		if (event == MorseEvent::dih || event == MorseEvent::symbolSpace) eventDuration = dotDuration;
		if (event == MorseEvent::dah || event == MorseEvent::letterSpace) eventDuration = 3*dotDuration;
		if (event == MorseEvent::wordSpace) eventDuration = 7*dotDuration;
		
		int bufSize = sampleRate * eventDuration;
		
		if (event == MorseEvent::dih || event==MorseEvent::dah) for (int i = 0; i<bufSize; i++) samples.push_back(SHRT_MAX*std::sin(double(2)*PI*i*freq/sampleRate));
		else for (int i = 0; i<bufSize;i++) samples.push_back(0);
	}

	alBufferData(buffer, AL_FORMAT_MONO16, &samples[0], 2*samples.size(), sampleRate);

	ALuint src = 0;
	alGenSources(1, &src);
	alSourcei(src, AL_BUFFER, buffer);
	alSourcePlay(src);

	}
}
