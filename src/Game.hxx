#ifndef ZEBRA_GAME_HXX
#define ZEBRA_GAME_HXX

#include "Board.hxx"



namespace zebra
{
	class Game;
}



class zebra::Game
{
	public:
		
		Game();
		
		//Game(Player* black_player, Player* white_player);
	
		Game(const Game& game);
		
		const Board& board() const;
		
	private:
		
		Board state;
		//Player* black;
		//Player* next;
		//Player* white;
};



#endif
