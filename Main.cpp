/*
Sorting Playing Cards

This program reads a list of playing cards from the input file, 
creates an array of Card type objects, then sorts them with the help
of a custom comparison function.

Changelog:
2019-02-28 Boshen Wang initial version
*/

#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <cctype>
#include <algorithm>
#include <vector>
#include <list>

using namespace std;

// Utility functions
void loadFile(string fname, fstream& file)
{
    file.open(fname.c_str());
    if (file.fail())
    {
        cout << "Cannot open file " << fname << endl;
    }
}

// converts string to lowercase
string lowercase(string s)
{
    for (unsigned int i = 0; i < s.length(); i++)
    {
        s[i] = std::tolower(s[i]);
    }
    return s;
}


// Class representing a playing card
class Card
{
public:
    string value; // 2, 3, 4, ..., Q, K, A
    char suit; // C, D, H, S
    // constructor
    // no input validation here!
    Card(string v, char s) : value(v), suit(s) {}

    bool operator < (Card& c) const;
	int valueInt(string value) const;
	int suitInt(char suit) const;
    void print() const;
};

// AUTHOR: Ethan Puschell
// CREATION DATE: 4-6-20
// LAST MODIFIED: 4-6-20
// INPUT: Card value.
// OUTPUT: Integer representation of card value.
// DESCRIPTION: Function converts the card value char into an int.
int
Card::valueInt(string value) const
{
	if (value == "1")			//Series of if, else if statements that checks the possibility of every card value string, returning its value as an int for comparison.
		return 1;
	else if (value == "2")
		return 2;
	else if (value == "3")
		return 3;
	else if (value == "4")
		return 4;
	else if (value == "5")
		return 5;
	else if (value == "6")
		return 6;
	else if (value == "7")
		return 7;
	else if (value == "8")
		return 8;
	else if (value == "9")
		return 9;
	else if (value == "10")
		return 10;
	else if (value == "J")		//Even the Jack, Queen, King, and Ace are converted into their respective integer values and returned.
		return 11;
	else if (value == "Q")
		return 12;
	else if (value == "K")
		return 13;
	else if (value == "A")
		return 14;
	else
		return NULL;		//If the Card value is anything else, the function will return NULL.
}

// AUTHOR: Ethan Puschell
// CREATION DATE: 4-6-20
// LAST MODIFIED: 4-6-20
// INPUT: Card suit
// OUTPUT: Integer representaion of suit.
// DESCRIPTION: Function converts the suit into an integer value.
int
Card::suitInt(char suit) const
{
	switch (suit)		//Switch is used here because the suit is a char.
	{
	case 'C':			//For each case, the Suit is converted into an integer value and returned so it can be used in comparison.
		return 1;
		break;
	case 'D':
		return 2;
		break;
	case 'H':
		return 3;
		break;
	case 'S':
		return 4;
		break;
	default:			//If the Suit is anything else, the function will return NULL.
		return NULL;
		break;
	}
}

// AUTHOR: Ethan Puschell
// CREATION DATE: 4-6-20
// LAST MODIFIED: 4-7-20
// Less than comparison operator overload
// INPUT: a Card c
// OUTPUT: True if 'this' Card is less than Card c, False otherwise
bool 
Card::operator < (Card& c) const
{
	if (valueInt(c.value) == NULL || valueInt(value) == NULL || suitInt(c.suit) == NULL || suitInt(suit) == NULL)		//If any of the value or suits are NULL, the function terminates.
		return NULL;
	if (valueInt(c.value) > valueInt(value))			//If the value of c is higher than the value of this card
		return true;									//then we return true.
	else if (valueInt(c.value) < valueInt(value))		//If the value of c is less than the value of this card
		return false;									//then we return false.
	else if (valueInt(c.value) == valueInt(value))		//If both cards share the same value, then we need to break the tie with the suit.
	{
		if (suitInt(c.suit) > suitInt(suit))			//If the suit of c is higher than the suit of this card.
			return true;								//Then we return true.
		else if (suitInt(c.suit) < suitInt(suit))		//If the suit of c is less than the suit of this card.
			return false;								//We return false.
		else if (suitInt(c.suit) == suitInt(suit))		//If 2 copies of the same card exist in the deck.
			return false;
		else
			return NULL;									//Otherwise, the program will simply exit.
	}
	else
		return NULL;										//Otherwise, the program will simply exit.
}

// prints out a string representation of the Card
void
Card::print() const
{
    cout << this->value << " " << this->suit << endl;
}

// AUTHOR: Ethan Puschell
// CREATION DATE: 4-6-20
// LAST MODIFIED: 4-7-20
// INPUT: Cards list, along with the lists that contain the top half and bottom half of the deck.
// OUTPUT: Top half and bottom half of the card decks now contain cards.
// DESCRIPTION: Partitions the cards deck into a top half and bottom half of the deck.
void 
partition(list<Card> cards, list<Card>& topHalf, list<Card>& bottomHalf)
{
	if (cards.size() == 1)							//If the size of the deck is only 1 card, there is no need to partition the deck.
		return;

	list<Card>::iterator it = cards.begin();		//List iterator is set to the beginning of the cards list.
	int half = cards.size() / 2;					//Integer half is declared as half of the cards list.

	for (int i = 0; i < half; i++)					//First for loop that will iterate through the first half of the cards list.
	{
		topHalf.push_back(*it);						//The cards in the first half of the list are pushed back into the topHalf list.
		it++;										//Iterator is incremented to the next Card in the cards list.
	}

	for (int j = half; j < cards.size(); j++)		//Second for loop that will iterate through the second half of the cards list.
	{
		bottomHalf.push_back(*it);					//The cards in the second half of the list are pushed back into the bottomHalf list.
		it++;										//Iterator is incremented to the next Card in the cards list.
	}
}

// AUTHOR: Ethan Puschell
// CREATION DATE: 4-6-20
// LAST MODIFIED: 4-7-20
// INPUT: Card lists topHalf and bottomHalf.
// OUTPUT: A merged list containing the cards from both topHalf and bottomHalf, in descending order.
// DESCRIPTION: Conquering portion of the merge sort that will combine the 2 lists.
list<Card> fusion(list<Card>& topHalf, list<Card>& bottomHalf)
{
	list<Card> sortedDeck;												//Card list sortedDeck will be the final product that will be returned to the mergeSort function.
	list<Card>::iterator t = topHalf.begin(), b = bottomHalf.begin();	//2 iterators declared and set for the beginning of the topHalf and bottomHalf lists.
	while (topHalf.size() > 0 && bottomHalf.size() > 0)					//While both lists contain at least 1 card.
	{
		if (*b < *t)													//If the topHalf card is higher than the bottomHalf card
		{
			sortedDeck.push_back(*t);									//Then the topHalf card is pushed back into the sortedDeck list.
			if (topHalf.size() > 1)										//If topHalf contains more than 1 card
				*t++;													//Then the iterator for topHalf is incremented to the next card in the list.
			topHalf.pop_front();										//Now the card that was just pushed into the sortedDeck list is removed from the topHalf list.
		}
		else if (*t < *b)												//If the bottomHalf card is higher than the topHalf card
		{
			sortedDeck.push_back(*b);									//Then the bottomHalf card is pushed back into the sortedDeck list.
			if (bottomHalf.size() > 1)									//If bottomHalf contains more than 1 card
				*b++;													//Then the iterator for bottomHalf is incremented to the next card in the list.
			bottomHalf.pop_front();										//Now the card that was just pushed into the sortedDeck list is removed from the bottomHalf list.
		}
		else
		{																//Else, if the topHalf and bottomHalf cards are equal to each other.
			sortedDeck.push_back(*t);									//Then first we push the topHalf card into the sortedDeck.
			if (topHalf.size() > 1)										//If topHalf contains more than 1 card.
				*t++;													//Then the iterator for topHalf is incremented to the next card in the list.
			topHalf.pop_front();										//Now the card that was just pushed into the sortedDeck list is removed from the topHalf list.
			sortedDeck.push_back(*b);									//Next, the bottomHalf card is pushed back into the sortedDeck list.
			if (bottomHalf.size() > 1)									//If bottomHalf contains more than 1 card
				*b++;													//Then the iterator for bottomHalf is incremented to the next card in the list.
			bottomHalf.pop_front();										//Now the card that was just pushed into the sortedDeck list is removed from the bottomHalf list.
		}
	}

	while (topHalf.size() == 0 && bottomHalf.size() > 0)				//While the topHalf contains no cards but the bottomHalf still contains cards.
	{
		sortedDeck.push_back(*b);										//Then the cards in bottomHalf will be pushed back into the sortedDeck list.
		if (bottomHalf.size() > 1)										//If there is another card still in bottomHalf
			*b++;														//Then the iterator increments to it.
		bottomHalf.pop_front();											//And the card that was just pushed back into sortedDeck is removed from bottomHalf.
	}

	while (topHalf.size() > 0 && bottomHalf.size() == 0)				//While the bottomHalf contains no cards but the topHalf still contains cards.
	{
		sortedDeck.push_back(*t);										//Then the cards in topHalf will be pushed back into the sortedDeck list.
		if (topHalf.size() > 1)											//If there is another card still in topHalf
			*t++;														//Then the iterator increments to it.
		topHalf.pop_front();											//And the card that was just pushed back into sortedDeck is removed from bottomHalf.
	}
	return sortedDeck;													//When both bottomHalf and topHalf are empty, the sortedDeck is returned to mergeSort.
}

// INPUT: a list of Cards
// OUTPUT: a sorted list of Cards (descending order)
list<Card> mergeSort(list<Card>& cards)
{
	if (cards.size() > 1)								//If the cards list contains more than 1 Card.
	{
		list<Card> topHalf, bottomHalf;					//Two lists are initialized, topHalf and bottomHalf.
		partition(cards, topHalf, bottomHalf);			//Partition function call will split the cards list into 2 halves: topHalf and bottomHalf.
		mergeSort(topHalf);								//Recursive call on mergeSort for the topHalf.
		mergeSort(bottomHalf);							//Recursive call on mergeSort for the bottomHalf.
		cards = fusion(topHalf, bottomHalf);			//cards will be set equal to the fusion function call that will do a sorted merge on the topHalf and bottomHalf.
	}
	return cards;										//Cards is returned either as a single card (the base case) if the size of the list is 0, or as a sorted list of cards
}														//after the if statement has fully excecuted.

int main()
{
    string inputFilename = "input.txt";
    string line;

    list<Card> cards = list<Card>();
    // open input file
    fstream inputFile;
    loadFile(inputFilename, inputFile);
    while (getline(inputFile, line))
    {
        // trim whitespace
        //line.erase(line.find_last_not_of(" \n\r\t") + 1);
        // echo input
        cout << line << endl;
        // parse input using a stringstream
        stringstream lineSS(line);
        string token;
        string command;
        // store tokens in a vector
        vector<string> tokens;
        while (getline(lineSS, token, ' '))
        {
            // trim whitespace
            token.erase(token.find_last_not_of(" \n\r\t") + 1);
            tokens.push_back(token);
        }

        if (tokens.size() > 0)
        {
            command = tokens[0]; // first token is the command
        }
        else
        {
            command = "";
        }

        if (command == "card")
        {
            // treat string tokens as a single char (first character)
            cards.push_back(Card(tokens[1], tokens[2][0]));
        }
        if (command == "sort")
        {
            cards = mergeSort(cards);
        }
        if (command == "print")
        {
            for (Card c : cards)
            {
                c.print();
            }
        }


    }
    inputFile.close();
	//system("pause");
    return EXIT_SUCCESS;
}