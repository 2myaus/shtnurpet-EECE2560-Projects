#include <cstdint>
#include <ostream>
#include <vector>

// Represents a code with n digits, each in range [0, m)
class code
{
  public:
    code(unsigned int n, unsigned short m);
    code(const std::vector<unsigned short> &digits);
    unsigned int checkCorrect(code &guess) const;
    unsigned int checkIncorrect(code &guess) const;
    const unsigned int digit_count;   // number of digits in code
    const unsigned short digit_range; // range of each digit [0, m)
    const std::vector<unsigned short> &getDigits() const;

  private:
    std::vector<unsigned short> digits; // the code digits
}; // end code class

// Represents the result of comparing two codes
class response
{
  public:
    response(code &code1, code &code2);
    const unsigned int getNumCorrect();
    const unsigned int getNumIncorrect();

  private:
    const unsigned int num_correct;
    const unsigned int num_incorrect;

    // Equality and output stream operators
    bool operator==(response&other);
    std::ostream &operator<<(std::ostream &out);
};

// Represents a full game of Mastermind
class mastermind
{
  public:
    mastermind(unsigned short n = 5, unsigned short m = 10);
    void printSecretCode();
    code humanGuess();
    response getResponse(code &guess);
    bool isSolved(response &solution);
    void playGame();
  private:
    code secretCode;
};
