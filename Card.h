#include <string>

class Card
{
private:
	char suit;

public:
	Card(std::string str);
	char getSuit();
	void setSuit(std::string str);
	
};

