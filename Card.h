//Header for Card class

#ifndef CARD_H
#define CARD_H

#include <iostream>
#include <string>
using namespace std;

//Type of card (A number card, Skip Turn, Reverse, Draw Two, Wild Card, Wild Draw Four)
enum Type {zero, one, two, three, four, five, six, seven, eight, nine, skip, reverseOrder, drawTwo, wild, wild4};
//Colour of card ('none' is for wild cards before assignment)
enum Colour {red, yellow, green, blue, none};

class Card
{
	private:
		Type card_type; //Type of card
		Colour card_colour; //Colour of card

    public:
		Card(Type t, Colour c); //Create a normal card with type and colour
		Card(Type t); //Create a card without a colour (for wild cards only)
		int getType(); //Return the type of the card as an integer
		int getColour(); //Return the colour of the card as an integer
		void setWildColour(Colour); //Set a new colour for this card (used for wild cards when played by a player)
		string toString(); //Return this card as a string (ex. "Red 5")
};


#endif //UNO_GAME_CARD_H
