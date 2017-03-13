Text-Based Implementation of "UNO" Card Game
Runnable via command line

Created as part of a group project in my Object Oriented Programming class during my 4th year at Dalhousie University.
Group members were Abdul S. AlHajji and Ye Liang.

Original Project Readme follows:

<!-- language: lang-none -->

-----------COMPILING THE PROGRAM-----------

A makefile is included, so the program can be compiled by using the 'make' command.
After compiling, the game can be run with the command './unogame'

----------------HOW TO PLAY----------------

This program allows you to simulate the card game UNO in a text-based interface.
When launched, the program will ask you how many computer players you wish to play against.
You may choose to play against 1 to 5 computer players. After making this choice, the game will start.
(Entering 0 will exit the game)

This guide is for program-specific input/output only. See the included word document for a description of UNO itself.

The game starts on your turn. Whenever it is your turn, the game will print out the card currently on top
of the discard pile, all the cards in your hand, and then the cards in your hand that you could play.

Example:

---

--------Your Turn--------

Current card on top of discard pile: Yellow 1

Your hand:
[Yellow 6] - [Yellow 9] - [Yellow 2] - [Green 1] - [Red 3] - [Green 0] - [Green Skip]
Valid Moves:
1:[Yellow 6] - 2:[Yellow 9] - 3:[Yellow 2] - 4:[Green 1]

Which card would you like to play? (type a number)
> 

---

Each valid move is printed with a number before it. You type this number into the prompt in order to select your move.
(Entering 0 here will also exit the game)
Once you select a move, the card is played onto the discard pile. Any effects that the card would have will be activated,
such as making the next player in sequence draw cards or skip their turn, or reversing the turn order. If you play a
wild card, the game will prompt for you to select the colour that must be played next:

---

Please select the next colour to be played. (Type a number)
1. Red   -   2. Yellow   -   3. Green   -   4. Blue
> 

---

After your move is completed, each computer player will make their moves. Once it is your turn again, the process repeats.

---

Which card would you like to play? (type a number)
> 1

COMPUTER1 loses their turn.
COMPUTER2 plays Green 4
COMPUTER3 draws a card. It's a Yellow 4, so they play it.
COMPUTER4 plays Wild Draw Four
> You lose your turn and have to draw 4 cards!
COMPUTER1 plays Blue Skip
COMPUTER2 loses their turn.
COMPUTER3 plays Blue Skip
COMPUTER4 loses their turn.

--------Your Turn--------

---

The game will print a message when any player has a single card in their hand.
The game will end once a player empties their hand.
Regardless of if you win or lose, the game will allow you to start another game by entering the new number of AI players.
As before, you can enter 0 to exit the game.