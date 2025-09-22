// Project 1a Michael Shteynberg Temirlan Nurtayev Daniil Petrov
//
// Main program file containing the code class implementation for Project Mastermind

#include <algorithm>
#include <cassert>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <numeric>
#include <stdint.h>
#include <vector>

class code
// Represents a code with n digits, each in range [0, m)
{
   public:
      code(unsigned int n, unsigned int m);
      code(const std::vector<uint8_t> &digits);
      unsigned int checkCorrect(code &guess) const;
      unsigned int checkIncorrect(code &guess) const;
      const unsigned int digit_count;      // number of digits in code
      const unsigned int digit_range;      // range of each digit [0, m)
      const std::vector<uint8_t> &getDigits() const;
      
   private:
      std::vector<uint8_t> digits;         // the code digits
}; // end code class

code::code(unsigned int n, unsigned int m)
    : digit_count(n), digit_range(m), digits(digit_count)
// Constructor that creates a random code with n digits in range [0, m).
// Parameters: n - number of digits in code
//            m - range of each digit [0, m)
{
   std::srand(std::time({}));
   
   // Generate random digits using transform with lambda function
   std::transform(digits.begin(), digits.end(), digits.begin(), 
                  [&](uint8_t _) 
                  {
                     return std::rand() % digit_range;
                  });
} // end constructor

code::code(const std::vector<uint8_t> &digits)
    : digit_count(digits.size()),
      digit_range(*std::max_element(digits.begin(), digits.end())),
      digits(digits)
// Constructor that creates a code from a given vector of digits.
// Parameters: digits - vector containing the code digits
{
} // end constructor

unsigned int code::checkCorrect(code &guess) const
// Counts and returns the number of digits in correct positions between
// this code and the guess code.
// Parameters: guess - the code to compare against
// Returns: number of digits in correct positions
// Assumptions: guess.digit_count <= digit_count
{
   assert(guess.digit_count <= digit_count);
   
   // Count equal digits at same positions using inner_product
   return std::inner_product(guess.digits.begin(), guess.digits.end(),
                            digits.begin(), 0, std::plus<>(),
                            std::equal_to<>());
} // end checkCorrect

unsigned int code::checkIncorrect(code &guess) const
// Counts the number of unique digits that appear in both codes but are
// not in correct positions. If a digit appears more than once and any
// instance is correct, it counts as 0 incorrect. Otherwise, it counts
// as 1 incorrect regardless of frequency.
// Parameters: guess - the code to compare against
// Returns: number of unique incorrect digits
{
   unsigned int num_incorrect = 0;
   
   for (unsigned int i = 0; i < digit_count; i++)
   {
      // Skip if this digit was already processed (appears earlier)
      if (std::find(digits.begin(), digits.begin() + i, digits[i]) != 
          digits.begin() + i)
         continue;
      
      // Skip if the guess doesn't contain this digit
      if (std::find(guess.digits.begin(), guess.digits.end(), 
                    digits[i]) == guess.digits.end())
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
} // end checkIncorrect

const std::vector<uint8_t> &code::getDigits() const
// Returns a const reference to the code's digits vector.
// Returns: const reference to digits vector
{
   return digits;
} // end getDigits

int main()
// Main function that demonstrates the code class functionality by
// creating a random code and testing it with three different guesses.
{
   // Create a random code with 5 digits in range [0, 7)
   code guessing(5, 7);
   const std::vector<uint8_t> guessing_digits = guessing.getDigits();
   
   printf("The code: ");
   std::for_each(guessing_digits.begin(), guessing_digits.end(),
                 [&](uint8_t digit) 
                 { 
                    printf("%i ", digit); 
                 });
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
   printf("Guess 1: (5 0 3 2 6): %i, %i\n", guess1_correct, 
          guess1_incorrect);
   printf("Guess 2: (2 1 2 2 2): %i, %i\n", guess2_correct, 
          guess2_incorrect);
   printf("Guess 3: (1 3 3 4 5): %i, %i\n", guess3_correct, 
          guess3_incorrect);
   
   return 0;
} // end main
