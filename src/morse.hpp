#ifndef MORSE_MORSE_HPP
#define MORSE_MORSE_HPP

#include <iostream>
#include <vector>
#include <map>
#include "alc.h"
#include "al.h"
#include <cmath>
#include <unistd.h>
#include <climits>
#include <algorithm>
#include <vector>

namespace Morse {
	enum class Event {dih, dah, symbolSpace, letterSpace, wordSpace};
	extern std::map<char, std::vector<Event>> morseCode;

	void initialize();
	void terminate();

	std::vector<Event> textToEvents(std::string str);
	std::vector<Event> morseToEvents(std::string str);
	
	std::string eventsToMorse(std::vector<Event>);
	std::string eventsToText(std::vector<Event>);

	ALuint* eventsToBuffer(std::vector<Event>);
	std::vector<Event> bufferToEvents(ALuint* buffer);
}

#endif
