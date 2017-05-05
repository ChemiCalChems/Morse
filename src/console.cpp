#include "console.hpp"
#include <regex>

namespace Morse {
	void console(std::string command) {
		//TODO: say, parse, print
		std::regex sayregex ("\\s*say\\s+(\\w+)");
		
		while(true) {
			std::string input;
			std::getline(std::cin, input);

			std::smatch m;
			if(std::regex_match(input, m, sayregex)) {
				auto buf = eventsToBuffer(stringToEvents(m[1]));

				ALuint src;
				alGenSources(1, &src);
				alSourcei(src, AL_BUFFER, *buf);
				alSourcePlay(src);
			}
		}
	}
}
