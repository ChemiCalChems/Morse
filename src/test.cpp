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
