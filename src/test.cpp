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
#include "console.hpp"

int main() {
	Morse::initialize();

	Morse::console();
	
	Morse::terminate();
}
