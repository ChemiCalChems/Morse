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

	std::vector<Event> stringToEvents(std::string str);
	void initialize();
	void terminate();
	ALuint* eventsToBuffer(std::vector<Event>);
	std::string eventsToMorseString(std::vector<Event>);
}

#endif
