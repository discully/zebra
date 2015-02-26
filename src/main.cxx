#include <iostream>

#include "Game.hxx"
#include "Random.hxx"



//int main(int argc, char* argv[])
int main()
{
	zebra::Player *const player1 = new zebra::Random();
	zebra::Player *const player2 = new zebra::Random();
	std::pair<size_t,size_t> wins(0,0);
	
	zebra::Player* black = player1;
	zebra::Player* white = player2;
	const zebra::Player* winner = nullptr;
	zebra::Game g;//(black,white);
	
	for(size_t i = 0; i < 100; ++i)
	{
		std::swap(black, white);
		g.players(black, white);
		g.play();
		
		winner = g.winner();
		if( winner == player1 )
		{
			++(wins.first);
		}
		else
		{
			++(wins.second);
		}
		
		std::cout << ((winner == black) ? "Black" : "White") << " wins" << std::endl;
		//std::cout << "\n" << g << "\n" << std::endl;
	}
	
	std::cout << "Player 1 (" << player1->name() << ") " << wins.first << std::endl;
	std::cout << "Player 2 (" << player2->name() << ") " << wins.second << std::endl;
	
	delete player1;
	delete player2;
	
	return 0;
}
