#ifndef ZEBRA_PLAYER_HXX
#define ZEBRA_PLAYER_HXX

#include <vector>

#include "Move.hxx"



namespace zebra
{
	class Player;
	
	// Forward-declare
	class Game;
}



class zebra::Player
{
	public:
		
		Player();
		
		/// Copy-constructor copies every aspect of the player with the
		/// exception of the current game, which is initialised to \c nullptr.
		Player(const Player& p);
		
		/// Copy-assignment copies every aspect of the player with the
		/// exception of the current game, which is left unchanged.
		Player& operator= (const Player& p);
		
		/// Get the current game being played.
		/// \returns A pointer to the game the player is currently playing,
		/// or \c nullptr if no game is being played.
		const Game* game() const;
		
		/// Use this player to play a side in a game.
		/// \param game The game to play.
		/// \param is_black The side to play, \c true for black, \c false for white.
		void play(const Game *const game, const bool is_black);
		
		/// Request the player's next turn in the game.
		/// \returns An in-order series of moves which make up the player's turn.
		/// \throws std::runtime_error If the player is not currently attached to a game.
		virtual std::vector<Move> turn() = 0;
	
	protected:
		
		/// Will be called when the game when the game ends.
		/// A derived class can optionally implement it to perform any
		/// finalising actions it wants to.
		virtual void finishGame();
		
		/// Will be called by the game when the player is attached to it.
		/// A derived class can optionally implement it to perform any
		/// initialising actions it wants to.
		virtual void startGame();
		
		/// The game currently being played.
		const Game* g;
		
		/// The side this player is currently representing.
		/// \c true for black, \c false for white.
		bool side;
};



#endif
