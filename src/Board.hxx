#ifndef ZEBRA_BOARD_HXX
#define ZEBRA_BOARD_HXX

#include <bitset>
#include <cstdint>
#include <vector>
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
		
		
		/// Constructs a board with the normal starting set-up.
		Board();
		
		
		/// Constructs a board with a custom set-up.
		/// \param black_pieces A bitset whose bits [0,n-1] represent the squares [1,n] and are true where black pieces are.
		/// \param white_pieces A bitset whose bits [0,n-1] represent the squares [1,n] and are true where white pieces are.
		/// \param king_pieces  A bitset whose bits [0,n-1] represent the squares [1,n] and are true where king pieces are.
		/// \throws std::invalid_argument If there are more than PLAYER_PIECES bits set in any of the arguments,
		/// if both \p black_pieces and \p white_pieces have two identical bits set, or if \p king_pieces has
		/// bits set where neither \p black_pieces nor \p white_pieces are set.
		Board(
			const std::bitset<Rules::BOARD_SQUARES>& black_pieces,
			const std::bitset<Rules::BOARD_SQUARES>& white_pieces,
			const std::bitset<Rules::BOARD_SQUARES>& king_pieces
			);
		
		
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
		
		
		/// Get all the jump moves available to a given player.
		/// \param is_black Specifies the player to get jump moves for, \c true for black, \c false for white.
		/// \returns The jump moves available to the specified player.
		std::vector<zebra::Move> jumps(const bool& is_black) const;
		
		
		/// Get all the jump moves available to a given piece.
		/// \param from The piece to get jump moves for.
		/// \returns The jump moves available to the specified piece.
		/// \throws std::out_of_range If \p from is outside of the valid range [1,BOARD_SQUARES].
		/// \throws std::invalid_arguement If \p from is an empty square.
		std::vector<zebra::Move> jumps(const square& from) const;
		
		
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
		
		
		/// Get all the moves available to a given player.
		/// \param is_black Specifies the player to get moves for, \c true for black, \c false for white.
		/// \returns The result of jumps() if it is not empty, or the result of slides() otherwise.
		std::vector<zebra::Move> moves(const bool& is_black) const;
		
		
		/// Get all the moves available to a given piece.
		/// \param from The piece to get moves for.
		/// \returns The result of jumps() if it is not empty, or the result of slides() otherwise.
		/// \throws std::out_of_range If \p from is outside of the valid range [1,BOARD_SQUARES].
		/// \throws std::invalid_arguement If \p from is an empty square.
		std::vector<zebra::Move> moves(const square& from) const;
		
		
		/// Check whether a specified square is occupied by a piece.
		/// \returns \c true if the square is occupied by a piece, or \c false otherwise.
		/// \throws std::out_of_range If \p s is outside of the valid range [1,BOARD_SQUARES].
		bool occupied(const square& s) const;
		
		
		/// Check whether a specified square is occupied by a piece.
		/// \returns \c true if the square is occupied by a piece, or \c false otherwise.
		/// \throws std::out_of_range If \p x or \p y are outside of the valid range [0,BOARD_SIZE).
		/// \throws std::invalid_argument If (\p x, \p y) is not a playable square.
		bool occupied(const coord& x, const coord& y) const;
		
		
		/// Get all the slide moves available to a given player.
		/// \param is_black Specifies the player to get slide moves for, \c true for black, \c false for white.
		/// \returns The slide moves available to the specified player.
		std::vector<zebra::Move> slides(const bool& is_black) const;
		
		
		/// Get all the slide moves available to a given piece.
		/// \param from The piece to get slide moves for.
		/// \returns The slide moves available to the specified piece.
		/// \throws std::out_of_range If \p from is outside of the valid range [1,BOARD_SQUARES].
		/// \throws std::invalid_arguement If \p from is an empty square.
		std::vector<zebra::Move> slides(const square& from) const;
		
		
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
		/// \throws std::invalid_argument for all the same reasons Board::validate(const Move&) would.
		/// If an exception is thrown, the board remains unchanged.
		void move(const Move& m);
		
		
		/// Applies a sequence of moves to the board.
		/// \throws std::invalid_argument for all the same reasons Board::validate(const Turn&) would.
		/// If an exception is thrown, the board remains unchanged.
		void turn(const Turn& t);
		
		
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
		
		
		/// Checks a move to see if it's valid.
		/// \throws std::invalid_argument If the move is not valid for the board. This could be a:
		///  * move from an unoccupied square
		///  * move to an occupied square
		///  * jump over an unoccupied square
		///  * jump over a player's own piece
		///  * regular piece moving backwards
		///  * slide when a jump was available
		void validate(const Move& mv) const;
		
		
		/// Checks a turn to see if it's valid.
		/// \throws std::invalid_argument for:
		///  * all the same reasons Board::validate(const Move&) would
		///  * moves being made by more than one piece
		///  * a move made after a piece is crowned
		/// If an exception is thrown, the board remains unchanged.
		void validate(const Turn& turn) const;
		
		
		/// \throws std::out_of_range If square is outside of the valid range [1,BOARD_SIZE].
		void validate(const square& s) const;
		
		std::bitset< Rules::BOARD_SQUARES > blacks;
		std::bitset< Rules::BOARD_SQUARES > whites;
		std::bitset< Rules::BOARD_SQUARES > kings;
};



std::ostream& operator<< (std::ostream& oss, const zebra::Board& b);



#endif
