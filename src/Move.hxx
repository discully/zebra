#ifndef ZEBRA_MOVE_HXX
#define ZEBRA_MOVE_HXX

#include "Rules.hxx"

#include <iostream>
#include <vector>



namespace zebra
{
	class Move;
	
	typedef std::vector<Move> Turn;
}



/// Represents a single move of a single piece from one square to another.
class zebra::Move
{
	public:
		
		/// Constructs a new move from one square to another.
		/// \param from The initial square, before the move.
		/// \param to The final square, after the move.
		/// \throws std::out_of_range If either \p from or \p to are outside the valid range [1,BOARD_SQUARES].
		/// \throws std::invalid_argument If from-to does not form a valid jump or slide move.
		Move(const square& from, const square& to);
		
		
		/// Copy-constructor
		Move(const Move& mv);
		
		
		Move& operator= (const Move& mv);
		
		bool operator== (const Move& mv) const;
		
		bool operator!= (const Move& mv) const;
		
		
		/// Get the final square after the move is completed.
		square from() const;
		
		
		/// Checks if this move is a jump.
		/// \returns \c true if the move is a valid jump move, or \c false otherwise.
		bool jump() const;
		
		
		/// Get the \p square being jumped over.
		/// \returns The square being jumped over if this is a valid jump move, or \c 0 otherwise.
		square jumped() const;
		
		
		/// Check if this move is a regular slide.
		/// \returns \c true if the move is a valid slide move, or \c false otherwise.
		bool slide() const;
		
		
		/// Get the starting square before the move.
		square to() const;
		
		
	private:
		
		/// Check if this is a valid move.
		/// A move is valid if it is a slide or a jump.
		/// \returns \c true if the move is valid, or \c false otherwise.
		/// \throws std::out_of_range If either square in \p positions is outside the valid range [1,BOARD_SQUARES].
		bool valid() const;
		
		
		/// Not implemented.
		Move();
		
		
		std::pair<square,square> positions;
};



std::ostream& operator<< (std::ostream& oss, const zebra::Move& mv);



#endif
