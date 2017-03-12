//Functions for Card class

#include "Card.h"

Card::Card(Type t, Colour c) //Create a card
{
	card_type = t;
	card_colour = c;
}
Card::Card(Type t) //Colourless alternative used for creating wild cards
{
	card_type = t;
	card_colour = none;
}

int Card::getType() //Return type of card as an integer
{
	return card_type;
}
int Card::getColour() //Return colour of card as an integer
{
	return card_colour;
}
void Card::setWildColour(Colour c) //Declare colour of a wild card (used when wild card is played)
{
	card_colour = c;
}
string Card::toString() //Print out card colour and type
{
	string out = "";
	//Colour
	if(card_colour != none)
	{
		if(card_colour == red)
			out.append("Red ");
		else if(card_colour == yellow)
			out.append("Yellow ");
		else if(card_colour == green)
			out.append("Green ");
		else if(card_colour == blue)
			out.append("Blue ");
	}

	//Type
	if(card_type <= 9)
	{
		char num = (char)(48+card_type);
		out += num;
	}
	else if(card_type == skip)
		out.append("Skip");
	else if(card_type == reverseOrder)
		out.append("Reverse");
	else if(card_type == drawTwo)
		out.append("Draw Two");
	else if(card_type == wild)
		out.append("Wild Card");
	else if(card_type == wild4)
		out.append("Wild Draw Four");

	return out;
}
