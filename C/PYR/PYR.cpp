// PYR.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <tchar.h>
#include "stdlib.h"
#include <vector>
#include <fstream>
#include <algorithm>
#include <sstream>
#include <iostream>

//#include "Log.h"
//extern CLog glog;
//#define log(type, msg) glog.log2(type, msg, __FUNCTION__, __FILE__, __LINE__) 
//#define dlog(msg) glog.log2(glog.eDBUG, msg, __FUNCTION__, __FILE__, __LINE__) 
//#define trace() glog.log2(glog.eTRCE, "", __FUNCTION__, __FILE__, __LINE__) 
using namespace std;


//CLog glog;

struct Card
{
	Card(){}
	Card(const Card & card)
	{
		if(this != &card)
		{
			rank = card.rank;
			suit = card.suit;
		}
	}

	Card & operator= (const Card & card)
	{
		if(this!=&card)
		{
			rank = card.rank;
			suit = card.suit;
		}
		return *this;
	}

	Card(char r, char s): rank(r), suit(s){}

	void print() { std::cout << toString();}
	std::string toString() 
	{
		std::ostringstream oss;
		oss << rank << suit;
		return oss.str();
	}
	bool operator< (const Card & card)	//rank A, K, Q, J, 10, 9, 8, 7, 6, 5, 4, 3, 2   suit ace, space, heart, club
	{
		if (getRankOrder(rank) == getRankOrder(card.rank))
		{
			return (getSuitOrder(suit) < getSuitOrder(card.suit));
		}
		else
			return (getRankOrder(rank) < getRankOrder(card.rank));
	}
	bool operator> (const Card & card)	//rank A, K, Q, J, 10, 9, 8, 7, 6, 5, 4, 3, 2   suit ace, space, heart, club
	{
		if (getRankOrder(rank) == getRankOrder(card.rank))
		{
			return (getSuitOrder(suit) > getSuitOrder(card.suit));
		}
		else
			return (getRankOrder(rank) > getRankOrder(card.rank));
	}

	bool operator== (const Card& card)
	{
		return (getRankOrder(rank) == getRankOrder(card.rank)) && (getSuitOrder(suit) == getSuitOrder(card.suit));
	}

	int getRankOrderLo()
	{
		int order = getRankOrder();
		return (order == 14)? 1 : order;
	}

	int getRankOrder()
	{
		return getRankOrder(rank);
	}

	int getSuitOrder()
	{
		return getSuitOrder(suit);
	}

	int getRankOrder(char R)
	{
		switch(R)
		{
		case 'A':
		case 'a':
			return 14;
		case 'K':
		case 'k':
			return 13;
		case 'Q':
		case 'q':
			return 12;
		case 'J':
		case 'j':
			return 11;
		case '10':
		case '1':
			return 10;
		case '9':	return 9;
		case '8':	return 8;
		case '7':	return 7;
		case '6':	return 6;
		case '5':	return 5;
		case '4':	return 4;
		case '3':	return 3;
		case '2':	return 2;
		default:	return 0;
		}
	}

	int getSuitOrder(char S)
	{
		// this order is my presumption and can be changed
		switch(S)
		{
		case 'S':	// Spades
		case 's':
			return 4;
		case 'H':	// Hearts
		case 'h':
			return 3;
		case 'D':	// Diamonds
		case 'd':
			return 2;
		case 'C':	// Clubs
		case 'c':
			return 1;
		default: return 0;
		}
	}


	
//	enum order {A = 14, K=13, Q=12, J=11};

	char rank;
	char suit;
};

class OmahaHiLo
{
public:
	OmahaHiLo(const char* infile, const char* outfile): inputfile(infile), outputfile(outfile)
	{
		play();
	}

	~OmahaHiLo()
	{
	}

	void play()
	{
		// open input file for reading
		std::ifstream fin(inputfile);
		//std::ifstream fin;
		//fin.open("test.txt");
		//fin.open("test.txt", ios::in);
		std::string line;
		if(fin.is_open())
		{
			// read one line from input file and check the winner
			while(getline(fin, line))
			{
				std::cout << "\n\n***  " << line;
				std::vector<Card> handA, handB, board;

				// extract handA, handB and board cards
				getHandsBoardCards(line, handA, handB, board);

				// check who is winner
				checkWinner(handA, handB, board);
			}
			fin.close();
		}
		else std::cout << "unable to open the file to read\n";
	}

	// this function takes one line from input file and extracts handA, handB and Board cards
	void getHandsBoardCards(const std::string& line, std::vector<Card>& handA, std::vector<Card>& handB, std::vector<Card>& board)
	{
		//std::cout << line << std::endl;

		// HandA:Ac-Kd-Jd-3d HandB:5c-5d-6c-7d Board:Ah-Kh-5s-2s-Qd
		// HandA:Ac-Kd-Jd-3d HandB:5c-5d-6c-6d Board:Ad-Kh-5s-2d-Qd
		char* token		= NULL;
		char* context	= NULL;
		char  delims[]	= " ";//" ,\t\n";

		// During the first read, establish the char string and get the first token.
		token = strtok_s((char*)line.c_str(), delims, &context);

		// extract 3 HandsA, HandsB and Board
		int i=0;
		while (token != NULL)
		{
			// remove titles (HandsA, HandsB, Board)
			std::string str(token);
			int idx = str.find(":");
			std::string sCards = str.substr(str.find(":")+1);
			//std::cout << " " << sCards;
			switch(i)
			{
			case 0:	// HandA
				getCards(sCards, handA);
				//std::cout << "\n" << __FUNCTION__ << " " << sCards; printHand(", handA:", handA);
				break;

			case 1:	// HandB
				getCards(sCards, handB);
				//std::cout << "\n" << __FUNCTION__ << " " << sCards; printHand(", handA:", handA);
				break;

			case 2:	// Board
				getCards(sCards, board);
				//std::cout << "\n" << __FUNCTION__ << " " << sCards; printHand(", board:", board);
				break;
			}

			// NOTE: NULL, function just re-uses the context after the first read.
			token = strtok_s(NULL, delims, &context); 
			++i;
		}
		//std::cout << "\n";

	}

	// this function checks who is winner between A and B and returns accordingly
	char checkWinner(const std::vector<Card> handA, const std::vector<Card> handB, const std::vector<Card> board)
	{
		//printHand("\nHandA:", handA);		printHand(", HandB:", handB);		printHand(", Board:", board);

		// get high/low combinations for player A
		std::vector<Card> handAHi, handALo;
		std::string sRankHiA = getHiCombination(handA, board, handAHi);
		std::string sRankLoA = getLoCombination(handA, board, handALo);

		// get high/low combinations for player B
		std::vector<Card> handBHi, handBLo;
		std::string sRankHiB = getHiCombination(handB, board, handBHi);
		std::string sRankLoB = getLoCombination(handB, board, handBLo);

		// compare Hi's
		std::string sWinnerHiRank = "";
		char cHiWinner = findHigh(handAHi, handBHi);
		std::ostringstream ossHi;
		if(cHiWinner == 'A')
		{
			ossHi << sRankHiA << " ";
			auto itr = handAHi.begin();
			while(itr != handAHi.end())
			{
				ossHi << itr->rank;
				++itr;
			}
		}
		else if(cHiWinner == 'B')
		{
			ossHi << sRankHiB << " ";
			auto itr = handBHi.begin();
			while(itr != handBHi.end())
			{
				ossHi << itr->rank;
				++itr;
			}
		}
		else
		{
			ossHi << "It is a tie and pot will be split";
		}
		std::cout << "\n=> Hand" << cHiWinner << " wins Hi (" << ossHi.str() << ");";

		//if(cHiWinner == '=')
		//{
		//	// special case
		//	std::cout << "\n=> It is a tie and pot will be split";
		//}
		//else
		//{
		//	std::string sWinnerHiRank = (cHiWinner == 'A')? sRankHiA : sRankHiB;
		//	std::cout << "\n=> Hand" << cHiWinner << " wins Hi (" << sWinnerHiRank << ");";
		//}

		// compare Lo's
		char cLoWinner = findLow(handALo, handBLo);
		std::string sWinnerLoRank = (cLoWinner == 'A')? sRankLoA : sRankLoB;

		std::ostringstream ossLo;
		if(cLoWinner == 'A')
		{
			auto itr = handALo.begin();
			while(itr != handALo.end())
			{
				ossLo << itr->rank;
				++itr;
			}
		}
		else if(cLoWinner == 'B')
		{
			auto itr = handBLo.begin();
			while(itr != handBLo.end())
			{
				ossLo << itr->rank;
				++itr;
			}
		}
		else
		{
			ossLo << "Not qualified";
		}
		std::cout << "  \t Hand" << cLoWinner << " wins Lo (" << ossLo.str() << ");";

		return 0;
	}

	void getCards(const std::string& sCards, std::vector<Card>& hand)
	{
		// Ac-Kd-Jd-3d
		char* token		= NULL;
		char* context	= NULL;
		char  delims[]	= "-";

		// During the first read, establish the char string and get the first token.
		token = strtok_s((char*)sCards.c_str(), delims, &context);

		// extract 3 HandsA, HandsB and Board
		int i=0;
		while (token != NULL)
		{
			Card card;
			if(strlen(token)==2){
			card.rank = token[0];
			card.suit = token[1];
			}else{				// to cater for 10s, 10h, 10c, 10d
			card.rank = token[0];
			card.suit = token[2];
			}
			hand.push_back(card);

			// NOTE: NULL, function just re-uses the context after the first read.
			token = strtok_s(NULL, delims, &context); 
			++i;
		}
		
		//std::cout << "\n" << __FUNCTION__ << " " << sCards << " "; printHand("", hand);
	}

	// this function takes hand and board cards and returns handHi containing highest possible combination for Omaha Hi
	std::string getHiCombination(const std::vector<Card>& hand, const std::vector<Card>& board, std::vector<Card>& handHi)
	{
		// combinations for hand = n!/(r!(n-r)!) => 4!/(2!(4-2)!) => 6
		// combinations for board = n!/(r!(n-r)!) => 5!/(3!(5-3)!) => 10
		// total combinations = 6 x 10 => 60

		// create hand combinations
		std::vector<std::vector<Card>> handCombi;
		getCombi(hand, 0, 2, handCombi);
		//std::cout << "\n" << __FUNCTION__ << " size=" << handCombi.size();

		// create board combinations
		std::vector<std::vector<Card>> boardCombi;
		getCombi(board, 0, 3, boardCombi);
		//std::cout << "\n" << __FUNCTION__ << " size=" << boardCombi.size();

		// create mix of all combinations of hand and board
		//cout << "\n" << __FUNCTION__ << ":" << __LINE__ << " handCombi size=" << handCombi.size() << ", boardCombi size=" << boardCombi.size();
		std::vector<std::vector<Card>> combiA;
		auto it1 = handCombi.begin();
		while(it1 != handCombi.end())
		{
			auto it2 = boardCombi.begin();
			while(it2 != boardCombi.end())
			{
				vector<Card> temp;
				temp.insert(temp.end(), it1->begin(), it1->end());
				temp.insert(temp.end(), it2->begin(), it2->end());
				//printHand("", temp);

				// sort temp. It will be beneficient while
				std::sort(temp.rbegin(), temp.rend());
				combiA.push_back(temp);
				++it2;
			}			
			++it1;
		}
		//cout << "\n" << __FUNCTION__ << ":" << __LINE__ << " " << combiA.size();
		
		// print cmobinations
		auto itr = combiA.begin();
		while(itr != combiA.end())
		{
			//printHand("\n", *itr);
			++itr;
		}

		// find out highest combination
		// iterate thru each combination and check for various ranks
		//cout << "\n" << __FUNCTION__ << ":" << __LINE__ << " iterating thru all combination to find best rank";

		// checking each rank for all combinations

		// check if strgight flush
		if(isStraightFlush(combiA, handHi)) { return "Straight Flush"; }

		// check if	4-of-kind
		if(is4OfAKind(combiA, handHi)) { return "4-of-kind"; }

		// check if	Full house
		if(isFullHouse(combiA, handHi)) { return "Full house"; }

		// check if	Flush
		if(isFlush(combiA, handHi)) { return "Flush"; }

		// check if	Straight
		if(isStraight(combiA, handHi)) { return "Straight"; }

		// check if	3-of-kind
		if(is3OfAKind(combiA, handHi)) { return "3-of-kind"; }

		// check if	Two Pair
		if(isTwoPair(combiA, handHi)) { return "Two Pair"; }

		// check if	One Pair
		if(isOnePair(combiA, handHi)) { return "One Pair"; }

		// find High Card
		findHighCard(combiA, handHi);
		return "High Card";
	}

	// this function takes hand and board cards and returns handHi containing highest possible combination for Omaha Lo
	std::string  getLoCombination(const std::vector<Card>& hand, const std::vector<Card>& board, std::vector<Card>& handLo)
	{
		// combinations for hand = n!/(r!(n-r)!) => 4!/(2!(4-2)!) => 6
		// combinations for board = n!/(r!(n-r)!) => 5!/(3!(5-3)!) => 10
		// total combinations = 6 x 10 => 60

		// create hand combinations
		std::vector<std::vector<Card>> handCombi;
		getCombi(hand, 0, 2, handCombi);
		//std::cout << "\n" << __FUNCTION__ << " size=" << handCombi.size();

		// create board combinations
		std::vector<std::vector<Card>> boardCombi;
		getCombi(board, 0, 3, boardCombi);
		//std::cout << "\n" << __FUNCTION__ << " size=" << boardCombi.size();

		// create mix of all combinations of hand and board
		//cout << "\n" << __FUNCTION__ << ":" << __LINE__ << " handCombi size=" << handCombi.size() << ", boardCombi size=" << boardCombi.size();
		std::vector<std::vector<Card>> combiA;
		auto it1 = handCombi.begin();
		while(it1 != handCombi.end())
		{
			//All 5 cards should have different rank
			if((*it1)[0].rank != (*it1)[1].rank)
			{
				//None of the cards should be higher than 8
				if( ((*it1)[0].getRankOrderLo() <= 8) && ((*it1)[1].getRankOrderLo()<= 8) )
				{
					auto it2 = boardCombi.begin();
					while(it2 != boardCombi.end())
					{
						//All 5 cards should have different rank
						if((*it2)[0].rank != (*it2)[1].rank != (*it2)[2].rank)
						{
							//None of the cards should be higher than 8
							if( ((*it2)[0].getRankOrderLo() <= 8) && ((*it2)[1].getRankOrderLo()<= 8)  && ((*it2)[2].getRankOrderLo()<= 8) )
							{
								vector<Card> temp;
								temp.insert(temp.end(), it1->begin(), it1->end());
								temp.insert(temp.end(), it2->begin(), it2->end());
								//printHand("", temp);

								// sort temp. It will be beneficient while
								std::sort(temp.rbegin(), temp.rend());
								combiA.push_back(temp);
							}
						}
						++it2;
					}
				}
			}
			++it1;
		}
		//cout << "\n" << __FUNCTION__ << ":" << __LINE__ << " " << combiA.size();
		
		// print cmobinations
		if(combiA.size()>0)
		{
			auto itr = combiA.begin();
			//cout << "\n" << __FUNCTION__ << ":" << __LINE__ << " " << "Lows";
			while(itr != combiA.end())
			{
				//printHand("\n", *itr);
				++itr;
			}
		}

		if(combiA.size() > 0)
		{
			// find Low Card
			findLowCard(combiA, handLo);
			return "Low Card";
		}
		else
			return "No qualified";
	}

	// this method compares hi's of two players and returns either 'A' or 'B'
	//char compareHighs(const std::vector<Card> handA, const std::vector<Card> handB)
	//{
	//	return isAGreater(handA, handB)? 'A' : 'B';
	//}

	//// this method compares lo's of two players and returns either 'A' or 'B' or 0 if no one qualifies
	//char compareLows(const std::vector<Card> handA, const std::vector<Card> handB)
	//{
	//	// hand containing higher card loses
	//	return isALower(handA, handB)? 'B' : 'A';
	//}

	// this function generate all possible combinations taken r elements at a time
	vector<Card> combination;
	void getCombi(const std::vector<Card> cards, int offset, int k, vector<vector<Card> >& comb)
	{
	  if (k == 0) {
		comb.push_back(combination);

		std::ostringstream oss;
		//oss << " Input=";
		auto it = combination.begin();
		while(it != combination.end())
		{
			Card card = *it;
			oss << card.toString() << " ";
			++it;
		}
		//cout << "\n"	<< oss.str();
		return;
	  }
	  for (unsigned int i = offset; i <= (cards.size() - k); ++i) {
		combination.push_back(cards[i]);
		getCombi(cards, i+1, k-1, comb);
		combination.pop_back();
	  }
	}
	void combinations(vector<vector<int> > array, int i, vector<int> accum, vector<vector<int> >& comb)
	{
		if (i == array.size()) // done, no more rows
		{
			comb.push_back(accum); // assuming comb is global
		}
		else
		{
			vector<int> row = array[i];
			for(unsigned int j = 0; j < row.size(); ++j)
			{
				vector<int> tmp(accum);
				tmp.push_back(row[j]);
				combinations(array,i+1,tmp, comb);
			}
		}
	}


	int generateCombinations(const std::vector<Card> cards, int r, std::vector<std::vector<Card>> outCombi)
	{
		//printHand("\nInput=", cards);
		std::ostringstream oss;
		oss << " Input=";
		auto it = cards.begin();
		while(it != cards.end())
		{
			Card card = *it;
			oss << card.toString() << " ";
			++it;
		}
		oss << "Combis:";

		auto itr = cards.begin();
		while(itr != (cards.end()-r+2))
		{
			auto itr2 = itr+1;
			while(itr2 != (cards.end()-r+2))
			{
				std::vector<Card> cardset;
				cardset.push_back(*itr);
				oss << itr->rank << itr->suit << " ";
				for(int i=0; i < (r-1); i++)
				{
					Card card = *(itr2+i);
					cardset.push_back(card);
					oss << itr->rank << itr->suit << " ";
				}
				outCombi.push_back(cardset);
				oss << ", ";
				//printHand(",", cardset);
				++itr2;
			}
			++itr;
		}
		std::cout << "\n" << __FUNCTION__ << ":" << __LINE__ << oss.str();
		return outCombi.size();
	}

	bool isStraightFlush(const std::vector<std::vector<Card>>& combi, std::vector<Card>& cards5)
	{
		auto itr = combi.begin();
		while(itr != combi.end())
		{
			if(isStraightFlush(*itr))
			{
				cards5.clear();
				cards5.insert(cards5.end(), itr->begin(), itr->end());
				return true;
			}
			++itr;
		}
		return false;
	}

	bool is4OfAKind(const std::vector<std::vector<Card>>& combi, std::vector<Card>& cards5)
	{
		auto itr = combi.begin();
		while(itr != combi.end())
		{
			if(is4OfAKind(*itr))
			{
				cards5.clear();
				cards5.insert(cards5.end(), itr->begin(), itr->end());
				return true;
			}
			++itr;
		}
		return false;
	}

	bool isFullHouse(const std::vector<std::vector<Card>>& combi, std::vector<Card>& cards5)
	{
		auto itr = combi.begin();
		while(itr != combi.end())
		{
			if(isFullHouse(*itr))
			{
				cards5.clear();
				cards5.insert(cards5.end(), itr->begin(), itr->end());
				return true;
			}
			++itr;
		}
		return false;
	}

	bool isFlush(const std::vector<std::vector<Card>>& combi, std::vector<Card>& cards5)
	{
		auto itr = combi.begin();
		while(itr != combi.end())
		{
			if(isFlush(*itr))
			{
				cards5.clear();
				cards5.insert(cards5.end(), itr->begin(), itr->end());
				return true;
			}
			++itr;
		}
		return false;
	}

	bool isStraight(const std::vector<std::vector<Card>>& combi, std::vector<Card>& cards5)
	{
		auto itr = combi.begin();
		while(itr != combi.end())
		{
			if(isStraight(*itr))
			{
				cards5.clear();
				cards5.insert(cards5.end(), itr->begin(), itr->end());
				return true;
			}
			++itr;
		}
		return false;
	}

	bool is3OfAKind(const std::vector<std::vector<Card>>& combi, std::vector<Card>& cards5)
	{
		auto itr = combi.begin();
		while(itr != combi.end())
		{
			if(is3OfAKind(*itr))
			{
				cards5.clear();
				cards5.insert(cards5.end(), itr->begin(), itr->end());
				return true;
			}
			++itr;
		}
		return false;
	}

	bool isTwoPair(const std::vector<std::vector<Card>>& combi, std::vector<Card>& cards5)
	{
		auto itr = combi.begin();
		while(itr != combi.end())
		{
			if(isTwoPair(*itr))
			{
				cards5.clear();
				cards5.insert(cards5.end(), itr->begin(), itr->end());
				return true;
			}
			++itr;
		}
		return false;
	}

	bool isOnePair(const std::vector<std::vector<Card>>& combi, std::vector<Card>& cards5)
	{
		auto itr = combi.begin();
		while(itr != combi.end())
		{
			if(isOnePair(*itr))
			{
				cards5.clear();
				cards5.insert(cards5.end(), itr->begin(), itr->end());
				return true;
			}
			++itr;
		}
		return false;
	}

	bool findHighCard(const std::vector<std::vector<Card>>& combi, std::vector<Card>& cards5)
	{
		if(combi.size() == 0)
			return false;
		if(combi.size() == 1)
		{
			cards5 = combi[0];
			return true;
		}

		auto it1 = combi.begin();
		auto highCard = *it1;
		while(it1 != combi.end())
		{
			auto it11 = it1->begin();
			if(isAGreater(*it1, highCard))
			{
				highCard = *it1;
			}
			++it1;
		}
		cards5 = highCard;
		//cout << "\n" << __FUNCTION__ << ":" << __LINE__; printHand("highCard=", highCard);
		return true;
	}

	bool findLowCard(const std::vector<std::vector<Card>>& combi, std::vector<Card>& cards5)
	{
		if(combi.size() == 0)
			return false;
		if(combi.size() == 1)
		{
			cards5 = combi[0];
			return true;
		}

		auto it1 = combi.begin();
		auto lowCard = *it1;
		while(it1 != combi.end())
		{
			auto it11 = it1->begin();
			if(!isAGreater(*it1, lowCard))
			{
				lowCard = *it1;
			}
			++it1;
		}
		cards5 = lowCard;
		//cout << "\n" << __FUNCTION__ << ":" << __LINE__; printHand("lowCard=", lowCard);
		return true;
	}

	bool isAGreater(const std::vector<Card>& A, const std::vector<Card> & B)
	{
		auto itrA = A.begin();
		auto itrB = B.begin();
		for(unsigned i=0; i<A.size(); i++)
		{
			Card a = A[i];
			Card b = B[i];
			if (a == b)
				continue;
			return (a > b);
		}
		return false;
	}

	bool isALower(const std::vector<Card>& A, const std::vector<Card> & B)
	{
		auto itrA = A.begin();
		auto itrB = B.begin();
		for(unsigned i=0; i<A.size(); i++)
		{
			Card a = A[i];
			Card b = B[i];
			if (a == b)
				continue;
			return (a.getRankOrderLo() < b.getRankOrderLo());
		}
		return false;
	}

	// compares two set of hands/cards and return 'A' if A > B or return 'B' if B > A otherwise return '='
	char findHigh(const std::vector<Card>& A, const std::vector<Card> & B)
	{
		//cout << "\n" << __FUNCTION__ << ":" << __LINE__; printHand(" A=>", A);printHand(", B=", B); cout << " A size=" << A.size() << " B size=" << B.size();

		if(A.size() == B.size() == 0)
		{
			return '=';
		}
		if(A.size() > 0 && B.size()==0 )
		{
			return 'A';
		}
		if(B.size() > 0 && A.size()==0 )
		{
			return 'B';
		}

		auto itrA = A.begin();
		auto itrB = B.begin();
		for(unsigned i=0; i<A.size(); i++)
		{
			Card a = A[i];
			Card b = B[i];
			if (a == b)
				continue;
			return (a.getRankOrder() > b.getRankOrder())? 'A' : 'B';
		}
		return '=';
	}

	// compares two set of hands/cards and return 'A' if A > B or return 'B' if B > A otherwise return '='
	char findLow(const std::vector<Card>& A, const std::vector<Card> & B)
	{
		//cout << "\n" << __FUNCTION__ << ":" << __LINE__; printHand(" A=>", A);printHand(", B=", B); cout << " A size=" << A.size() << " B size=" << B.size();

		if(A.size() == B.size() == 0)
		{
			return '=';
		}
		if(A.size() > 0 && B.size()==0 )
		{
			return 'A';
		}
		if(B.size() > 0 && A.size()==0 )
		{
			return 'B';
		}

		auto itrA = A.begin();
		auto itrB = B.begin();
		for(unsigned i=0; i<A.size(); i++)
		{
			Card a = A[i];
			Card b = B[i];
			if (a == b)
				continue;
			return (a.getRankOrderLo() < b.getRankOrderLo())? 'A' : 'B';
		}
		//cout << __FUNCTION__ << ":" << __LINE__ << " equal";
		return '=';
	}

	bool isStraightFlush(std::vector<Card> cards5)
	{
		//std::sort(cards5.begin(), cards5.end());
		//cout << "\n" << __FUNCTION__ << ":" << __LINE__; printHand(" ", cards5);
		if(cards5[0].suit == cards5[1].suit == cards5[2].suit == cards5[3].suit == cards5[4].suit)
		{
			//cards are already sorted so we can compare their ranks
			if(cards5[0].getRankOrder() == (cards5[1].getRankOrder()+1) == (cards5[2].getRankOrder()+2) == (cards5[3].getRankOrder()+3) == (cards5[4].getRankOrder()+4))
			{
				return true;
			}
		}
		return false;
	}

	bool is4OfAKind(std::vector<Card> cards5)
	{
		// any 4 cards of the same rank
		// since cards are already sorted so we can compare either flanks
		if( (cards5[0].rank == cards5[1].rank == cards5[2].rank == cards5[3].rank ) 
		|| 	(cards5[1].rank == cards5[2].rank == cards5[3].rank == cards5[4].rank ) )
			return true;
		else
			return false;
	}

	bool isFullHouse(std::vector<Card> cards5)
	{
		// any 3 cards of same rank together with any 2 cards of same rank
		// since cards are sorted so a straight comparison
		if( ((cards5[0].rank == cards5[1].rank == cards5[2].rank) && (cards5[3].rank == cards5[4].rank))
			||
		 	((cards5[0].rank == cards5[1].rank) && (cards5[2].rank == cards5[3].rank == cards5[4].rank))  )
			return true;
		else
			return false;
	}

	bool isFlush(std::vector<Card> cards5)
	{
		// any 5 cards of same suit (non consecutive)
		if( cards5[0].suit == cards5[1].suit == cards5[2].suit == cards5[3].suit == cards5[4].suit )
			return true;
		else
			return false;
	}

	bool isStraight(std::vector<Card> cards5)
	{
		// any 5 consecutive cards of different suit
		// since cards are sorted so a straight comparison
		if(cards5[0].getRankOrder() == (cards5[1].getRankOrder()+1) == (cards5[2].getRankOrder()+2) == (cards5[3].getRankOrder()+3) == (cards5[4].getRankOrder()+4))
			return true;
		else
			return false;
	}

	bool is3OfAKind(std::vector<Card> cards5)
	{
		// any 3 cards of same rank
		// since cards are sorted so a straight comparison
		if( (cards5[0].rank == cards5[1].rank == cards5[2].rank)
		||  (cards5[1].rank == cards5[2].rank == cards5[3].rank)
		||  (cards5[2].rank == cards5[3].rank == cards5[4].rank)  )
			return true;
		else
			return false;
	}

	bool isTwoPair(std::vector<Card> cards5)
	{
		// any 2 cards of the same rank together with any 2 cards of the same rank
		// since cards are sorted so a straight comparison
		if( ((cards5[0].rank == cards5[1].rank) && ((cards5[2].rank == cards5[3].rank) || (cards5[3].rank == cards5[4].rank)))
		||  ((cards5[1].rank == cards5[2].rank) &&  (cards5[3].rank == cards5[4].rank)) )
			return true;
		else
			return false;
	}

	bool isOnePair(std::vector<Card> cards5)
	{
		// any 2 cards of the same rank
		// since cards are sorted so a straight comparison
		if( (cards5[0].rank == cards5[1].rank) || (cards5[1].rank == cards5[2].rank)
		 || (cards5[2].rank == cards5[3].rank) || (cards5[3].rank == cards5[4].rank) )
			return true;
		else
			return false;
	}

	//bool isHighCard(std::vector<Card> cards5)
	//{
	//	return true;
	//}

	void printHand(std::string tag, std::vector<Card> hand)
	{
		std::cout << tag;
		auto itr = hand.begin();
		while(itr != hand.end())
		{
			std::cout << itr->rank << itr->suit << " ";
			itr++;
		}
	}


protected:
	const char*	inputfile;
	const char*	outputfile;

};


int _tmain(int argc, _TCHAR* argv[])
{
	//trace();
	//dlog("this is debug log");
	//log(glog.eINFO, "this is info log");
	//log(glog.eWARN, "this is warning log");
	//log(glog.eERRR, "this is error log");
	//log(glog.eTRCE, "this is trace log");
	//log(glog.eEXCP, "this is exception log");
	//log(glog.eDBUG, "this is debug log");


	//_tprintf(_T("/%s"), __targv[0]);
	//std::wcout << argv[0];
	std::cout << __targv[0] << std::endl;

	//
	OmahaHiLo pyr(argv[1], argv[2]);

	return 0;
}
