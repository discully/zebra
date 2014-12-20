#ifndef ZEBRA_BOARD_HXX
#define ZEBRA_BOARD_HXX

#include <bitset>
#include <cstdint>
#include <utility>

#include "Move.hxx"
#include "Rules.hxx"



namespace zebra
{
	class Board;
}



/// Represents the draughts board and the locations and ranks of all pieces.
class zebra::Board
{
	public:
		
		
		/// Constructs a board with the customary starting set-up.
		Board();
		
		
		/// Copy-constructor.
		Board(const Board& b);
		
		
		Board& operator= (const Board& b);
		
		bool operator== (const Board& b) const;
		
		bool operator!= (const Board& b) const;
		
		
		//
		// State Information
		
		
		/// Check whether a specified square is occupied by a black piece.
		/// \returns \c true if the square is occupied by a black piece, or \c false otherwise.
		/// \throws std::out_of_range If \p s is outside of the valid range [1,BOARD_SQUARES].
		bool black(const square& s) const;
		
		
		/// Check whether a specified square is occupied by a black piece.
		/// \returns \c true if the square is occupied by a black piece, or \c false otherwise.
		/// \throws std::out_of_range If \p x or \p y are outside of the valid range [0,BOARD_SIZE).
		/// \throws std::invalid_argument If (\p x, \p y) is not a playable square.
		bool black(const coord& x, const coord& y) const;
		
		
		/// Check whether a specified square is unoccupied by a piece.
		/// \returns \c true if the square is not occupied by a piece, or \c false otherwise.
		/// \throws std::out_of_range If \p s is outside of the valid range [1,BOARD_SQUARES].
		bool empty(const square& s) const;
		
		
		/// Check whether a specified square is unoccupied by a piece.
		/// \returns \c true if the square is not occupied by a piece, or \c false otherwise.
		/// \throws std::out_of_range If \p x or \p y are outside of the valid range [0,BOARD_SIZE).
		/// \throws std::invalid_argument If (\p x, \p y) is not a playable square.
		bool empty(const coord& x, const coord& y) const;
		
		
		/// Check whether a specified square is occupied by a king.
		/// \returns \c true if the square is occupied by a king, or \c false otherwise.
		/// \throws std::out_of_range If \p s is outside of the valid range [1,BOARD_SQUARES].
		bool king(const square& s) const;
		
		
		/// Check whether a specified square is occupied by a king.
		/// \returns \c true if the square is occupied by a king, or \c false otherwise.
		/// \throws std::out_of_range If \p x or \p y are outside of the valid range [0,BOARD_SIZE).
		/// \throws std::invalid_argument If (\p x, \p y) is not a playable square.
		bool king(const coord& x, const coord& y) const;
		
		
		/// Check whether a specified square is occupied by a regular piece.
		/// \returns \c true if the square is occupied by a regular piece, or \c false otherwise.
		/// \throws std::out_of_range If \p s is outside of the valid range [1,BOARD_SQUARES].
		bool man(const square& s) const;
		
		
		/// Check whether a specified square is occupied by a regular piece.
		/// \returns \c true if the square is occupied by a regular piece, or \c false otherwise.
		/// \throws std::out_of_range If \p x or \p y are outside of the valid range [0,BOARD_SIZE).
		/// \throws std::invalid_argument If (\p x, \p y) is not a playable square.
		bool man(const coord& x, const coord& y) const;
		
		
		/// Check whether a specified square is occupied by a piece.
		/// \returns \c true if the square is occupied by a piece, or \c false otherwise.
		/// \throws std::out_of_range If \p s is outside of the valid range [1,BOARD_SQUARES].
		bool occupied(const square& s) const;
		
		
		/// Check whether a specified square is occupied by a piece.
		/// \returns \c true if the square is occupied by a piece, or \c false otherwise.
		/// \throws std::out_of_range If \p x or \p y are outside of the valid range [0,BOARD_SIZE).
		/// \throws std::invalid_argument If (\p x, \p y) is not a playable square.
		bool occupied(const coord& x, const coord& y) const;
		
		
		/// Check whether a specified square is occupied by a white piece.
		/// \returns \c true if the square is occupied by a white piece, or \c false otherwise.
		/// \throws std::out_of_range If \p s is outside of the valid range [1,BOARD_SQUARES].
		bool white(const square& s) const;
		
		
		/// Check whether a specified square is occupied by a white piece.
		/// \returns \c true if the square is occupied by a white piece, or \c false otherwise.
		/// \throws std::out_of_range If \p x or \p y are outside of the valid range [0,BOARD_SIZE).
		/// \throws std::invalid_argument If (\p x, \p y) is not a playable square.
		bool white(const coord& x, const coord& y) const;
		
		
		//
		// Modify
		
		
		/// Applies a move to the board.
		/// \throws std::invalid_argument If the move is not valid for the board.
		/// This could be a move from an unoccupied square, a move to an occupied square, a jump over an unoccupied square,
		/// a jump over a player's own piece, or a regular piece moving backward.
		void move(const Move& m);
		
		
		//void turn(const Turn& t);
		
		
		//
		// Utilities
		
		
		/// \returns A std::pair of co-ordinates where first corresponds to \e x, and second corresponds to \e y.
		/// \throws std::out_of_range If \p s is outside of the valid range [1,BOARD_SQUARES].
		std::pair<coord,coord> getCoordinates(const square& s) const;
		
		
		/// \returns The square 
		/// \throws std::out_of_range If \p x or \p y are outside of the valid range [0,BOARD_SIZE).
		/// \throws std::invalid_argument If (\p x, \p y) is not a playable square.
		square getSquare(const coord& x, const coord& y) const;
		
		
	private:
		
		void validateSquare(const square& s) const;
		
		std::bitset< Rules::BOARD_SQUARES > blacks;
		std::bitset< Rules::BOARD_SQUARES > whites;
		std::bitset< Rules::BOARD_SQUARES > kings;
};



#endif
