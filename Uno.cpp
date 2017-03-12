/* UNO Game
 * CSCI 3132 Group Project
 *
 * Connor Foran
 * Abdul S. AlHajji
 * Ye Liang
 *
 * November 2016
 * Dalhousie University
 *
 * Program that simulates the card game UNO
 *
 * Main file - initializes the game and loops to play it
 */

#include "Game.h" //Load other files

int main() //Main method
{
	Game* game = NULL;
	//Misc. Variables
	Card* card = NULL;
	Player* currentPlayer = NULL;
	int input = 1;
	bool gameInProgress = false;
	bool firstGame = true;
	Type cardPlayed = zero; //Used to identify action cards


	while(input != 0) //======================================Main loop======================================
	{
		if(!gameInProgress) //If there is currently no game
		{
			if(firstGame) //Only prints this message the first time the program starts
			{
				cout << "----==== Welcome to UNO! ====----" << endl << "To start a game, please input the number of computer players you wish to play against (Enter 1-5, or 0 to quit)" << endl << "> ";
				firstGame = false;
			}
			else
			{
				cout << "Would you like to play again? Enter how many computer players you would like to face this time (1-5) or type 0 to quit." << endl << "> ";
			}
			cin >> input; //Gets the user's choice of # of computer players
			while(input < 0 || input > 5) //Avoid invalid inputs
			{
				cout << "Invalid choice." << endl << "> ";
				cin >> input;
			}
			if(input == 0) //Exit command
				continue;

			game = new Game(input+1); //Creates the game with the specified number of computer players
			gameInProgress = true; //Mark the game as in progress
			cout << "Okay! Let the game begin!" << endl;
		}

		//-------------Reset/Increment-------------
		cardPlayed = zero;
		card = NULL;
		currentPlayer = game->nextPlayer(); //Get the player who's turn it is

		//-------------Print out info for human player-------------
		if(currentPlayer->isHuman() && currentPlayer->validMoves() != 0)
		{
			cout << endl << "--------Your Turn--------" << endl << endl;
			cout << "Current card on top of discard pile: " << game->getTopCard()->toString() << endl << endl; //Print card currently at the top of the discard pile
			currentPlayer->printHand(); //Print the player's hand (if human)
		}

		//==========================If the current player has no valid moves==========================
		if(currentPlayer->validMoves() == 0)
		{
			card = game->drawCard(); //...They draw a card
			if(currentPlayer->isHuman())
				cout << "> You have no valid moves. You draw a card... " << card->toString() << endl; //Print the card drawn
			if(game->validPlay(card)) //If this card can be played...
			{
				cardPlayed = (Type)card->getType(); //Record the card's type
				game->playCard(card); //Play the card
				if(currentPlayer->isHuman())
					cout << "> A valid move! You play the card." << endl;
				else
					cout << currentPlayer->getName() << " draws a card. It's a " << card->toString() << ", so they play it." << endl;
			}
			else //If the player still cannot make a move...
			{
				currentPlayer->drawCard(card); //Add the card to the player's hand
				if(currentPlayer->isHuman())
					cout << "> You can't play this card either, so you add it to your hand." << endl;
				else
					cout << currentPlayer->getName() << " drew a card but couldn't play it, so they added it to their hand." << endl;
			}
		}
		//==========================If the current player DOES have valid moves==========================
		else if(currentPlayer->isHuman()) //For a human player
		{
			currentPlayer->printValidCards(); //Print out the player's valid moves, along with numbers...

			cout << endl << "Which card would you like to play? (type a number)" << endl << "> ";
			cin >> input; //...the user enters the number corresponding to the move they wish to make.

			if(input == 0) //Entering a 0 is the exit command
				continue;
			while(input > currentPlayer->validMoves()) //If input is invalid
			{
				cout << "Invalid choice." << endl << "> ";
				cin >> input;
			}

			game->playCard( currentPlayer->playCard(input-1) ); //Place the card onto the discard pile
			cardPlayed = (Type)game->getTopCard()->getType(); //Record the type of the card
			cout << endl;
		}
		else //For a computer player
		{
			card = currentPlayer->playCard(currentPlayer->chooseMove()); //AI chooses a card to play
			game->playCard(card);
			cout << currentPlayer->getName() << " plays " << game->getTopCard()->toString() << endl; //Print what card was played, and by who
			cardPlayed = (Type)game->getTopCard()->getType(); //Record the type of the card
		}

		//=====================================Conditions=====================================
		//-------------Win Condition-------------
		if(currentPlayer->handSize() == 0) //If the current player's hand is empty, they win
		{
			if(currentPlayer->isHuman())
				cout << "You win!!";
			else
				cout << currentPlayer->getName() << " wins. Better luck next time!";
			gameInProgress = false; //Ends game
			delete game; //Deallocates dynamic memory
			game = NULL;
			cout << endl << endl << endl;
			continue;
		}
		//-------------"UNO" Condition-------------
		else if(currentPlayer->handSize() == 1) //If the current player has only one card left, they say "Uno"
		{
			if(currentPlayer->isHuman())
				cout << "> You say \"Uno!\"" << endl;
			else
				cout << currentPlayer->getName() << " says \"Uno!\"" << endl;
		}

		//============================Code for if an action card is played============================
		//-------------WILD CARD-------------
		if(cardPlayed == wild || cardPlayed == wild4) //If the card played was a wild card, the player must declare the next colour to be played
		{
			if(currentPlayer->isHuman()) //Get the user to pick the colour if it is their turn
			{
				do{
					cout << "Please select the next colour to be played. (Type a number)" << endl
						 << "1. Red   -   2. Yellow   -   3. Green   -   4. Blue" << endl << "> ";
					cin >> input; //Get the user's choice
					if(input < 1 || input > 4)
					{
						cout << "Invalid choice." << endl;
					}
				}while(input < 1 || input > 4); //The user must make a valid choice to continue.
				game->getTopCard()->setWildColour((Colour)(input-1));
				cout << endl;
			}
			else //Randomly picks a colour for the AI
			{
				srand(time(0));
				game->getTopCard()->setWildColour((Colour)(rand()%4));
			}
			if(cardPlayed == wild4) //If the wild card is a 'draw 4' variant, the next players loses their turn and draws 4 cards
			{
				currentPlayer = game->nextPlayer(); //Get next player
				for(int i=0; i<4; i++) //Make them draw cards
					currentPlayer->drawCard(game->drawCard());
				if(currentPlayer->isHuman())
					cout << "> You lose your turn and have to draw 4 cards!" << endl;
				else
					cout << currentPlayer->getName() << " loses their turn and draws 4 cards!" << endl;
			}
		}
		//-------------SKIP TURN CARD-------------
		else if(cardPlayed == skip) //Skips the next player's turn
		{
			currentPlayer = game->nextPlayer(); //Get next player
			if(currentPlayer->isHuman())
				cout << "> You lose your turn..." << endl;
			else
				cout << currentPlayer->getName() << " loses their turn." << endl;
		}
		//-------------DRAW TWO CARD-------------
		else if(cardPlayed == drawTwo) //Skips the next player's turn and makes them draw two cards
		{
			currentPlayer = game->nextPlayer(); //Get next player
			for(int i=0; i<2; i++) //Make them draw cards
				currentPlayer->drawCard(game->drawCard());
			if(currentPlayer->isHuman())
				cout << "> You lose your turn and have to draw 2 cards..." << endl;
			else
				cout << currentPlayer->getName() << " loses their turn and draws 2 cards." << endl;
		}
		//-------------REVERSE CARD-------------
		else if(cardPlayed == reverseOrder)
		{
			game->reverseTurns(); //Reverses the turn order
		}
	}

	if(game != NULL) //Shouldn't be needed, but just in case
		delete game; //Clean up (will delete all card objects)
	cout << endl << "Closing program. Bye bye!" << endl;
}
