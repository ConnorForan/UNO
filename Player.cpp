//Functions for Player base class

#include "Player.h"

Player::Player() //Constructor
{
	name = "Player"; //Not used
}

Player::~Player() //Destructor, deletes all card objects
{
	for(unsigned int i=0; i < hand.size(); i++)
	{
		delete hand[i];
	}
}

string Player::getName() //Return name
{
	return name;
}

int Player::handSize() //Return number of cards in hand
{
	return hand.size();
}
int Player::validMoves() //Return the number of valid moves
{
	return validCards.size();
}

void Player::drawCard(Card* card) //Add a card to the hand
{
    hand.push_back(card);
}

/*Card* Player::getCard(unsigned int x) //Return card at given validCards index (unused)
{
	x--;
	Card* card = Hand[validCards[x]];
    return card;
}*/
Card* Player::playCard(unsigned int x) //Removes and returns card based on validCards index
{
	Card* card = hand[validCards[x]]; //Get card
	hand.erase(hand.begin() + validCards[x]); //Remove from hand
    return card; //Return it
}

//Virtual methods for children
bool Player::isHuman() {return false;}
void Player::printHand(){}
void Player::printValidCards(){}
unsigned int Player::chooseMove(){return 0;}
void Player::updateValidCards(Card* topCard){}
