#include <vector>

namespace Morse {
	enum class Event {dih, dah, symbolSpace, letterSpace, wordSpace};

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

	std::vector<Event> stringToEvents(std::string str);
	void initialize();
	void terminate();
	ALuint* eventsToBuffer(std::vector<Event>);
	std::string eventsToMorseString(std::vector<Event>);
}
