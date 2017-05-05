#include <iostream>
#include <vector>
#include <map>
#include "alc.h"
#include "al.h"
#include <cmath>
#include <unistd.h>
#include <climits>
#include <algorithm>
#include "morse.hpp"

#define PI 3.14159265359

namespace Morse {
	std::vector<Event> stringToEvents(std::string str) {
		std::vector<Event> result;
		for (char c : str) {
			result.push_back(Event::letterSpace);
			result.insert(result.end(), morseCode.at(c).begin(), morseCode.at(c).end());
		}

		return result;
	}

	void initialize() {
		ALCdevice *dev = NULL;
		ALCcontext *ctx = NULL;

		const char *defname = alcGetString(NULL, ALC_DEFAULT_DEVICE_SPECIFIER);
		std::cout << "Default device: " << defname << std::endl;

		dev = alcOpenDevice(defname);
		ctx = alcCreateContext(dev, NULL);
		alcMakeContextCurrent(ctx);
	}

	void terminate() {
		ALCdevice *dev = NULL;
		ALCcontext *ctx = NULL;
		ctx = alcGetCurrentContext();
		dev = alcGetContextsDevice(ctx);

		alcMakeContextCurrent(NULL);
		alcDestroyContext(ctx);
		alcCloseDevice(dev);
	}

	ALuint* eventsToBuffer(std::vector<Event> events) {
		std::vector<short> samples;
		double freq = 600;
		double sampleRate = 44100;
		double wpm = 15;
		double dotDuration = 1.2/wpm;
	
		for (auto event : events) {
			double eventDuration;
			switch (event) {
			case Event::dih:
			case Event::symbolSpace:
				eventDuration = dotDuration;
				break;
			case Event::dah:
			case Event::letterSpace:
				eventDuration = 3*dotDuration;
				break;
			case Event::wordSpace:
				eventDuration = 7*dotDuration;
				break;
			default:
				throw new std::runtime_error("unhandled event type!");
			}
		    
			int bufSize = sampleRate * eventDuration;
		
			if (event == Event::dih || event==Event::dah) for (int i = 0; i<bufSize; i++) samples.push_back(SHRT_MAX*std::sin(double(2)*PI*i*freq/sampleRate));
			else for (int i = 0; i<bufSize;i++) samples.push_back(0);
		}

		ALuint* buffer = new ALuint;
		alGenBuffers(1, buffer);

		alBufferData(*buffer, AL_FORMAT_MONO16, &samples[0], 2*samples.size(), sampleRate);
 		return buffer;
	}

	std::string eventsToMorseString (std::vector<Event> events) {
		std::string result;

		for (auto event : events) {
			switch(event) {
			case Event::dih:
				result += ".";
				break;
			case Event::dah:
				result += "-";
				break;
			case Event::letterSpace:
				result += " ";
				break;
			case Event::wordSpace:
				result += " / ";
				break;
			}
		}

		return result;
	}
}

int main() {
	Morse::initialize();
	
	while (true) {
		std::string input;
		std::getline(std::cin, input);
		std::for_each(input.begin(), input.end(), [](char& c){c = std::tolower(c);});

		auto output = Morse::stringToEvents(input);
		auto buf = Morse::eventsToBuffer(output);
		
		std::cout << Morse::eventsToMorseString(output);
		
		ALuint src;
		alGenSources(1, &src);
		alSourcei(src, AL_BUFFER, *buf);
		alSourcePlay(src);
	}

	Morse::terminate();
}
