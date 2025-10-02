/*

Project 2a Michael Shteynberg Temirlan Nurtayev Daniil Petrov

main.cpp: Contains function definitions for the classes:
  card
  deck

  Also contains the main() function / entry point

*/

#include "main.h"
#include <stdexcept>

/*! Constructor creating a card */
card::card(card_suit a_suit, card_value a_value)
    : m_suit(a_suit), m_value(a_value)
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
  (ace club, 2 club, 3 club, etc)
*/
deck::deck()
{
    const card_suit suits[] = {SUIT_CLUB, SUIT_DIAMOND, SUIT_HEART, SUIT_SPADE};

    const card_value values[] = {CARDVAL_ACE,
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
                                 CARDVAL_KING};

    const unsigned short n_suits = sizeof(suits) / sizeof(card_suit);
    const unsigned short n_values = sizeof(values) / sizeof(card_value);

    for (unsigned short i_suit = 0; i_suit < n_suits; i_suit++)
    {
        for (unsigned short i_value = 0; i_value < n_values; i_value++)
        {

        }
    }
    // TODO: Finish using placeCardTop()
}

/* Reorders the cards in this deck randomly */
void deck::shuffle()
{
    // TODO
}

/*
  Returns the card [index] cards down from the top, i.e 0 is the top, 1 is
  the first card down, etc
*/
const card &deck::getCardAt(unsigned int index) const
{
    node<card> *lastNode = card_first;
    for (unsigned int i = 0; i < index; i++)
    {
        if (lastNode->next == nullptr)
        {
            throw std::out_of_range("Given card index is out of deck range");
        }
        lastNode = lastNode->next;
    }

    return lastNode->nodeValue;
}

/*
  Returns and removes the top card from this deck.
*/
card deck::takeTopCard()
{
    node<card> *oldTopNode = card_first;
    card oldTopCard = oldTopNode->nodeValue;

    node<card> *newTopNode = oldTopNode->next;
    card_first = newTopNode;

    // Free the memory used by this node
    delete oldTopNode;

    return oldTopCard;
}

/* Places a card on the top of the deck */
void deck::placeCardTop(const card &toPlace){
    node<card> *newTopNode = new node<card>;

    // Set the next node of the new top node to be the old top node
    newTopNode->next = card_first;

    // Set the new top node value to be the given card
    newTopNode->nodeValue = toPlace;

    // Set the top node of the deck to the new top node
    card_first = newTopNode;
}

void operator<<(std::ostream &lhs, const deck &rhs)
{
    // TODO
}
