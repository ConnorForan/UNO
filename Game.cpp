//Functions for UNO Game class

#include "Game.h"

Game::Game(int numPlayers) //Constructor, set up the deck and the players
{
	//Fill the deck
	for(int i=0; i<13; i++) //Add standard cards. For each type of coloured card (0...9, skip, reverse, and drawTwo)...
	{
		for(int k=0; k<4; k++) //...and for each colour (red, yellow, green, and blue)...
		{
			deck.push_back(new Card((Type)i, (Colour)k)); //...add two cards of this type and colour to the deck.
			if(i != 0)
				deck.push_back(new Card((Type)i, (Colour)k)); // (Except for 0 cards, where there is only one of each colour)
		}
	}
	for(int i=0; i<4; i++) //Add wild cards (4 Wild cards, 4 'Wild Draw Four' cards)
	{
		deck.push_back(new Card(wild));
		deck.push_back(new Card(wild4));
	}

	do{
		shuffleDeck(); //Shuffle the deck
	}while(deck.back()->getType() > 9); //Only allow number cards as the first card
	discardPile.push_back(deck.back()); //Place the first card onto the discard pile (shuffle function makes sure first card is always a number card)
	deck.pop_back(); //Remove that card from the top of the deck

	//Make the players
	players.push_back(new HumanPlayer()); //Create the human player
	for(int i=0; i<numPlayers-1; i++) //Create the specified number of computer players
	{
		players.push_back(new CompPlayer(i+1));
	}

	//Fill the players' hands (each player gets 7 cards at the start of the game
	for(unsigned int i=0; i<players.size(); i++)
	{
		for(int x=0; x<7; x++)
			players[i]->drawCard(Game::drawCard());
	}

	reversed = false;
	currentPlayer = -1; //Initial value to denote beginning of the match
}

Game::~Game() //Destructor
{
	//Empty the deck, discard pile, and players vectors (deallocate all space, delete all new'd objects)
	for(unsigned int i=0; i<deck.size(); i++)
	{
		delete deck[i];
	}
	for(unsigned int i=0; i<discardPile.size(); i++)
	{
		delete discardPile[i];
	}
	for(unsigned int i=0; i<players.size(); i++)
	{
		delete players[i];
	}
}

int Game::deckSize() //Return the number of cards in the deck
{
	return deck.size();
}

/*void Game::printDeck() //Print the contents of the deck (unused)
{
	for(unsigned int i=0; i<deck.size(); i++)
	{
		cout << deck[i]->toString() << endl;
	}
}*/

Card* Game::getTopCard() //Return the card at the top of the discard pile
{
	return discardPile.back();
}

void Game::shuffleDeck() //Shuffle the cards in the deck
{
	srand(time(0));
	random_shuffle(deck.begin(), deck.end());
}

Card* Game::drawCard() //Removes a card from the deck and returns it
{
	Card* card = NULL;
	if(deck.size() == 0) //Shuffle all cards from the discard pile except the top one back into the deck if the deck runs out
	{
		card = discardPile.back(); //Save the current top card
		for(unsigned int i=0; i<discardPile.size()-1; i++) //Push all other contents of the discard pile into the deck
		{
			if(discardPile[i]->getType() > 12) //If card is a wild card, restore its default colour value
				discardPile[i]->setWildColour(none);
			deck.push_back(discardPile[i]);
		}
		discardPile.clear(); //Empty the discard pile
		discardPile.push_back(card); //Put the top card back
		shuffleDeck(); //Shuffle the deck
	}
	card = deck.back(); //Get card
	deck.pop_back(); //Remove card from deck
	return card; //Return the card pointer
}

void Game::playCard(Card* card) //Place a card onto the discard pile
{
	discardPile.push_back(card);
}

bool Game::validPlay(Card* card) //Returns true if the given card would be a valid play
{
	if(card->getType() == wild || card->getType() == wild4 || card->getColour() == discardPile.back()->getColour() || card->getType() == discardPile.back()->getType())
	{
		return true;
	}
	else
		return false;
}

Player* Game::nextPlayer() //Return pointer to the player who's turn it is
{
	if(currentPlayer == -1) //Set it to 0 (the human player) for the first turn
		currentPlayer = 0;
	else
	{
		//Increment the currentPlayer in the appropriate direction, in regards to the value of 'reversed'
		if(reversed) //Backwards
		{
			currentPlayer--;
			if(currentPlayer < 0)
				currentPlayer = players.size()-1;
		}
		else //Forwards
		{
			currentPlayer++;
			if((unsigned int)currentPlayer >= players.size())
				currentPlayer = 0;
		}
	}

	for(unsigned int i=0; i<players.size(); i++) //Update valid moves for all players
		players[i]->updateValidCards(Game::getTopCard());

	return players[currentPlayer]; //Return pointer to the current player
}

void Game::reverseTurns() //Reverse the turn order
{
	if(reversed)
		reversed = false;
	else
		reversed = true;
}
