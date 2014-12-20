#ifndef ZEBRA_RULES_HXX
#define ZEBRA_RULES_HXX



namespace zebra
{
	class Rules;
		
	/// Conventional index of a playable board square, in the range [1,BOARD_SIZE].
	typedef unsigned int square;
	
	/// Co-ordinate of any square on the board, in the range [0,BOARD_SIZE).
	typedef unsigned int coord;
}



class zebra::Rules
{
	public:
	
		static const unsigned int BOARD_SIZE  = 8;
		static const unsigned int BOARD_SQUARES = (BOARD_SIZE / 2) * BOARD_SIZE;
		static const unsigned int PLAYER_PIECES = 3 * (BOARD_SIZE / 2);
		static const unsigned int SLIDE_SHORT = 3;
		static const unsigned int SLIDE_LONG  = 4;
		static const unsigned int JUMP_SHORT  = 7;
		static const unsigned int JUMP_LONG   = 9;
};



#endif
