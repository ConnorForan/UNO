//Functions for Computer Player class

#include "Player.h"

CompPlayer::CompPlayer(int i) //Constructor, appends their player# to their name
{
	string s = "COMPUTER";
	char c = (char)(48+i);
	s += c;
	name = s;
}

bool CompPlayer::isHuman() //This player is NOT human
{
	return false;
}

unsigned int CompPlayer::chooseMove() //Use weighted random to determine move
{
    int sum = 0; //Sum of weights
    int index = -1; //Chosen move index (an index of validCards, which is the same size as weights)
    for(unsigned int i=0; i<weights.size(); i++) //Sum the weights
    {
    	sum += weights[i];
    }
	srand(time(0)); //Seed the random
    unsigned int r = std::rand()%sum; //Generate a random number from 0 to sum-1
    for(unsigned int i=0; i<weights.size() && index == -1; i++) //Decrease by each weight until r is smaller than the current weight
    {
    	if(r < weights[i])
    		index = i;
    	else
    		r -= weights[i];
    }
    if(index == -1) //Probably not necessary, but makes things safer
    {
    	cout << "Fuck" << endl;
    	index = 0;
    }
    return index; //Return the decided index
}

//Method to update the vector of valid cards to play, and update the weights
//The parameter should be 'discardPile.back()'
void CompPlayer::updateValidCards(Card* topCard)
{
	validCards.clear();//Empty the current validCard vector
	weights.clear(); //Empty the weights vector as well
	int wild_4 = -1; //Set to index of Wild Draw 4 if one is found
	bool hasColourMatch = false; //Wild Draw 4 is only valid if there are no colour matches
    for (unsigned int i=0; i < hand.size(); i++)
    {
        if (topCard->getColour() < 5 && hand[i]->getColour() == topCard->getColour()) //push a card to validPlayCards if color matches
        {
        	validCards.push_back(i);
        	weights.push_back(15); //Preference to matching colour
        	hasColourMatch = true; //Colour match found
        }
        else if (topCard->getType() <= 12 && hand[i]->getType() == topCard->getType()) //push a card to validPlayCards if num matches
        {
        	validCards.push_back(i);
        	weights.push_back(5); //Will play cards based on number less often if a colour match is an option
        }
        else if (hand[i]->getType() == 13) //push a card to validPlayCards if it is a wild card
        {
        	validCards.push_back(i);
        	weights.push_back(1); //Will not play wildcards as often if there are other options
        }
        else if (hand[i]->getType() == 14 && wild_4 == -1) //Wild 4 card will only be playable if no colour matches can be made
        {
        	wild_4 = i;
        }
    }
    if(!hasColourMatch && wild_4 != -1) //If Wild Draw 4 can be played
    {
    	validCards.push_back(wild_4);
    	weights.push_back(10); //Playing a draw 4 card is tempting when it is valid
    }
}
