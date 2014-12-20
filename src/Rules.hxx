#ifndef ZEBRA_RULES_HXX
#define ZEBRA_RULES_HXX



namespace zebra
{
	class Rules;
	
	typedef uint32_t Position;
	
	//enum Colour
	//{
	//	NONE,
	//	BLACK,
	//	WHITE
	//};
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
