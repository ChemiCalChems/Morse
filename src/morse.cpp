#include "morse.hpp"

#define PI 3.14159265359

namespace Morse {
	std::map<char, std::vector<Event>> morseCode = {
		{'a', {Event::dih, Event::symbolSpace, Event::dah}},
		{'b', {Event::dah, Event::symbolSpace, Event::dih, Event::symbolSpace, Event::dih, Event::symbolSpace, Event::dih}},
		{'c', {Event::dah, Event::symbolSpace, Event::dih, Event::symbolSpace, Event::dah, Event::symbolSpace, Event::dih}},
		{'d', {Event::dah, Event::symbolSpace, Event::dih, Event::symbolSpace, Event::dih}},
		{'e', {Event::dih}},
		{'f', {Event::dih, Event::symbolSpace, Event::dih, Event::symbolSpace, Event::dah, Event::symbolSpace, Event::dih}},
		{'g', {Event::dah, Event::symbolSpace, Event::dah, Event::symbolSpace, Event::dih}},
		{'h', {Event::dih, Event::symbolSpace, Event::dih, Event::symbolSpace, Event::dih, Event::symbolSpace, Event::dih}},
		{'i', {Event::dih, Event::symbolSpace, Event::dih}},
		{'j', {Event::dih, Event::symbolSpace, Event::dah, Event::symbolSpace, Event::dah, Event::symbolSpace, Event::dah}},
		{'k', {Event::dah, Event::symbolSpace, Event::dih, Event::symbolSpace, Event::dah}},
		{'l', {Event::dih, Event::symbolSpace, Event::dah, Event::symbolSpace, Event::dih, Event::symbolSpace, Event::dih}},
		{'m', {Event::dah, Event::symbolSpace, Event::dah}},
		{'n', {Event::dah, Event::symbolSpace, Event::dih}},
		{'o', {Event::dah, Event::symbolSpace, Event::dah, Event::symbolSpace, Event::dah}},
		{'p', {Event::dih, Event::symbolSpace, Event::dah, Event::symbolSpace, Event::dah, Event::symbolSpace, Event::dih}},
		{'q', {Event::dah, Event::symbolSpace, Event::dah, Event::symbolSpace, Event::dih, Event::symbolSpace, Event::dah}},
		{'r', {Event::dih, Event::symbolSpace, Event::dah, Event::symbolSpace, Event::dih}},
		{'s', {Event::dih, Event::symbolSpace, Event::dih, Event::symbolSpace, Event::dih}},
		{'t', {Event::dah}},
		{'u', {Event::dih, Event::symbolSpace, Event::dih, Event::symbolSpace, Event::dah}},
		{'v', {Event::dih, Event::symbolSpace, Event::dih, Event::symbolSpace, Event::dih, Event::symbolSpace, Event::dah}},
		{'w', {Event::dih, Event::symbolSpace, Event::dah, Event::symbolSpace, Event::dah}},
		{'x', {Event::dah, Event::symbolSpace, Event::dih, Event::symbolSpace, Event::dih, Event::symbolSpace, Event::dah}},
		{'y', {Event::dah, Event::symbolSpace, Event::dih, Event::symbolSpace, Event::dah, Event::symbolSpace, Event::dah}},
		{'z', {Event::dah, Event::symbolSpace, Event::dah, Event::symbolSpace, Event::dih, Event::symbolSpace, Event::dih}},
		{' ', {Event::wordSpace}},
		{'1', {Event::dih, Event::symbolSpace, Event::dah, Event::symbolSpace, Event::dah, Event::symbolSpace, Event::dah, Event::symbolSpace, Event::dah}},
		{'2', {Event::dih, Event::symbolSpace, Event::dih, Event::symbolSpace, Event::dah, Event::symbolSpace, Event::dah, Event::symbolSpace, Event::dah}},
		{'3', {Event::dih, Event::symbolSpace, Event::dih, Event::symbolSpace, Event::dih, Event::symbolSpace, Event::dah, Event::symbolSpace, Event::dah}},
		{'4', {Event::dih, Event::symbolSpace, Event::dih, Event::symbolSpace, Event::dih, Event::symbolSpace, Event::dih, Event::symbolSpace, Event::dah}},
		{'5', {Event::dih, Event::symbolSpace, Event::dih, Event::symbolSpace, Event::dih, Event::symbolSpace, Event::dih, Event::symbolSpace, Event::dih}},
		{'6', {Event::dah, Event::symbolSpace, Event::dih, Event::symbolSpace, Event::dih, Event::symbolSpace, Event::dih, Event::symbolSpace, Event::dih}},
		{'7', {Event::dah, Event::symbolSpace, Event::dah, Event::symbolSpace, Event::dih, Event::symbolSpace, Event::dih, Event::symbolSpace, Event::dih}},
		{'8', {Event::dah, Event::symbolSpace, Event::dah, Event::symbolSpace, Event::dah, Event::symbolSpace, Event::dih, Event::symbolSpace, Event::dih}},
		{'9', {Event::dah, Event::symbolSpace, Event::dah, Event::symbolSpace, Event::dah, Event::symbolSpace, Event::dah, Event::symbolSpace, Event::dih}},
		{'0', {Event::dah, Event::symbolSpace, Event::dah, Event::symbolSpace, Event::dah, Event::symbolSpace, Event::dah, Event::symbolSpace, Event::dah}}
	};
	
	std::vector<Event> textToEvents(std::string str) {
		std::vector<Event> result;
		for (int i = 0; i<str.size(); i++) {
			char c = str.at(i);
			
   			if(!result.empty()) {
				if (str.at(i-1) != ' ' && c != ' ') result.push_back(Event::letterSpace);
			}
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

		alBufferData(*buffer, AL_FORMAT_MONO16, &samples[0], sizeof(short)*samples.size(), sampleRate);
 		return buffer;
	}

	std::string eventsToMorse(std::vector<Event> events) {
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
				result += "/";
				break;
			}
		}

		return result;
	}

	std::string eventsToText(std::vector<Event> events) {
		std::string result;
	
		std::vector<Event> currentLetter;
		for (auto event : events) {
			if (event == Event::letterSpace || event == Event::wordSpace) {
				std::for_each(morseCode.begin(), morseCode.end(), [event, currentLetter, &result](std::pair<char, std::vector<Event>> p) {
						if (p.second == currentLetter) result += p.first;
					});
				if (event == Event::wordSpace) {result += " ";}
				currentLetter.clear();
			} else {
				currentLetter.push_back(event);
			}
		}
		
		std::for_each(morseCode.begin(), morseCode.end(), [currentLetter, &result](std::pair<char, std::vector<Event>> p) {
				if (p.second == currentLetter) result += p.first;
			});
			
		return result;
	}

	std::vector<Event> morseToEvents(std::string morse) {
		std::vector<Event> result;

		for (char c : morse) {
			switch (c) {
			case '.': if (!result.empty() && (result.back() == Event::dih || result.back() == Event::dah)) result.push_back(Event::symbolSpace); result.push_back(Event::dih); break;
			case '-': if (!result.empty() && (result.back() == Event::dih || result.back() == Event::dah)) result.push_back(Event::symbolSpace); result.push_back(Event::dah); break;
			case ' ': result.push_back(Event::letterSpace); break;
			case '/': result.push_back(Event::wordSpace); break;
			}
		}

		return result;
	}
}
