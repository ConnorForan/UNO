//Functions for Human Player class

#include "Player.h"

HumanPlayer::HumanPlayer() //Constructor
{
	name = "Player 1"; //Not used
}

bool HumanPlayer::isHuman() //Is a human
{
	return true;
}

void HumanPlayer::printHand()//Print out cards in the hand vector
{
	cout << "Your hand:" << std::endl;
	for(unsigned int i=0; i<hand.size(); i++) //Loop through the hand vector
	{
		cout << "[" << hand[i]->toString() << "]"; //Print each card
		if(i != hand.size()-1)
			cout << " - ";
	}
	cout << endl;
}

void HumanPlayer::printValidCards() //Print out the player's valid moves
{
	cout << "Valid Moves:" << endl;
	for(unsigned int i=0; i<validCards.size(); i++) //Loop through the validCards vector
	{
		//Print out each card with its index+1 (used for the user's choice)
		cout << (i+1) << ":[" << hand[validCards[i]]->toString() << "]";
		if(i != validCards.size()-1)
			cout << " - ";
	}
	cout << endl;
}

//Method to update the vector of valid cards to play
//The parameter should be 'discardPile.back()'
void HumanPlayer::updateValidCards(Card* topCard)
{
	validCards.clear();//Empty the current validCards vector
	int wild_4 = -1; //Set to index of Wild Draw 4 if one is found
	bool hasColourMatch = false; //Wild Draw 4 is only valid if there are no colour matches
    for (unsigned int i=0; i < hand.size(); i++)
    {
    	if (topCard->getColour() < 5 && hand[i]->getColour() == topCard->getColour()) //push a card to validPlayCards if color matches
    	{
    		validCards.push_back(i);
    		hasColourMatch = true; //Colour match found
    	}
    	else if (topCard->getType() <= 12 && hand[i]->getType() == topCard->getType()) //push a card to validPlayCards if type matches
        {
        	validCards.push_back(i);
        }
        else if (hand[i]->getType() == 13) //push a card to validPlayCards if it is a wild card
        {
        	validCards.push_back(i);
        }
        else if (hand[i]->getType() == 14 && wild_4 == -1) //Wild 4 card will only be playable if no colour matches can be made
        {
        	wild_4 = i;
        }
    }
    if(!hasColourMatch && wild_4 != -1) //If Wild Draw 4 can be played
    {
    	validCards.push_back(wild_4);
    }
}
