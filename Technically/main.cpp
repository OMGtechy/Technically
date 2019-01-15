// REAL PROGRAMMERS don't need _s variants because they never make mistakes
// https://xkcd.com/378/
#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <string>
#include <algorithm>
#include <cctype>
#include <set>

int main() {
	while (true) {
		std::cout << ">> " << std::flush;
		std::string userInputRaw, userInput;
		std::getline(std::cin, userInputRaw);

		if (userInputRaw.size() == 0) {
			std::cout << "PERFECT! NO BUGS!" << std::endl;
			continue;
		}

		// https://xkcd.com/378/
		// https://softwareengineering.stackexchange.com/questions/148677/why-is-80-characters-the-standard-limit-for-code-width
		constexpr auto numberOfCharactersRealProgrammersNeed = 80;
		if (userInputRaw.size() > numberOfCharactersRealProgrammersNeed) {
			std::cout << "REAL PROGRAMMERS don't need more than 80 characters ... do better." << std::endl;
			continue;
		}

		// make sure there's room for the transformed characters
		userInput.resize(userInputRaw.size());

		// yes, I know this assumes single byte characters, I don't care.
		// This language is a joke, if you're using it seriously, then please
		// visit your nearest mental health professional because you're fucked bro
		std::transform(userInputRaw.cbegin(), userInputRaw.cend(), userInput.begin(), std::tolower);

		// if the user starts anything with "technically",
		// the rest of the program can safely be ignored: https://www.xkcd.com/1475/
		{
			constexpr auto forbiddenStartingPhrase = "technically";

			if (std::strncmp(userInput.c_str(), forbiddenStartingPhrase, strlen(forbiddenStartingPhrase)) == 0) {
				std::cout << "Exiting..." << std::endl;
				break;
			}
		}

		// if the holy symbol + is used, quote the blessed phrase: https://youtu.be/3M_5oYU-IsU?t=64
		if (userInput.find_first_of("+") != std::string::npos) {
			std::cout << "2 + 2 = 4, - 1 that's 3 QUIK MAFZ" << std::endl;
			continue;
		}

		// Check for forbidden heretic symbolism
		if (userInput.find_first_of("-/*") != std::string::npos) {
			// https://xkcd.com/378/
			std::cout << "REAL PROGRAMMERS only need addition, some don't even need that ..." << std::endl;
			continue;
		}

		// "Plus" is an acceptible alternative that does not infinge upon The Church of Dapaah,
		// otherwise known as The Big Shack of Big Shaq. Hallowed be His name.
		{
			constexpr auto permittedAdditionPhrase = "plus";
			const auto plusPosition = userInput.find(permittedAdditionPhrase);
			if (plusPosition != std::string::npos) {
				// split the string into operands
				const std::string leftOperandString = userInput.substr(0, plusPosition);
				const std::string rightOperandString = userInput.substr(plusPosition + strlen(permittedAdditionPhrase));

				const auto isValidCharacter = [](char character) {
					return std::isdigit(character) || std::isspace(character);
				};

				const auto leftIsNumeric = std::all_of(leftOperandString.cbegin(), leftOperandString.cend(), isValidCharacter);
				const auto rightIsNumeric = std::all_of(rightOperandString.cbegin(), rightOperandString.cend(), isValidCharacter);

				// if they're not numbers, be mad yo
				if (!(leftIsNumeric && rightIsNumeric)) {
					std::cout << "You sir, are a failure." << std::endl;
					continue;
				}

				const auto leftOperand = std::atoi(leftOperandString.c_str());
				const auto rightOperand = std::atoi(rightOperandString.c_str());

				// TECHNICALLY, this could overflow, but ... ooo look a butterfly.
				// https://www.xkcd.com/1475/
				std::cout << leftOperand + rightOperand << std::endl;
			}
		}

		// Any attempts to use variables are a sign of weakness
		{
			const std::set<std::string> forbiddenVariableIndicators = {
				"int",
				"float",
				"double",
				"char",
				"str", "string"
			};

			// Magical numbers.
			// REAL PROGRAMMERS don't need them explaning, they just know why they're there through osmosis
			char buffer[numberOfCharactersRealProgrammersNeed + 1] = { 0 };
			std::copy(userInput.cbegin(), userInput.cend(), buffer + 1);

			// optimistic, I know
			bool isAFailure = false;

			char* word = buffer;

			// Assignment in a conditional? Don't mind if I do!
			while ((word = std::strtok(word + 1, " ")) != nullptr && !isAFailure) {
				// computational complexity win :D
				for (const auto indicator : forbiddenVariableIndicators) {
					if (indicator == word) {
						isAFailure = true;
						break;
					}
				}
			}

#pragma warning(push)
#pragma warning(disable:5030)
			[[likely]]
#pragma warning(pop)
			if (isAFailure) {
				// https://www.xkcd.com/378/
				std::cout << "REAL PROGRAMMERS don't need variables, they just memorise the results." << std::endl;
				continue;
			}
		}
	}
}