#include "console.hpp"
#include <regex>

namespace Morse {
	void console(std::string command) {
		//TODO: say, parse, print
		std::regex playregex ("^\\s*play\\s+([\\w\\s]+)\\s*$");
		std::regex parseregex ("^\\s*parse\\s+([/.\\s\\-]+)\\s*$");
		std::regex printregex ("^\\s*print\\s+([\\w\\s]+)\\s*$");
			
		while (true) {
			std::cout << ">>> ";
			std::string input;
			std::getline(std::cin, input);

			std::smatch m;
			if (std::regex_match(input, m, playregex)) {
				auto buf = eventsToBuffer(textToEvents(m[1]));

				ALuint src;
				alGenSources(1, &src);
				alSourcei(src, AL_BUFFER, *buf);
				alSourcePlay(src);
			}
			if (std::regex_match(input, m, parseregex)) {
				std::cout << eventsToText(morseToEvents(m[1])) << std::endl;
			}
			if (std::regex_match(input, m, printregex)) {
				std::cout << eventsToMorse(textToEvents(m[1])) << std::endl;
			}
			if (std::regex_match(input, m, std::regex("^\\s*exit\\s*"))) {
				std::cout << "closing console..." << std::endl;
				return;
			}
		}
			
	}
}
