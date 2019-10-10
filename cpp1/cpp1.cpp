// cpp1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
// C
#ifndef _GLIBCXX_NO_ASSERT
#include <cassert>
#endif
#include <cctype>
#include <cerrno>
#include <cfloat>
#include <ciso646>
#include <climits>
#include <clocale>
#include <cmath>
#include <csetjmp>
#include <csignal>
#include <cstdarg>
#include <cstddef>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <cwchar>
#include <cwctype>

#if __cplusplus >= 201103L
#include <ccomplex>
#include <cfenv>
#include <cinttypes>
#include <cstdalign>
#include <cstdbool>
#include <cstdint>
#include <ctgmath>
#include <cuchar>
#endif

// C++
#include <algorithm>
#include <bitset>
#include <complex>
#include <deque>
#include <exception>
#include <fstream>
#include <functional>
#include <iomanip>
#include <ios>
#include <iosfwd>
#include <iostream>
#include <istream>
#include <iterator>
#include <limits>
#include <list>
#include <locale>
#include <map>
#include <memory>
#include <new>
#include <numeric>
#include <ostream>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <stdexcept>
#include <streambuf>
#include <string>
#include <typeinfo>
#include <utility>
#include <valarray>
#include <vector>

#if __cplusplus >= 201103L
#include <array>
#include <atomic>
#include <chrono>
#include <codecvt>
#include <condition_variable>
#include <forward_list>
#include <future>
#include <initializer_list>
#include <mutex>
#include <random>
#include <ratio>
#include <regex>
#include <scoped_allocator>
#include <system_error>
#include <thread>
#include <tuple>
#include <typeindex>
#include <type_traits>
#include <unordered_map>
#include <unordered_set>
#endif

#if __cplusplus >= 201402L
#include <shared_mutex>
#endif

#if __cplusplus >= 201703L
#include <any>
#include <charconv>
// #include <execution>
#include <filesystem>
#include <optional>
#include <memory_resource>
#include <string_view>
#include <variant>
#endif

#if __cplusplus > 201703L
#include <bit>
// #include <compare>
// #include <concepts>
#include <numbers>
// #include <ranges>
// #include <span>
// #include <syncstream>
#include <version>
#endif

using namespace std;

class Player
{
   public:
	int id;
	string name;
    int totalScore;

     Player(int id1, string name1)
	{
		id = id1;
		name = name1;
		totalScore = 0;
	}

	void addScore(int score)
	{
		totalScore += score;
	}

	int getID()
	{
		return id;
	}

	string getName()
	{
		return name;
	}

	int getScore()
	{
		return totalScore;
	}
};


class Lane
{
public:
	int id;
	int maxPlayers;
	int numPlayers;
	int price;

	Lane() {
		id = -1;
		maxPlayers = -1;
		price = -1;
	}

	    Lane(int id1, int maxPlayers1, int price1) {
		id = id1;
		maxPlayers = maxPlayers1;
		price = price1;
	}

    void setNumPlayers(int numPlayers1)
	{
		numPlayers = numPlayers1;
	}

	int getID() {
		return id;
	}

	int getMaxPlayers() {
		return maxPlayers;
	}

	int getNumPlayers() {
		return numPlayers;
	}

	int getPrice() {
		return price;
	}
};



class BowlingAlley
{
public:
	vector<Lane> lanes;	
	string s;
    set<int> bookedLanes;

	BowlingAlley() 
	{
		fstream file;
		string word, t, q, filename;

		Lane lane1(0001,10,100);
		lanes.push_back(lane1);
		filename = "";
		cout << "Enter the path of lanes.txt file:\n";
		cin >> filename;
        file.open(filename.c_str());
		cout << "\nFollowing lanes are available:\n\nLaneID, MaxNumberOfPlayersAllowed, PriceOfOneGame\n";
		cout << "0001,10,100" << endl;
        while (file >> word)
		{
			cout << word << endl; 
			
			char char_array[101];

			strcpy(char_array, word.c_str());

			char *token = strtok(char_array, ",");
			int id, numPlayers, price,count=0;
			while (token != NULL)
			{
				if(count==0) id= stoi(token);
				if(count==1) numPlayers= stoi(token);
				if(count==2) price= stoi(token);
				token = strtok(NULL, ",");
				count++;
			}
			Lane lane(id, numPlayers, price);
			lanes.push_back(lane);

		}
		
    }

	Lane getLaneByID(int id) 
	{
		bool found = false;
		int laneID;
		for (int i=0;i < lanes.size();i++)
		{
			if (lanes[i].getID() == id)
			{
				laneID=i;
				found = true;
			}
		}
		if(found) return lanes[laneID];
	 }


	bool bookLane(int laneID)
	{
		bool found = false; int i;
		for (i = 0; i < lanes.size(); i++)
		{
			if (lanes[i].getID() == laneID)
			{
				found = true;
				break;
			}
		}
		
		if (found)
		{
			if (bookedLanes.find(laneID) == bookedLanes.end())
				bookedLanes.insert({laneID});
			else
				printf("Lane with id is already booked.");
		}
		else
			printf("Entered lane id is invalid.");

		return found;
	}
};


struct strategy
{
	string strategyName;
	int chanceNumber;
	int standingPins;
	int bonus;

	strategy(string s,int i,int j,int k) 
	{
		strategyName = s;
		chanceNumber = i;
		standingPins = j;
		bonus = k;
	}
};



class Game
{
public:
	 Lane lane;
	 vector<Player> players;
	 vector<strategy> strategies;
	 int numSets = 5;
	 int chancePerSets = 2;
	 int counter = 0;

    Game(Lane lane1, vector<Player> players1, vector<strategy> strategies1)
	{
		lane = lane1;
		players = players1;
		strategies = strategies1;
	}

	void start()
	{
		counter = 0;
		numSets = 10;
		while (counter < numSets)
		{

			printf("\nSet number %d of chances:\n", counter + 1);
			for (auto itr=players.begin();itr!=players.end();itr++) 
			{
				int standingPins = 10;
				int totalPinDown = 0;
				for (int i = 0; i < chancePerSets && standingPins > 0; i++) 
				{
					int numPinDown = takeShot(standingPins);
					totalPinDown += numPinDown;
					standingPins -= numPinDown;
					bool NoStrategyWorked = true;
					for (auto pi = strategies.begin(); pi != strategies.end(); pi++)
					{
						if (i == (*pi).chanceNumber && (*pi).standingPins == standingPins)
						{
							printf("There's a %s by player %s\n", (*pi).strategyName.c_str() ,(*itr).getName().c_str());
							(*itr).addScore(numPinDown + (*pi).bonus);
							NoStrategyWorked = false;
							break;
						}
					}

					if (NoStrategyWorked)
					{
						printf("%s pinned down %d pins in #%d roll.\n", (*itr).getName().c_str(), numPinDown, (i + 1));
						(*itr).addScore(numPinDown);
					}

				}
			}
			counter++;
		}
	}

	string getWinner()
	{
		int maxScore = -1, score;
		string name;
		printf("\n\n*****************Score Board*******************\n");
		for (auto itr=players.begin();itr!=players.end();itr++)
		{
			score = (*itr).getScore();
			printf("Total score of %s is %d.\n",(*itr).getName().c_str(),score);
			if (score > maxScore)
			{
				maxScore = (*itr).getScore();
				name = (*itr).getName();
			}
		}
		return name;
	}

	int takeShot(int standingPins)
	{
		return (rand() % (standingPins + 1));
	}
};


class BowlingAlleyTesting
{
public:
	int counter = 85721;

	vector<Player> getPlayerDetails()
	{
		vector<Player> players;
		printf("Enter total number of players:\n");
		int count; scanf("%d", &count);
		
		for (int i = 0; i < count; i++)
		{
			printf("Enter the player name:");
			string name; 
			cin >> name;
			Player player1(++counter, name);
			players.push_back(player1);
		}

		return players;
	}

	vector<strategy> getStrategies()
	{
		vector<strategy> strategies;
        strategy strategy01("strike",0,0,10);
		strategy strategy02("spare", 1, 0, 5);
		strategies.push_back(strategy01);
		strategies.push_back(strategy02);
		printf("\nStrategies present already are:");
		printf("\nstrategyName: %s, chanceNumber:%d , standingPins:%d , bonus:%d ",
			strategy01.strategyName.c_str(), strategy01.chanceNumber, strategy01.standingPins, strategy01.bonus);
		printf("\nstrategyName: %s, chanceNumber:%d , standingPins:%d , bonus:%d ",
			strategy02.strategyName.c_str(), strategy02.chanceNumber, strategy02.standingPins, strategy02.bonus);


		printf("\n\nEnter number of new strategies you want to add:\n");
		int count; scanf("%d", &count);

		for (int i = 2; i < count+2; i++)
		{
			string name; int chanceNumber, standingPins, bonus; 
			printf("Enter the strategy name:");
			cin >> name; 
			printf("Enter the chanceNumber:"); 
			cin >> chanceNumber;
			printf("Enter the standingPins remaining in above chanceNumber:"); 
			cin >> standingPins;
			printf("Enter the bonus points awarded in this strategy:"); 
			cin >> bonus;
			strategy strategy1(name, chanceNumber , standingPins , bonus);
			strategies.push_back(strategy1);
		}

		return strategies;
	}

	
};



int main()
{
	BowlingAlley alley;
	Lane lane;
	bool success = false; int start = 0;
    BowlingAlleyTesting BowlingAlleyTesting1;

	vector<strategy> strategies = BowlingAlleyTesting1.getStrategies();

	while (1)
	{
		printf("Start a new game? (Press 1 to start and 0 to quit:)\n"); 
		cin >> start;
		if (start == 1)
		{
			while (!success)
			{
				printf("\nChoose the lane you want to play in by entering the id:\n");
				int laneid;
				scanf("%d", &laneid);
				lane = alley.getLaneByID(laneid);
				success = alley.bookLane(laneid);
			}


			printf("\nEnter player details:\n");
			vector<Player> players = BowlingAlleyTesting1.getPlayerDetails();

			Game g1(lane, players, strategies);
			g1.start();
			string winnerofgame = g1.getWinner();
			cout << "***************************************\nWinner of this game is " + winnerofgame + 
				"\n#######################################\n\n\n\n\n\n";
		}
		else
			goto hell;
		
	}

    hell:;
}
