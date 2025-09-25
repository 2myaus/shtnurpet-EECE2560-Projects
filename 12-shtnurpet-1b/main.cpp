// Project 1b Michael Shteynberg Temirlan Nurtayev Daniil Petrov
//
// Main program file containing class definitions for a playable Mastermind

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
} // end constructor

// Counts the number of digits in correct positions between this code and the
// guess code.
// Parameters: guess - the code to compare against
// Returns: number of digits in correct positions
// Assumptions: guess.digit_count <= digit_count
unsigned int code::checkCorrect(code &guess) const
{
    assert(guess.digit_count <= digit_count);

    // Count equal digits at same positions using inner_product
    return std::inner_product(guess.digits.begin(),
                              guess.digits.end(),
                              digits.begin(),
                              0,
                              std::plus<>(),
                              std::equal_to<>());
} // end code::checkCorrect

// Counts the number of unique digits that appear in both codes but are not in
// correct positions. If a digit appears more than once and any instance is
// correct, it counts as 0 incorrect. Otherwise, it counts as 1 incorrect
// regardless of frequency.
// Parameters: guess - the code to compare against
// Returns: number of unique incorrect digits
unsigned int code::checkIncorrect(code &guess) const
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

// Returns: const reference to digits vector
const std::vector<unsigned short> &code::getDigits() const
{
    return digits;
} // end code::getDigits

// Main function that demonstrates the code class functionality by creating a
// random code and testing it with three different guesses.
int main()
{
    // Create a random code with 5 digits in range [0, 7)
    code guessing(5, 7);
    const std::vector<unsigned short> guessing_digits = guessing.getDigits();

    printf("The code: ");
    std::for_each(guessing_digits.begin(),
                  guessing_digits.end(),
                  [&](unsigned short digit) { printf("%i ", digit); });
    printf("\n");

    // Create three test guesses
    code guess1({5, 0, 3, 2, 6});
    code guess2({2, 1, 2, 2, 2});
    code guess3({1, 3, 3, 4, 5});

    // Check each guess for correct and incorrect digits
    unsigned int guess1_correct = guessing.checkCorrect(guess1);
    unsigned int guess1_incorrect = guessing.checkIncorrect(guess1);
    unsigned int guess2_correct = guessing.checkCorrect(guess2);
    unsigned int guess2_incorrect = guessing.checkIncorrect(guess2);
    unsigned int guess3_correct = guessing.checkCorrect(guess3);
    unsigned int guess3_incorrect = guessing.checkIncorrect(guess3);

    // Display results
    printf("Guess 1: (5 0 3 2 6): %i, %i\n", guess1_correct, guess1_incorrect);
    printf("Guess 2: (2 1 2 2 2): %i, %i\n", guess2_correct, guess2_incorrect);
    printf("Guess 3: (1 3 3 4 5): %i, %i\n", guess3_correct, guess3_incorrect);

    return 0;
} // end main
