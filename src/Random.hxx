#ifndef ZEBRA_RANDOM_HXX
#define ZEBRA_RANDOM_HXX

#include <random>
#include "Player.hxx"




namespace zebra
{
	class Random;
}



class zebra::Random : public zebra::Player
{
	public:
		
		Random();
		
		/// Is this player fallible?
		/// \returns \c false
		virtual bool onlyHuman() const;
		
		/// Request the player's next turn from the console.
		/// \returns An in-order series of moves which make up the player's turn.
		/// \throws std::runtime_error If the player is not currently attached to a game.
		virtual std::vector<Move> turn();
		
		
	private:
	
		Move choose(const std::vector<Move>& moves);
		
		/// Not implemented.
		Random(const Random& h);
		
		/// Not implemented.
		Random& operator= (const Random& h);
		
		std::mt19937 r_generator;
		std::uniform_int_distribution<int> r;
};



#endif
