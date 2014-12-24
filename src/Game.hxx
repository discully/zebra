#ifndef ZEBRA_GAME_HXX
#define ZEBRA_GAME_HXX

#include "Board.hxx"



namespace zebra
{
	class Game;
	
	// Forward-declare
	class Player;
}



class zebra::Game
{
	public:
		
		Game();
		
		/// Constructs a new game with specified players
		Game(Player* black_player, Player* white_player);
		
		/// Copy-constructor copies the state of a game but not the actual
		/// players (the state of the board and knowledge who's turn it is
		/// will be copied).
		Game(const Game& game);
		
		/// The game board.
		/// \returns A reference to the game's board.
		const Board& board() const;
		
		
	private:
		
		/// The game's board.
		Board state;
		
		/// Pointer to the player representing black.
		Player* black;
		
		/// Pointer to the Player* who is next to play.
		Player** next;
		
		/// Pointer to the player representing white.
		Player* white;
};



#endif
