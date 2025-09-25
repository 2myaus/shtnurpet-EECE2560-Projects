/*

Project 1b Michael Shteynberg Temirlan Nurtayev Daniil Petrov

main.cpp: Contains function definitions for the classes:
  code
  response
  mastermind

*/

#include "main.h"

#include <algorithm>
#include <cassert>
#include <iostream>
#include <numeric>
#include <random>
#include <vector>

// Constructor that creates a random code
// Parameters: n - number of digits, m - range of each digit [0, m)
code::code(unsigned int n, unsigned short m)
    : digit_count(n), digit_range(m), digits(digit_count)
{
    // set up random device / engine / distrubution
    std::random_device rnd_device;
    std::mt19937 engine{rnd_device()};
    std::uniform_int_distribution<int> dist{0, m - 1};

    // Fill digits vector with random digits
    std::generate(digits.begin(), digits.end(), [&]() { return dist(engine); });
} // end code::code

// Constructor that creates a code from a given vector of digits.
// Parameters: digits - vector containing the code digits
code::code(const std::vector<unsigned short> &digits)
    : digit_count(digits.size()),
      digit_range(*std::max_element(digits.begin(), digits.end())),
      digits(digits)
{
}

// Counts the number of identical digits appearing in the same location between
// the guess and the code
unsigned int code::checkCorrect(const code &guess) const
{
    // Assert that the guess is no longer than the code
    assert(guess.digit_count <= digit_count);

    // Count equal digits at same positions using inner_product
    return std::inner_product(guess.digits.begin(),
                              guess.digits.end(),
                              digits.begin(),
                              0,
                              std::plus<>(),
                              std::equal_to<>());
} // end code::checkCorrect

// Counts the number of identical digits appearing in the different locations
// between the guess and the code, counting each digit only once
unsigned int code::checkIncorrect(const code &guess) const
{
    unsigned int num_incorrect = 0;

    for (unsigned int i = 0; i < digit_count; i++)
    {
        // Skip if this digit was already processed (appears earlier)
        if (std::find(digits.begin(), digits.begin() + i, digits[i]) !=
            digits.begin() + i)
            continue;

        // Skip if the guess doesn't contain this digit
        if (std::find(guess.digits.begin(), guess.digits.end(), digits[i]) ==
            guess.digits.end())
            continue;

        bool any_correct = false;

        // Check if this digit is correct in any position
        for (unsigned int i2 = 0; i2 < guess.digit_count; i2++)
        {
            if ((i2 < digit_count) && (digits[i2] == guess.digits[i2]) &&
                (digits[i2] == digits[i]))
                any_correct = true;
        } // end for

        if (any_correct)
            continue;

        num_incorrect++;
    } // end for

    return num_incorrect;
} // end code::checkIncorrect

// Getter function for code::digits
const std::vector<unsigned short> &code::getDigits() const
{
    return digits;
}

/*! Constructor that compares two codes */
response::response(const code &code1, const code &code2)
    : num_correct(code1.checkCorrect(code2)),
      num_incorrect(code1.checkIncorrect(code2))
{
}

/*! Getter function for the number of correct digits in the response */
unsigned int response::getNumCorrect() const
{
    return num_correct;
}

/*! Getter function for the number of incorrect digits in the response */
unsigned int response::getNumIncorrect() const
{
    return num_incorrect;
}

/*! Equality operator which checks if two responses are identical */
bool operator==(const response &lhs, const response &rhs)
{
    return (lhs.getNumCorrect() == rhs.getNumCorrect()) &&
           (lhs.getNumIncorrect() == rhs.getNumIncorrect());
}

/*! Output operator which writes the response to an output stream */
std::ostream &operator<<(std::ostream &lhs, const response &rhs)
{
    // TODO
}

/*! Output operator which writes a code to an output stream */
std::ostream &operator<<(std::ostream &lhs, const code &rhs){
    // TODO
}

/*! Constructor with default values n=5, m=10 declared in main.h */
mastermind::mastermind(unsigned short n, unsigned short m) : secretCode(n, m)
{
}

/*! Prints the secret code to stdout */
void mastermind::printSecretCode() const
{
    std::cout << "Secret code: " << secretCode << std::endl;
}

/*! Generates a guess code from keyboard input */
code mastermind::humanGuess() const
{
    // TODO
}

/*! generates a comparison response from a guess code */
response mastermind::getResponse(code &guess) const
{
    return response(secretCode, guess);
}

/*! Checks if a comparison response solves the game */
bool mastermind::isSolved(response &solution) const
{
    return (solution == response(secretCode, secretCode));
}

/* Initializes and plays a game, calling humanGuess() until the game ends */
void mastermind::playGame()
{
    // TODO
}

// Main function that demonstrates the code class functionality by creating a
// random code and testing it with three different guesses.
int main()
{
    // TODO

    return 0;
} // end main
