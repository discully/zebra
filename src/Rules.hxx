#ifndef ZEBRA_RULES_HXX
#define ZEBRA_RULES_HXX



namespace zebra
{
	class Rules;
		
	/// Conventional index of a playable board square, in the range [1,BOARD_SIZE].
	typedef unsigned int square;
	
	/// Co-ordinate of any square on the board, in the range [0,BOARD_SIZE).
	typedef unsigned int coord;
	
	square slideNE(const square& s);
	square slideSE(const square& s);
	square slideSW(const square& s);
	square slideNW(const square& s);
	square jumpNE(const square& s);
	square jumpSE(const square& s);
	square jumpSW(const square& s);
	square jumpNW(const square& s);
}



class zebra::Rules
{
	public:
		
		/// The number of squares in a row/column of the board.
		static const unsigned int BOARD_SIZE  = 8;
		
		/// The number of playable square in a row/column of the board.
		static const unsigned int BOARD_ROW = BOARD_SIZE / 2;
		
		/// The total number of playable squares on the board.
		static const unsigned int BOARD_SQUARES = BOARD_ROW * BOARD_SIZE;
		
		/// The number of pieces a player has at the start of a game.
		static const unsigned int PLAYER_PIECES = 3 * (BOARD_SIZE / 2);
};



#endif
