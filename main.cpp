#include "BlackJack.h"

int main()
{
	//welcome message
    cout << "\t\tWelcome to Blackjack!\n\n";
    
    int numPlayers = 0;
    while (numPlayers < 1 || numPlayers > 7)
    {
        cout << "How many players? (1 - 7): ";
        cin >> numPlayers;
    }   

    vector<string> names;
    string name;
    for (int i = 0; i < numPlayers; ++i)
    {
        cout << "Enter player name: ";
        cin >> name;
        names.push_back(name);
    }
    cout << endl;

    //continue game loop        
    Game aGame(names);
    char again = 'y';
    while (again != 'n' && again != 'N')
    {
        aGame.play();
        cout << "\nDo you want to play again? (Y/N): ";
        cin >> again;
    } 

    return 0;
}//end main

//overloads << operator so Card object can be sent to cout
ostream& operator<<(ostream& os, const Card& aCard)
{
    const string RANKS[] = {"0", "A", "2", "3", "4", "5", "6", "7", "8", "9", 
                            "10", "J", "Q", "K"};
    const string SUITS[] = {"c", "d", "h", "s"};

    if (aCard.isup)
        os << RANKS[aCard.rank] << SUITS[aCard.suit];
    else
        os << "XX";

    return os;
}

//overloads << operator so a GenericPlayer object can be sent to cout
ostream& operator<<(ostream& os, const genericPlayer& aGenericPlayer)
{
    os << aGenericPlayer.name << ":\t";
    
    vector<Card*>::const_iterator pCard;
    if (!aGenericPlayer.cardVector.empty())
    {
        for (pCard = aGenericPlayer.cardVector.begin();pCard != aGenericPlayer.cardVector.end(); ++pCard)
            os << *(*pCard) << "\t";

        if (aGenericPlayer.getTotal() != 0)
            cout << "(" << aGenericPlayer.getTotal() << ")";
    }
    else
    {
        os << "<empty>";
    }
        
    return os;
}
