//Header for player classes

#ifndef PLAYER_H
#define PLAYER_H

#include "Card.h"
#include <vector>
#include <time.h>
#include <cstdlib>

class Player //Base class for a player
{
    protected:
		string name; //Player's name
        std::vector<Card*> hand; //The player's hand
        std::vector<unsigned int> validCards; //A vector of cards that are valid to play according to the top of the discard pile. The value stored is the index in Hand.

    public:
        Player();
        virtual ~Player(); //Destructor to delete all card objects in the hand from memory
        string getName(); //Return name as a string
        int handSize(); //Return the number of cards in the hand
        int validMoves(); //Return the number of valid moves
        void drawCard(Card*); //Add a card to the hand
        //Card* getCard(unsigned int); //Return a card WITHOUT removing it from the hand. Uses the index from the validCards vector. (unused)
        Card* playCard(unsigned int); //Return a card and remove it from the hand. Uses the index from the validCards vector.

        //Virtual methods for children
        virtual bool isHuman();
        virtual void printHand();
        virtual void printValidCards();
        virtual unsigned int chooseMove();
        virtual void updateValidCards(Card*); //Updates the vector of valid cards to play
};

class HumanPlayer : public Player
{
    public:
		HumanPlayer();
        bool isHuman(); //Returns true
        void printHand(); //Print out the player's hand to the console
        void printValidCards(); //Print out the player's valid moves to the console
        void updateValidCards(Card*); //Updates the vector of valid cards to play
};

class CompPlayer : public Player
{
	private:
		std::vector<unsigned int> weights; //Weights for probability of selecting certain cards (always the same size as validCards
    public:
		CompPlayer(int); //Constructor specifies what # player this is
        bool isHuman(); //Returns false
        unsigned int chooseMove(); //Uses weighted random to choose a card to play
        void updateValidCards(Card*); //Updates the vector of valid cards to play, and updates the weight vector
};

#endif //UNO_GAME_PLAYER_H
