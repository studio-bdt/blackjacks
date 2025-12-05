#include "main.h"

void NewRound()
{
    bet = 0;
    PlayerCards.clear();
    OppCards.clear();
    AddPlayerCardValues();
    AddOppCardValues();
    DidPlayerStand = false;
    DidOppStand = false;

    PlaceBets();

    PlayerCards.push_back(GetCardName(1 + ((std::time(nullptr) * rand()) % 13)));
    PlayerCards.push_back(GetCardName(1 + ((std::time(nullptr) * rand()) % 13)));
    AddPlayerCardValues();

    std::this_thread::sleep_for(std::chrono::milliseconds(250));
    std::cout << "You got a " << PlayerCards[0] << " and a " << PlayerCards[1] << " making up a value of " << PlayerValue << "!\n";
    
    OppCards.push_back(GetCardName(1 + ((std::time(nullptr) * rand()) % 13)));
    OppCards.push_back(GetCardName(1 + ((std::time(nullptr) * rand()) % 13)));
    AddOppCardValues();
    
    std::this_thread::sleep_for(std::chrono::milliseconds(250));
    std::cout << "The opponent got a " << OppCards[0] << ".\n";

    while(PlayerValue < 21 & OppValue < 21 & (!DidPlayerStand || !DidOppStand))
    {
        if(!DidPlayerStand)
        {
            std::this_thread::sleep_for(std::chrono::milliseconds(250));
            ChoosePlayerAction();
        }
        if(!DidOppStand)
        {
            std::this_thread::sleep_for(std::chrono::milliseconds(250));
            ChooseOppAction();
        }
    }
    EndGameConditionals();
}

void PlaceBets()
{
    std::this_thread::sleep_for(std::chrono::milliseconds(250));
    std::cout << "You have " << money << " dollars.\n";

    std::this_thread::sleep_for(std::chrono::milliseconds(250));
    std::cout << "How much would you like to bet?: ";
    std::cin >> bet;

    while (bet == 0 || bet > money) {
        if (std::cin.fail()) {
            std::cin.clear(); // Clear error state
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Discard invalid input

            std::this_thread::sleep_for(std::chrono::milliseconds(250));
            std::cout << "Please enter a valid bet amount: ";
            std::cin >> bet;
        }
        if (bet == 0)
        {
            std::this_thread::sleep_for(std::chrono::milliseconds(250));
            std::cout << "Sorry, you can't bet 0 dollars.\n";

            std::this_thread::sleep_for(std::chrono::milliseconds(250));
            std::cout << "Please enter a valid bet amount: ";
            std::cin >> bet;
        }
        if (bet > money) 
        {
            std::this_thread::sleep_for(std::chrono::milliseconds(250));
            std::cout << "Sorry, you're too broke for that.\n";

            std::this_thread::sleep_for(std::chrono::milliseconds(250));
            std::cout << "Please enter a valid bet amount: ";
            std::cin >> bet;
        }
    }
}

void ChoosePlayerAction()
{
    std::string action;
    bool IsValid = false;
    std::cout << "Would you like to hit or stand?";
    while(!IsValid)
    {
        std::cin >> action;
        if(action == "Hit" || action == "hit")
        {
            IsValid = true;
            PlayerCards.push_back(GetCardName(1 + ((std::time(nullptr) * rand()) % 13)));
            AddPlayerCardValues();
            if(PlayerValue < 21)
            {
                std::this_thread::sleep_for(std::chrono::milliseconds(250));
                std::cout << "You got a " << PlayerCards[PlayerCards.size() - 1] << " making up a value of " << PlayerValue << "!\n";
            }
        }
        else if(action == "Stand" || action == "stand")
        {
            IsValid = true;
            DidPlayerStand = true;
        }
        else
        {
            std::this_thread::sleep_for(std::chrono::milliseconds(250));
            std::cout << "Please enter a valid action: ";
        }
    }
}

void ChooseOppAction()
{
    int Chance = 1 + ((std::time(nullptr) * rand() * OppValue^2) % 10);
    if(Chance <= 21 - OppValue)
    {
        //Draw card
        OppCards.push_back(GetCardName(1 + ((std::time(nullptr) * rand() * OppValue^3) % 13)));
        AddOppCardValues();
        std::cout << "The opponent drew a card.\n";
    }
    else
    {
        std::cout << "The opponent stood.\n";
        DidOppStand = true;
    }
}

void AddPlayerCardValues()
{
    PlayerValue = 0;
    for(int i = 0; i < PlayerCards.size(); i++)
    {
        PlayerValue = PlayerValue + GetCardValue(PlayerCards[i]);
    }
}

void AddOppCardValues()
{
    OppValue = 0;
    for(int i = 0; i < OppCards.size(); i++)
    {
        OppValue = OppValue + GetCardValue(OppCards[i]);
    }
}

void EndGameConditionals()
{
    std::this_thread::sleep_for(std::chrono::milliseconds(250));
    if(PlayerValue == 21)
    {
        if(OppValue == 21)
        {
            std::this_thread::sleep_for(std::chrono::milliseconds(250));
            std::cout << "You drew a " << PlayerCards[PlayerCards.size() - 1] << ".\nIt's a draw!\n You both got a value of " << OppValue << "!\n";
        }
        else
        {
            std::cout << "You got a " << PlayerCards[PlayerCards.size() - 1] << " making up a value of " << PlayerValue << " meaning you won!\n";
            std::this_thread::sleep_for(std::chrono::milliseconds(250));
            std::cout << "The opponent had a value of " << OppValue << ".\n";
            money += bet;
        }
    }
    else if (PlayerValue > 21)
    {
        if(OppValue > 21)
        {
            std::cout << "You both busted meaning it's a draw!\nYou got a " << PlayerCards[PlayerCards.size() - 1] << " making a value of " << PlayerValue << "\nThe opponent had a value of " << OppValue << ".\n";
        }
        std::cout << "You got a " << PlayerCards[PlayerCards.size() - 1] << " and busted!\n";
        std::this_thread::sleep_for(std::chrono::milliseconds(250));
        std::cout << "The opponent had a value of " << OppValue << ".\n";
        money -= bet;
    }
    else if (OppValue == 21)
    {
        std::cout << "You lost because the opponent got a value of " << OppValue << ". :(\n";
        money -= bet;
    }
    else if (OppValue > 21)
    {
        std::cout << "You won because the opponent busted with a value of " << OppValue << "!\n";
        money += bet;
    }
    else
    {
        if(PlayerValue > OppValue)
        {
            std::cout << "You won!\nThe opponent had a value of " << OppValue << "!\n";
            money += bet;
        }
        if(PlayerValue < OppValue)
        {
            std::cout << "You lost.\nThe opponent had a value of " << OppValue << "!\n";
            money -= bet;
        }
        if(PlayerValue == OppValue)
        {
            std::cout << "Its a draw!\nYou both had a value of " << OppValue << "!\n";
        }
        
    }
}

int GetCardValue(std::string CardName)
{
    if(CardName == "Ace")
    {
        if(PlayerValue > 10)
        {
            return 1;
        }
        if(PlayerValue < 11)
        {
            return 11;
        }
    }
    std::map<std::string, int> CardRelations = { {"Two", 2}, {"Three", 3}, {"Four", 4}, {"Five", 5}, {"Six", 6}, {"Seven", 7}, {"Eight", 8}, {"Nine", 9}, {"Ten", 10}, {"Jack", 10}, {"Queen", 10}, {"King", 10} };
    if(CardRelations.count(CardName) == 1)
    {
        return CardRelations.at(CardName);
    }
    return 0;
}

std::string GetCardName(int CardNumber)
{
    static const std::string CardDeck[] = {"Ace", "Two", "Three", "Four", "Five", "Six", "Seven", "Eight", "Nine", "Ten", "Jack", "Queen", "King"};
    if(CardNumber > 0 & CardNumber < 14)
    {
        return CardDeck[CardNumber - 1];
    }
    return "Invalid";
}

int main()
{
    srand(std::time(nullptr));
    bool IsPlaying = true;
    std::cout << "Welcome to Black Jack!\n";
    while(IsPlaying)
    {
        NewRound();

        std::string IsPlayingPrompt;
        std::this_thread::sleep_for(std::chrono::milliseconds(250));
        if(money == 0)
        {
            std::cout << "Oh no! You lost all your money! Would you like to restart?";
            bool IsAnswering = true;
            while(IsAnswering)
            {
                std::cin >> IsPlayingPrompt;
                if(IsPlayingPrompt == "No" || IsPlayingPrompt == "no")
                {
                    IsPlaying = false;
                    IsAnswering = false;
                }
                else if(IsPlayingPrompt != "Yes" & IsPlayingPrompt != "yes")
                {
                    std::this_thread::sleep_for(std::chrono::milliseconds(250));
                    std::cout << "Please enter a valid answer: ";
                }
                else
                {
                    IsAnswering = false;
                    money = 500;
                }
            }
        }
        else
        {
            std::cout << "You now have " << money << " dollars.\nWould you like to keep playing?";
            bool IsAnswering = true;
            while(IsAnswering)
            {
                std::cin >> IsPlayingPrompt;
                if(IsPlayingPrompt == "No" || IsPlayingPrompt == "no")
                {
                    IsPlaying = false;
                    IsAnswering = false;
                }
                else if(IsPlayingPrompt != "Yes" & IsPlayingPrompt != "yes")
                {
                    std::this_thread::sleep_for(std::chrono::milliseconds(250));
                    std::cout << "Please enter a valid answer: ";
                }
                else
                {
                    IsAnswering = false;
                }
            }
        }
    }
    return 0;
    
}
