#include "blackJack.h"


//class and constructor
Card::Card(RANK r , SUIT s ,bool ifu ):rank(r),suit(s),isup(ifu)
{
}

//get value function
int Card::getValue() const
{
	//setting int value to 0
	int value = 0;
	
	//returning face value
	if(isup)
	{
		value = rank;
	
		if (value > 10)
		{
			value = 10;
		}
	}
	return value;
}

//flip function
void Card::flip()
{
	isup = !(isup); 
}

//constructor
Hand::Hand()
{
	cardVector.reserve(7);
}

//destructor
Hand::~Hand()
{
	//call clear hand
	 clearHand();
}
void Hand::add(Card* cardPtr)
{
	cardVector.push_back(cardPtr);
}

//clear hand function
void Hand::clearHand()
{
	//card vector loop
	vector<Card*>::iterator iter;
	for (iter = cardVector.begin(); iter != cardVector.end(); ++iter)
	{
		delete *iter;
		*iter = NULL;
	}
	cardVector.clear();
}

//get total function
int Hand::getTotal() const
{
	int total = 0;
	bool containsAce = false;

	if(cardVector.empty())
	{
		return 0;
	}

	if(cardVector[0]->getValue() == 0)
	{
		return 0;
	}

	vector<Card*>::const_iterator iter;
	for(iter = cardVector.begin(); iter != cardVector.end(); ++iter)
	{
		total += (*iter)->getValue();
	}

	//to determine if hand contains ace
	for(iter = cardVector.begin(); iter != cardVector.end(); ++iter)
	{
		if ((*iter)->getValue() == Card::ACE)
		{
			containsAce = true;
		}
	}
	if(containsAce && total <= 11)
	{
		total += 10;
	}
	return total;
}

//constructor
genericPlayer::genericPlayer(const string& name):name(name)
{
}

//destructor
genericPlayer::~genericPlayer()
{
}

//testing if generic player has busted
bool genericPlayer::isBusted() const
{
	bool busted=false;
	if(getTotal() > 21)
	{
		busted= true;
	
	}
	return busted;
}

//displaying a "busted" message
void genericPlayer::bust() const
{
	cout<<name<<" has busted"<<endl;
}

//player constructor
Player::Player(const string& name):genericPlayer(name)
{
}

//destructor
Player::~Player()
{}

//testing if player wants to hit
 bool Player::isHitting() const
{
	char responce;
	bool hitting= false;
	cout<<name<<" want to hit?(Y/N)"<<endl;
	cin>>responce;
	if(responce == 'y' || responce == 'Y')
	{
		hitting= true;
	
	}
	else
		hitting= false;
	return hitting;
}

 //calling win function
void Player::win() const
{
	//displaying player has won
	cout<<name<<" has won!"<<endl;
}

//calling lose function
void Player::lose() const
{
	//displaying player has lost
	cout<<name<<" has lost"<<endl;
}

//calling push function
void Player::push() const
{
	//displaying player has pushed
	cout<<name<<" has pushed"<<endl;
}

//house constructor
House::House(const string& name):genericPlayer(name)
{
	
}

//destructor
House::~House()
{}

//house hitting on 16
 bool House::isHitting() const
{
	return(getTotal() <= 16);	
}

//flip first card function
void House::flipFirstCard()
{
	 //house flipping first card
	if(!(cardVector.empty()))
	{
		cardVector[0]->flip();
	}
	else
		cout<<"There are no cards to flip"<<endl;
	
}

//deck constructor 
Deck::Deck()
{
	cardVector.reserve(52);
	populate();
}

//destructor
Deck::~Deck()
{}

//calling populate function
void Deck::populate()
{
	clearHand();

	//creating a standard deck
	for(int s = Card::CLUBS; s <= Card::SPADES; ++s)
	{
		for(int r = Card::ACE; r <= Card::KING; ++r)
		{
			add(new Card(static_cast<Card::RANK>(r), static_cast<Card::SUIT>(s)));
		}
	}
}

//calling shuffle function
void Deck::shuffle()
{
	random_shuffle(cardVector.begin(), cardVector.end());
}

//calling deal function
void Deck::deal(Hand& aHand)
{
	//populating deck
	if(!cardVector.empty())
	{
		aHand.add(cardVector.back());
		cardVector.pop_back();

	}
	else
	{
		cout<<"out of cards and are unable to deal."<<endl;
		populate();
	}

	
}

//calling additional cards function
void Deck::additionalCards(genericPlayer& aGenericPlayer)
{
	cout<<endl;
	
	//dealing to generic player as long as not busted
	while(!(aGenericPlayer.isBusted()) && aGenericPlayer.isHitting())
	{
		deal(aGenericPlayer);
		cout<<aGenericPlayer<<endl;

		if(aGenericPlayer.isBusted())
		{
			aGenericPlayer.bust();
		}
	}
}

//game constructor
Game::Game(const vector<string>& names)
{
	vector<string>::const_iterator pName;
	
	for(pName = names.begin(); pName != names.end(); ++pName)
	{
		players.push_back(Player(*pName));
	}

	srand(time(0)); //seed the random number generator
	deck.populate();
	deck.shuffle();
}

//destuctor
Game::~Game()
{}

//play function
void Game::play()
{
	//deal 2 cards to everyone
	vector<Player>::iterator pPlayer;

	for(int i = 0; i < 2; ++i)
	{
		for(pPlayer = players.begin(); pPlayer != players.end(); ++pPlayer)
		{
			deck.deal(*pPlayer);
		}
		deck.deal(house);
	}
	house.flipFirstCard();

	//Display everyone hand
	for(pPlayer = players.begin(); pPlayer != players.end(); ++pPlayer)
	{
		cout<< *pPlayer <<endl;
	}
	cout<<house<<endl;

	for(pPlayer = players.begin(); pPlayer != players.end(); ++pPlayer)
	{
		deck.additionalCards(*pPlayer);
	}

	house.flipFirstCard();
	cout<<endl<<house;

	deck.additionalCards(house);

	//if house is busted, player wins
	if(house.isBusted())
	{
		for(pPlayer = players.begin(); pPlayer != players.end(); ++pPlayer)
		{
			if(!(pPlayer->isBusted()))
			{
				pPlayer->win();
			}
		}
	}
	else
	{
		//player pushes
		for(pPlayer = players.begin(); pPlayer != players.end(); ++pPlayer)
		{
			if(!(pPlayer->isBusted()))
			{
				if(pPlayer->getTotal() > house.getTotal())
				pPlayer->win();
				else if(pPlayer->getTotal() < house.getTotal())
				pPlayer->lose();
				else
				pPlayer->push();
			}
		}
	}
	for(pPlayer = players.begin(); pPlayer != players.end(); ++pPlayer)
	{
		pPlayer->clearHand();
	}
	house.clearHand();
	}




			















