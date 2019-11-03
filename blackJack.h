#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <ctime>
#include <exception>
using namespace std;

class Card
{
	//overloading << operator so can send Card object to standard output
	friend ostream &operator<<(ostream &os, const Card &aCard);

public:

	enum SUIT {CLUBS, SPADES, HEARTS, DIMONDS};
	enum RANK {ACE = 1, TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE, TEN, JACK, QUEEN, KING};

	Card(RANK r = ACE, SUIT s = SPADES, bool ifu = true);

	//returns value of a card, 1-11
	int getValue() const;

	//flips the card; if face up, becomes face down and vice versa
	void flip();

private: 
	
	// declared variables
	RANK rank;
	SUIT suit;
	bool isup;
};


class Hand
{
public:
	Hand();

	//destructor
	virtual ~Hand();

	//adds card to hand
	void add(Card* cardPtr);

	//clears all cards in the hand
	void clearHand();

	//gets hand total value, intelligently treats aces as 1 or 11
	int getTotal() const;

protected:
	vector<Card*> cardVector;
};


class genericPlayer : public Hand
{
	//overloading << operator so can send generic player object to standard output
	friend ostream &operator<<(ostream& os, const genericPlayer& aGenericPlayer);

public: 
	genericPlayer(const string& name = " ");

	//desructor
	virtual ~genericPlayer();

	//indicates weather or not the player wants another hit
	virtual bool isHitting() const = 0;

	//returns whether generic player has busted - has a total greater than 21
	bool isBusted() const;

	//announces that the generic player busts
	void bust() const;

protected: 
	string name;

};


class Player : public genericPlayer
{
public:
	Player(const string& name = " ");

	//destructor
	virtual ~Player();

	//returns whether or not the player wants another hit
	virtual bool isHitting() const;

	//announces that the player wins
	void win() const ;

	//annonces that the player lost
	void lose() const;

	//announces that the player pushes
	void push() const;
};


class House : public genericPlayer
{
public: 
	House(const string& name = "House");

	//destructor
	virtual ~House();

	//indicates whether house is hitting - will always hit on 16 or less
	virtual bool isHitting() const;

	//flips over first card
	void flipFirstCard();
};


class Deck : public Hand
{
public:
	Deck();

	//destructor
	virtual ~Deck();
	
	//create a standard deck of 52 cards
	void populate();

	//shuffle cards
	void shuffle();

	//deal one card to a hand
	void deal(Hand& aHand);

	//give additional cards to a generic player
	void additionalCards(genericPlayer& aGenericPlayer);
};


class Game
{
public:
	Game(const vector<string>& names);

	//destructor
	~Game();

	//plays the game of blackjack
	void play();

private:
	Deck deck;
	House house;
	vector<Player> players;
};

