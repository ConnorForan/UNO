//Header for UNO Game class

#ifndef GAME_H
#define GAME_H

#include <algorithm>
#include "Player.h"

class Game
{
    private:
		//Vectors for the deck and discard pile. The 'back' of the vector is considered the 'top' of the deck/pile, for our purposes.
		std::vector<Card*> deck;
		std::vector<Card*> discardPile;
		std::vector<Player*> players; //Vector of players. The first one is always the sole human player.
		int currentPlayer; //Identifies the player whos turn it is. Corrisponds to the index from the players vector. Loops around if it gets too big or goes negative
		bool reversed; //Is set to true if the turns are currently in reverse order
    public:
        Game(int); //Constructor (create deck, shuffle deck, place first card onto discard pile)
        ~Game(); //Destructor (deallocates all space; destroys all card objects)
        int deckSize(); //Returns the current number of cards in the deck
        //void printDeck(); //Print the contents of the deck (unused)
        Card* getTopCard(); //Print the card at the top of the discard pile
        void shuffleDeck(); //Shuffle the deck
        Card* drawCard(); //Remove a card from the top of the deck and return it
        void playCard(Card*); //Place a card onto the discard pile
        bool validPlay(Card*); //Check if a card would be a valid 'play' onto the discard pile (does not yet account for the extra rule for 'Wild Draw Four' cards)
        Player* nextPlayer(); //Increment currentPlayer and return the player who should go next
        void reverseTurns(); //Set reversed to true
};

#endif //UNO_GAME_GAME_H
