#include <string>
#include "Card.h"
using namespace std;

Card::Card(string str){
		setSuit(str);
	};//constructor
char Card::getSuit()
	{
		 return suit;
	}
void Card::setSuit(string str){
		suit = str[0];
	}


		



