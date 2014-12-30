#ifndef ZEBRA_HUMAN_HXX
#define ZEBRA_HUMAN_HXX

#include "Player.hxx"



namespace zebra
{
	class Human;
}



class zebra::Human : public zebra::Player
{
	public:
		
		Human();
		
		/// Is this player fallible?
		/// \returns \c true
		virtual bool onlyHuman() const;
		
		/// Request the player's next turn from the console.
		/// \returns An in-order series of moves which make up the player's turn.
		/// \throws std::runtime_error If the player is not currently attached to a game.
		virtual std::vector<Move> turn();
		
		
	private:
		
		/// Not implemented.
		Human(const Human& h);
		
		/// Not implemented.
		Human& operator= (const Human& h);
};



#endif
