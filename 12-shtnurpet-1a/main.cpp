// by Daniil Petrov

#include <algorithm>
#include <cassert>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <numeric>
#include <stdint.h>
#include <vector>

class code {
public:
  code(unsigned int n, unsigned int m);
  code(const std::vector<uint8_t> &digits);

  unsigned int checkCorrect(code &guess) const;
  unsigned int checkIncorrect(code &guess) const;

  const unsigned int digit_count;
  const unsigned int digit_range;

  const std::vector<uint8_t> &getDigits() const;

private:
  std::vector<uint8_t> digits;
};

code::code(unsigned int n, unsigned int m)
    : digit_count(n), digit_range(m), digits(digit_count) {
  // n: number of digits in code
  // m: range of each digit [0, m)

  std::srand(std::time({}));
  std::transform(digits.begin(), digits.end(), digits.begin(), [&](uint8_t _) {
    // lambda map func
    return std::rand() % digit_range;
  });
}

code::code(const std::vector<uint8_t> &digits)
    : digit_count(digits.size()),
      digit_range(*std::max_element(digits.begin(), digits.end())),
      digits(digits) {}

unsigned int code::checkCorrect(code &guess) const {
  assert(guess.digit_count <= digit_count);

  // count and return number of equal digits between the two guesses
  return std::inner_product(guess.digits.begin(), guess.digits.end(),
                            digits.begin(), 0, std::plus<>(),
                            std::equal_to<>());
}

unsigned int code::checkIncorrect(code &guess) const {
  // if a digit appears more than once and any is in a correct location,
  // count it incorrect 0 times
  // if a digit appears more than once and is not in a correct location,
  // count it incorrect 1 time

  unsigned int num_incorrect = 0;
  for (unsigned int i = 0; i < digit_count; i++) {
    // if the code has previously contained this digit, skip
    if (std::find(digits.begin(), digits.begin() + i, digits[i]) !=
        digits.begin() + i)
      continue;

    // if the guess doesn't contain this digit, skip
    if (std::find(guess.digits.begin(), guess.digits.end(), digits[i]) ==
        guess.digits.end())
      continue;

    bool any_correct = false;
    // if the guess has this digit correct in any place, skip
    for (unsigned int i2 = 0; i2 < guess.digit_count; i2++) {
      if ((i2 < digit_count) && (digits[i2] == guess.digits[i2]) && (digits[i2] == digits[i]))
        any_correct = true;
    }
    if (any_correct)
      continue;

    num_incorrect++;
  }

  return num_incorrect;
}

const std::vector<uint8_t> &code::getDigits() const { return digits; }

int main() {
  code guessing(5, 7);

  const std::vector<uint8_t> guessing_digits = guessing.getDigits();
  printf("The code: ");
  std::for_each(guessing_digits.begin(), guessing_digits.end(),
                [&](uint8_t digit) { printf("%i ", digit); });
  printf("\n");
  // ((5, 0, 3, 2, 6)
  // (2, 1, 2, 2, 2),
  // (1, 3, 3, 4, 5)).
  code guess1({5, 0, 3, 2, 6});
  code guess2({2, 1, 2, 2, 2});
  code guess3({1, 3, 3, 4, 5});

  unsigned int guess1_correct = guessing.checkCorrect(guess1);
  unsigned int guess1_incorrect = guessing.checkIncorrect(guess1);

  unsigned int guess2_correct = guessing.checkCorrect(guess2);
  unsigned int guess2_incorrect = guessing.checkIncorrect(guess2);

  unsigned int guess3_correct = guessing.checkCorrect(guess3);
  unsigned int guess3_incorrect = guessing.checkIncorrect(guess3);

  printf("Guess 1: (5 0 3 2 6): %i, %i\n", guess1_correct, guess1_incorrect);
  printf("Guess 2: (2 1 2 2 2): %i, %i\n", guess2_correct, guess2_incorrect);
  printf("Guess 3: (1 3 3 4 5): %i, %i\n", guess3_correct, guess3_incorrect);
}
