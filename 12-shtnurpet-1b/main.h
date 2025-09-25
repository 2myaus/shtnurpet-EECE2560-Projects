/*

Project 1b Michael Shteynberg Temirlan Nurtayev Daniil Petrov

main.h: Contains function and class prototypes for the classes:
  code
  response
  mastermind

*/

#include <ostream>
#include <vector>

/*!
  Class representing a code with n digits, each in range [0, m)
*/
class code
{
  public:
    /*! Constructor generating random digits in [0, m)*/
    code(unsigned int n, unsigned short m);

    /*! Constructor using given digits */
    code(const std::vector<unsigned short> &digits);

    /*!
      Counts the number of digits in correct positions between this code and the
      guess code.

      Parameters: guess - the code to compare against
      Returns: number of digits in correct positions
      Assumptions: guess.digit_count <= digit_count
    */
    unsigned int checkCorrect(const code &guess) const;

    /*!
      Counts the number of unique digits that appear in both codes but are not
      in correct positions. If a digit appears more than once and any instance
      is correct, it counts as 0 incorrect. Otherwise, it counts as 1 incorrect
      regardless of frequency.

      Parameters: guess - the code to compare against
      Returns: number of unique incorrect digits
      Assumptions: guess.digit_count <= digit_count
    */
    unsigned int checkIncorrect(const code &guess) const;

    /*! Number of digits in this code */
    const unsigned int digit_count;

    /*! Range of each digit [0,m) */
    const unsigned short digit_range;

    /*! Getter function for the digits vector */
    const std::vector<unsigned short> &getDigits() const;

  private:
    /*! Private vector containing the code's digits */
    std::vector<unsigned short> digits;
}; // end code class

/*!
  Class representing the result of comparing two codes
*/
class response
{
  public:
    /*! Constructor that compares two codes */
    response(const code &code1, const code &code2);

    /*! Getter function for the number of correct digits in the response */
    unsigned int getNumCorrect() const;

    /*! Getter function for the number of incorrect digits in the response */
    unsigned int getNumIncorrect() const;

  private:
    const unsigned int num_correct;
    const unsigned int num_incorrect;
};

/*! Equality operator which checks if two responses are identical */
bool operator==(const response &lhs, const response &rhs);

/*! Output operator which writes a response to an output stream */
std::ostream &operator<<(const std::ostream &lhs, const response &rhs);

/*! Output operator which writes a code to an output stream */
std::ostream &operator<<(const std::ostream &lhs, const code &rhs);

/*! Class represening a full game of Mastermind */
class mastermind
{
  public:
    /*! Constructor with default values n=5, m=10 */
    mastermind(unsigned short n = 5, unsigned short m = 10);

    /*! Prints the secret code to stdout */
    void printSecretCode() const;

    /*! Generates a guess code from keyboard input */
    code humanGuess() const;

    /*! generates a comparison response from a guess code */
    response getResponse(code &guess) const;

    /*! Checks if a comparison response solves the game */
    bool isSolved(response &solution) const;

    /* Initializes and plays a game, calling humanGuess() until the game ends */
    void playGame();

  private:
    code secretCode;
};
