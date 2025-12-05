#include <iostream>
#include <limits>
#include <ctime>
#include <vector>
#include <thread>
#include <chrono>
#include <map>

int money = 500;
int bet;
int PlayerValue;
int OppValue;
bool DidPlayerStand = false;
bool DidOppStand = false;

void NewRound();
void PlaceBets();
void ChoosePlayerAction();
void ChooseOppAction();
void AddPlayerCardValues();
void AddOppCardValues();
void EndGameConditionals();

int GetCardValue(std::string CardName);
std::string GetCardName(int CardValue);
std::vector<std::string> PlayerCards;
std::vector<std::string> OppCards;
