/*

Project 2a Michael Shteynberg Temirlan Nurtayev Daniil Petrov

main.cpp: Contains function definitions for the classes:
  card
  deck

  Also contains the main() function / entry point

*/

#include "main.h"

/*! Constructor creating a card */
card::card(card_suit a_suit, card_value a_value) : suit(a_suit), value(a_value)
{
}

/* Getter for the card's suit */
card_suit card::getSuit() const
{
    return m_suit;
}

/* Getter for the card's value */
card_value card::getValue() const
{
    return m_value;
}

/* Setter for the card's suit */
void card::setSuit(card_suit a_suit)
{
    m_suit = a_suit;
}

/* Setter for the card's value */
void card::setValue(card_value a_value)
{
    m_value = a_value;
}

/*
  Constructor for all 52 unique cards in order, ace-king /
  club-diamond-heart-spade
*/
deck::deck(){
  // TODO
}

/* Reorders the cards in this deck randomly */
void deck::shuffle(){
  // TODO
}

/*
  Returns the card [index] cards down from the top, i.e 0 is the top, 1 is
  the first card down, etc
*/
const card &deck::getCardAt(unsigned int index) const{
  // TODO
}

/*
  Returns and removes the top card from this deck.
*/
card deck::takeTopCard(){
  // TODO
}

void operator<<(std::ostream &lhs, const deck &rhs){
  // TODO
}
