/*

Project 2a Michael Shteynberg Temirlan Nurtayev Daniil Petrov

main.h: Contains function and class prototypes for the classes:
  card
  deck

*/

#include "d_node.h"
#include <ostream>

/*!
  Enum type representing the suit of a card
*/
enum card_suit
{
    SUIT_CLUB,
    SUIT_DIAMOND,
    SUIT_HEART,
    SUIT_SPADE
};

/*!
  Enum type representing the face vaue of a card
*/
enum card_value
{
    CARDVAL_ACE,
    CARDVAL_2,
    CARDVAL_3,
    CARDVAL_4,
    CARDVAL_5,
    CARDVAL_6,
    CARDVAL_7,
    CARDVAL_8,
    CARDVAL_9,
    CARDVAL_JACK,
    CARDVAL_QUEEN,
    CARDVAL_KING
};

/*!
  Class representing a playing card, with a suite and a face
*/
class card
{
  public:
    /*!
      Constructor creating a card
      @param a_suit The card's suit
      @param a_value The card's value, ace to king
    */
    card(card_suit a_suit, card_value a_value);

    /* Getter for the card's suit */
    card_suit getSuit() const;
    /* Getter for the card's value */
    card_value getValue() const;

    /* Setter for the card's suit */
    void setSuit(card_suit a_suit);
    /* Setter for the card's value */
    void setValue(card_value a_value);

  private:
    /*! Private member for the card's suit */
    card_suit m_suit;

    /*! Private member for the card's value*/
    card_value m_value;
}; // end card class

/*!
  Class representing a deck of any set of playing cards
*/
class deck
{
  public:
    /*!
      Constructor for all 52 unique cards in order, ace-king /
      club-diamond-heart-spade
      (ace club, 2 club, 3 club, etc)
    */
    deck();

    /*! Reorders the cards in this deck randomly */
    void shuffle();

    /*!
      Returns the card [index] cards down from the top, i.e 0 is the top, 1 is
      the first card down, etc
      @param index The card index to find from the top, 0 being the top card
    */
    const card &getCardAt(unsigned int index) const;

    /* Returns and removes the top card from this deck. */
    card takeTopCard();

    /*! Places a card on the top of the deck */
    void placeCardTop(const card &toPlace);

  private:
    /*!
      Pointer to the first card in the linked list. The last card in this linked
      list points to nullptr
    */
    node<card> *card_first;
}; // end deck class

void operator<<(const std::ostream &lhs, const deck &rhs);
