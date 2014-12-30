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
		
		/// Constructs a new game with no players.
		/// \param logging \c true (default) to enable logging, \c false to disable logging.
		explicit Game(bool logging = true);
		
		
		/// Constructs a new game with specified players
		/// \param black_player Pointer to an instance of a player to be black.
		/// \param white_player Pointer to an instance of a player to be white.
		/// \param logging \c true (default) to enable logging, \c false to disable logging.
		Game(Player* black_player, Player* white_player, bool logging = true);
		
		
		/// Copy-constructor copies the state of a game but not the actual
		/// players (the state of the board and knowledge who's turn it is
		/// will be copied).
		Game(const Game& game);
		
		
		virtual ~Game();
		
		
		const Player* blackPlayer() const;
		
		
		/// The game board.
		/// \returns A reference to the game's board.
		const Board& board() const;
		
		
		/// Determine if the game is over.
		/// \returns \c true if the game is over, or false otherwise.
		bool end() const;
		
		
		/// Gets a copy of the log of moves.
		/// \returns A vector log of the turns player. Each element of the
		/// vector is a turn. Each turn is a vector of one or more moves.
		/// If logging is not enabled an empty vector is returned.
		std::vector< std::vector<Move> > log() const;
		
		
		/// Get whether the game is being logged.
		/// \returns \c true if logging is enabled, or \c false otherwise.
		bool logging() const;
		
		
		void play();
		
		
		/// Set the players of this game.
		void players(Player* black_player, Player* white_player);
		
		
		const Player* whitePlayer() const;
		
		
		/// Get the winning player.
		/// \returns A pointer to the winning player if the game is over and ended in a win, or \c nullptr otherwise.
		const Player* winner() const;
		
		
	private:
		
		void logTurn(const std::vector<Move>& turn);
		
		void playTurn();
		
		void playerTurn(zebra::Player* player);
		
		/// The game's board.
		Board state;
		
		/// Pointer to the player representing black.
		Player* black;
		
		/// Pointer to the Player* who is next to play.
		Player** next;
		
		/// Pointer to the player representing white.
		Player* white;
		
		/// Optional log of the turns which took place.
		std::vector< std::vector<Move> >* history;
		
};



std::ostream& operator<< (std::ostream& oss, const zebra::Game& g);



#endif
