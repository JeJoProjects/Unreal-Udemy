#include <iostream>
#include <ctime>
#include <cstdlib>

void playGame(int& levelDifficulty, const int maxDifficulty) noexcept
{
	std::cout << "\n\nYou are a secret agent breaking in to a level " << levelDifficulty;
	std::cout << " secure server room....\nEnter the correct code to continue...\n \n";

	const int codeA{ std::rand() % levelDifficulty + levelDifficulty };
	const int codeB{ std::rand() % levelDifficulty + levelDifficulty };
	const int codeC{ std::rand() % levelDifficulty + levelDifficulty };

	const int codeSum{ codeA + codeB + codeC };
	const int codeProduct{ codeA * codeB * codeC };

	// print the code sum and code product to the terminal
	std::cout << "+ There are 3 numbers in the code";
	std::cout << "\n+ The codes add-up to: " << codeSum;
	std::cout << "\n+ The codes multiplies to: " << codeProduct << "\n";

	// store player guess
	int guessA{}, guessB{}, guessC{};
	std::cin >> guessA >> guessB >> guessC;

	const int guessSum{ guessA + guessB + guessC };
	const int guessProduct{ guessA * guessB * guessC };

	if (codeSum != guessSum || codeProduct != guessProduct)
	{
		std::cout << "\nYou lost!\n";
		return;
	}
	std::cout << "\nYou won!\n";
	// level incrementing and validating the completeness
	++levelDifficulty <= maxDifficulty
		? std::cout << "You are now entering to the " << levelDifficulty << "th level\n"
		: std::cout << "\n*** Great work agent! You got all the files! Now get out of there! ***\n";
}

int main()
{
	// create new random sequence based on time of day
	std::srand(std::time(nullptr));

	int levelDifficulty{ 1 };
	const int maxDifficulty{ 5 };

	// Loop game until all levels completed
	while (levelDifficulty <= 5)
	{
		::playGame(levelDifficulty, maxDifficulty);
		std::cin.clear();  // clears any errors
		std::cin.ignore(); // discards the buffer
	}
	return 0;
}

