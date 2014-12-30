#include <gtest/gtest.h>
#include "../src/Board.hxx"
#include "../src/Rules.hxx"
#include <stdexcept>



class TestBoard : public ::testing::Test
{
	public:
	
		void SetUp()
		{
			start = zebra::Board();
			
			rows = zebra::Board(
				std::bitset<zebra::Rules::BOARD_SQUARES>("00000000000000000000111100001111"),
				std::bitset<zebra::Rules::BOARD_SQUARES>("11110000111100000000000000000000"),
				std::bitset<zebra::Rules::BOARD_SQUARES>("00000000111100000000111100000000")
				);
			
			attack = zebra::Board(
				std::bitset<zebra::Rules::BOARD_SQUARES>("00000000000000001111000011110000"),
				std::bitset<zebra::Rules::BOARD_SQUARES>("00001111000011110000000000000000"),
				std::bitset<zebra::Rules::BOARD_SQUARES>("00000000000000000000000000000000")
				);
			
			royal_attack = zebra::Board(
				std::bitset<zebra::Rules::BOARD_SQUARES>("00000000000000001111000011110000"),
				std::bitset<zebra::Rules::BOARD_SQUARES>("00001111000011110000000000000000"),
				std::bitset<zebra::Rules::BOARD_SQUARES>("00001111000011111111000011110000")
				);
			
			single_black_king = zebra::Board(
				std::bitset<zebra::Rules::BOARD_SQUARES>("00000000000001000000000000000000"),
				std::bitset<zebra::Rules::BOARD_SQUARES>("00000000000000000000000000000000"),
				std::bitset<zebra::Rules::BOARD_SQUARES>("00000000000001000000000000000000")
				);
				
			single_white_king = zebra::Board(
				std::bitset<zebra::Rules::BOARD_SQUARES>("00000000000000000000000000000000"),
				std::bitset<zebra::Rules::BOARD_SQUARES>("00000000000001000000000000000000"),
				std::bitset<zebra::Rules::BOARD_SQUARES>("00000000000001000000000000000000")
				);
			
			single_black_man = zebra::Board(
				std::bitset<zebra::Rules::BOARD_SQUARES>("00000000000001000000000000000000"),
				std::bitset<zebra::Rules::BOARD_SQUARES>("00000000000000000000000000000000"),
				std::bitset<zebra::Rules::BOARD_SQUARES>("00000000000000000000000000000000")
				);
				
			single_white_man = zebra::Board(
				std::bitset<zebra::Rules::BOARD_SQUARES>("00000000000000000000000000000000"),
				std::bitset<zebra::Rules::BOARD_SQUARES>("00000000000001000000000000000000"),
				std::bitset<zebra::Rules::BOARD_SQUARES>("00000000000000000000000000000000")
				);
			
			// two regular pieces in a position to take each other
			two_men = zebra::Board(
				std::bitset<zebra::Rules::BOARD_SQUARES>("00000000000000000100000000000000"),
				std::bitset<zebra::Rules::BOARD_SQUARES>("00000000000001000000000000000000"),
				std::bitset<zebra::Rules::BOARD_SQUARES>("00000000000000000000000000000000")
				);
			
			// two regular pieces with their backs to each other
			two_men_backwards = zebra::Board(
				std::bitset<zebra::Rules::BOARD_SQUARES>("00000000000001000000000000000000"),
				std::bitset<zebra::Rules::BOARD_SQUARES>("00000000000000000100000000000000"),
				std::bitset<zebra::Rules::BOARD_SQUARES>("00000000000000000000000000000000")
				);
			
			// two kings with their backs to each other
			two_kings_backwards = zebra::Board(
				std::bitset<zebra::Rules::BOARD_SQUARES>("00000000000001000000000000000000"),
				std::bitset<zebra::Rules::BOARD_SQUARES>("00000000000000000100000000000000"),
				std::bitset<zebra::Rules::BOARD_SQUARES>("00000000000001000100000000000000")
				);
			
			// black man at 13, which can't take white man at 16
			ote_man = 13;
			over_the_edge_man = zebra::Board(
				std::bitset<zebra::Rules::BOARD_SQUARES>("00000000000000000001000000000000"),
				std::bitset<zebra::Rules::BOARD_SQUARES>("00000000000000001000000000000000"),
				std::bitset<zebra::Rules::BOARD_SQUARES>("00000000000000000000000000000000")
				);
			
			// white king at 20, which can't take black men at 17 or 25
			ote_king = 20;
			over_the_edge_king = zebra::Board(
				std::bitset<zebra::Rules::BOARD_SQUARES>("00000001000000010000000000000000"),
				std::bitset<zebra::Rules::BOARD_SQUARES>("00000000000010000000000000000000"),
				std::bitset<zebra::Rules::BOARD_SQUARES>("00000000000010000000000000000000")
				);
		}
		
		zebra::Board start;
		zebra::Board rows;
		zebra::Board attack;
		zebra::Board royal_attack;
		zebra::Board single_black_king;
		zebra::Board single_white_king;
		zebra::Board single_black_man;
		zebra::Board single_white_man;
		zebra::Board two_men;
		zebra::Board two_men_backwards;
		zebra::Board two_kings_backwards;
		zebra::Board over_the_edge_man;
		zebra::Board over_the_edge_king;
		
		zebra::square ote_man;
		zebra::square ote_king;
};


//
// Constructors


// Board();


TEST_F(TestBoard, DefaultConstructorProducesStartingBoard)
{
	const zebra::square pieces = zebra::Rules::PLAYER_PIECES;
	const zebra::square squares = zebra::Rules::BOARD_SQUARES;
	
	for(zebra::square s = 1; s <= pieces; ++s)
	{
		ASSERT_TRUE( start.black(s) ) << "Square " << s << " is not black.";
		ASSERT_TRUE( start.man(s) ) << "Square " << s << " is not a man.";
	}
	
	for(zebra::square s = pieces + 1; s <= squares - pieces; ++s)
	{
		ASSERT_TRUE( start.empty(s) ) << "Square " << s << " is not empty.";
	}
	
	for(zebra::square s = squares - pieces + 1; s <= squares; ++s)
	{
		ASSERT_TRUE( start.white(s) ) << "Square " << s << " is not white.";
		ASSERT_TRUE( start.man(s) ) << "Square " << s << " is not a man.";
	}
}


// zebra::Board::Board(
//	const std::bitset<Rules::BOARD_SQUARES>& black_pieces,
//	const std::bitset<Rules::BOARD_SQUARES>& white_pieces,
//	const std::bitset<Rules::BOARD_SQUARES>& king_pices
//	)


TEST_F(TestBoard, BitsetsConstructorThrowsInvalidArgumentIfBlackAndWhiteHaveSameBitsSet)
{
	const std::bitset<zebra::Rules::BOARD_SQUARES> black_pieces("11110000010000000000000000000000");
	const std::bitset<zebra::Rules::BOARD_SQUARES> white_pieces("00001111010000000000000000000000");
	const std::bitset<zebra::Rules::BOARD_SQUARES> king_pieces( "00000000000000000000000000000000");
	
	ASSERT_THROW( zebra::Board(black_pieces, white_pieces, king_pieces), std::invalid_argument );
}


TEST_F(TestBoard, BitsetsConstructorThrowsInvalidArgumentIfBlackHasTooManyBitsSet)
{
	const std::bitset<zebra::Rules::BOARD_SQUARES> black_pieces("11111111111111111111111111110000");
	const std::bitset<zebra::Rules::BOARD_SQUARES> white_pieces("00000000000000000000000000000000");
	const std::bitset<zebra::Rules::BOARD_SQUARES> king_pieces( "00000000000000000000000000000000");
	
	ASSERT_THROW( zebra::Board(black_pieces, white_pieces, king_pieces), std::invalid_argument );
}


TEST_F(TestBoard, BitsetsConstructorThrowsInvalidArgumentIfWhiteHasTooManyBitsSet)
{
	const std::bitset<zebra::Rules::BOARD_SQUARES> black_pieces("00000000000000000000000000000000");
	const std::bitset<zebra::Rules::BOARD_SQUARES> white_pieces("11111111111111111111111111110000");
	const std::bitset<zebra::Rules::BOARD_SQUARES> king_pieces( "00000000000000000000000000000000");
	
	ASSERT_THROW( zebra::Board(black_pieces, white_pieces, king_pieces), std::invalid_argument );
}


TEST_F(TestBoard, BitsetsConstructorThrowsInvalidArgumentIfKingsHasBitsSetNotInBlacksOrWhites)
{
	const std::bitset<zebra::Rules::BOARD_SQUARES> black_pieces("11110000000000000000000000000000");
	const std::bitset<zebra::Rules::BOARD_SQUARES> white_pieces("00001111000000000000000000000000");
	const std::bitset<zebra::Rules::BOARD_SQUARES> king_pieces( "00111100000000000000000000000001");
	
	ASSERT_THROW( zebra::Board(black_pieces, white_pieces, king_pieces), std::invalid_argument );
}


TEST_F(TestBoard, BitsetsConstructorProducesExpectedBoard)
{
	const std::bitset<zebra::Rules::BOARD_SQUARES> black_pieces("00000000000000000000111100001111");
	const std::bitset<zebra::Rules::BOARD_SQUARES> white_pieces("11110000111100000000000000000000");
	const std::bitset<zebra::Rules::BOARD_SQUARES> king_pieces( "00000000111100000000111100000000");
	
	const zebra::Board b(black_pieces, white_pieces, king_pieces);
	
	for(zebra::square s = 1; s <= zebra::Rules::BOARD_SQUARES; ++s)
	{
		if( s <= 4 )
		{
			ASSERT_TRUE( b.black(s) ) << "Square " << s << " is not black.";
			ASSERT_TRUE( b.man(s) ) << "Square " << s << " is not a man.";
		}
		else if( s >= 9 && s <= 12 )
		{
			ASSERT_TRUE( b.black(s) ) << "Square " << s << " is not black.";
			ASSERT_TRUE( b.king(s) ) << "Square " << s << " is not a king.";
		}
		else if( s >= 21 && s <= 24 )
		{
			ASSERT_TRUE( b.white(s) ) << "Square " << s << " is not white.";
			ASSERT_TRUE( b.king(s) ) << "Square " << s << " is not a king.";
		}
		else if( s >= 29 && s <= 32 )
		{
			ASSERT_TRUE( b.white(s) ) << "Square " << s << " is not white.";
			ASSERT_TRUE( b.man(s) ) << "Square " << s << " is not a man.";
		}
		else
		{
			ASSERT_TRUE( b.empty(s) ) << "Square " << s << " is not empty.";
		}
	}
}


//
// State Information


// bool black(const square& s) const;


TEST_F(TestBoard, BlackSquareThrowsOutOfRangeIfSquareIsZero)
{
	ASSERT_THROW( start.black(0), std::out_of_range );
}


TEST_F(TestBoard, BlackSquareThrowsOutOfRangeIfSquareIsTooLarge)
{
	ASSERT_THROW( start.black(zebra::Rules::BOARD_SQUARES+1), std::out_of_range );
}


TEST_F(TestBoard, BlackSquareReturnsTrueForBlackStartingPositions)
{
	for(zebra::square s = 1; s <= zebra::Rules::PLAYER_PIECES; ++s)
	{
		ASSERT_TRUE( start.black(s) ) << "Failed on square " << s << ".";
	}
}


TEST_F(TestBoard, BlackSquareReturnsFalseForEmptyStartingPositions)
{
	const zebra::square begin = zebra::Rules::PLAYER_PIECES + 1;
	const zebra::square end = (zebra::Rules::BOARD_SQUARES - zebra::Rules::PLAYER_PIECES);
	for(zebra::square s = begin; s <= end; ++s)
	{
		ASSERT_FALSE( start.black(s) ) << "Failed on square " << s << ".";
	}
}


TEST_F(TestBoard, BlackSquareReturnsFalseForWhiteStartingPositions)
{
	zebra::square begin = (zebra::Rules::BOARD_SQUARES - zebra::Rules::PLAYER_PIECES) + 1;
	for(zebra::square s = begin; s <= zebra::Rules::BOARD_SQUARES; ++s)
	{
		ASSERT_FALSE( start.black(s) ) << "Failed on square " << s << ".";
	}
}


// bool black(const coord& x, const coord& y) const;


TEST_F(TestBoard, BlackXYThrowsOutOfRangeIfXIsTooLarge)
{
	unsigned int n = zebra::Rules::BOARD_SIZE;
	ASSERT_THROW( start.black(n, 0), std::out_of_range );
}


TEST_F(TestBoard, BlackXYThrowsOutOfRangeIfYIsTooLarge)
{
	unsigned int n = zebra::Rules::BOARD_SIZE;
	ASSERT_THROW( start.black(0, n), std::out_of_range );
}


TEST_F(TestBoard, BlackXYThrowsInvalidArgumentIfXYIsNotAPlayableSquare)
{
	unsigned int n = zebra::Rules::BOARD_SIZE;
	ASSERT_THROW( start.black(0, n-1), std::invalid_argument );
}


TEST_F(TestBoard, BlackXYReturnsTrueForBlackStartingPositions)
{
	const unsigned int n = zebra::Rules::BOARD_SIZE;
	bool playable = false;
	size_t squares = 0;
	
	for(zebra::coord y = 0; y < n; ++y)
	{
		for(zebra::coord x = 0; x < n; ++x)
		{
			playable = ( x%2 == y%2 );
			
			if( playable )
			{
				++squares;
				if( squares > (zebra::Rules::BOARD_SQUARES - zebra::Rules::PLAYER_PIECES) )
				{
					ASSERT_TRUE( start.black(x,y) ) << "Failed on (" << x << "," << y << ").";
				}
			}
		}
	}
}


TEST_F(TestBoard, BlackXYReturnsFalseForEmptyStartingPositions)
{
	const unsigned int n = zebra::Rules::BOARD_SIZE;
	bool playable = false;
	size_t squares = 0;
	
	for(zebra::coord y = 0; y < n; ++y)
	{
		for(zebra::coord x = 0; x < n; ++x)
		{
			playable = ( x%2 == y%2 );
			
			if( playable )
			{
				++squares;
				if(
					( squares <= (zebra::Rules::BOARD_SQUARES - zebra::Rules::PLAYER_PIECES) )
					&&
					( squares > zebra::Rules::PLAYER_PIECES )
					)
				{
					ASSERT_FALSE( start.black(x,y) ) << "Failed on (" << x << "," << y << ").";
				}
			}
		}
	}
}


TEST_F(TestBoard, BlackXYReturnsFalseForWhiteStartingPositions)
{
	const unsigned int n = zebra::Rules::BOARD_SIZE;
	bool playable = false;
	size_t squares = 0;
	
	for(zebra::coord y = 0; y < n; ++y)
	{
		for(zebra::coord x = 0; x < n; ++x)
		{
			playable = ( x%2 == y%2 );
			
			if( playable )
			{
				++squares;
				if( squares < zebra::Rules::PLAYER_PIECES )
				{
					ASSERT_FALSE( start.black(x,y) ) << "Failed on (" << x << "," << y << ").";
				}
			}
		}
	}
}


// bool empty(const square& s) const;


TEST_F(TestBoard, EmptySquareThrowsOutOfRangeIfSquareIsZero)
{
	ASSERT_THROW( start.empty(0), std::out_of_range );
}


TEST_F(TestBoard, EmptySquareThrowsOutOfRangeIfSquareIsTooLarge)
{
	ASSERT_THROW( start.empty(zebra::Rules::BOARD_SQUARES+1), std::out_of_range );
}


TEST_F(TestBoard, EmptySquareReturnsFalseForBlackStartingPositions)
{
	for(zebra::square s = 1; s <= zebra::Rules::PLAYER_PIECES; ++s)
	{
		ASSERT_FALSE( start.empty(s) ) << "Failed on square " << s << ".";
	}
}


TEST_F(TestBoard, EmptySquareReturnsTrueForEmptyStartingPositions)
{
	const zebra::square begin = zebra::Rules::PLAYER_PIECES + 1;
	const zebra::square end = (zebra::Rules::BOARD_SQUARES - zebra::Rules::PLAYER_PIECES);
	for(zebra::square s = begin; s <= end; ++s)
	{
		ASSERT_TRUE( start.empty(s) ) << "Failed on square " << s << ".";
	}
}


TEST_F(TestBoard, EmptySquareReturnsFalseForWhiteStartingPositions)
{
	zebra::square begin = (zebra::Rules::BOARD_SQUARES - zebra::Rules::PLAYER_PIECES) + 1;
	for(zebra::square s = begin; s <= zebra::Rules::BOARD_SQUARES; ++s)
	{
		ASSERT_FALSE( start.empty(s) ) << "Failed on square " << s << ".";
	}
}


// bool empty(const coord& x, const coord& y) const;


TEST_F(TestBoard, EmptyXYThrowsOutOfRangeIfXIsTooLarge)
{
	unsigned int n = zebra::Rules::BOARD_SIZE;
	ASSERT_THROW( start.empty(n, 0), std::out_of_range );
}


TEST_F(TestBoard, EmptyXYThrowsOutOfRangeIfYIsTooLarge)
{
	unsigned int n = zebra::Rules::BOARD_SIZE;
	ASSERT_THROW( start.empty(0, n), std::out_of_range );
}


TEST_F(TestBoard, EmptyXYThrowsInvalidArgumentIfXYIsNotAPlayableSquare)
{
	unsigned int n = zebra::Rules::BOARD_SIZE;
	ASSERT_THROW( start.empty(0, n-1), std::invalid_argument );
}


TEST_F(TestBoard, EmptyXYReturnsFalseForBlackStartingPositions)
{
	const unsigned int n = zebra::Rules::BOARD_SIZE;
	bool playable = false;
	size_t squares = 0;
	
	for(zebra::coord y = 0; y < n; ++y)
	{
		for(zebra::coord x = 0; x < n; ++x)
		{
			playable = ( x%2 == y%2 );
			
			if( playable )
			{
				++squares;
				if( squares > (zebra::Rules::BOARD_SQUARES - zebra::Rules::PLAYER_PIECES) )
				{
					ASSERT_FALSE( start.empty(x,y) ) << "Failed on (" << x << "," << y << ").";
				}
			}
		}
	}
}


TEST_F(TestBoard, EmptyXYReturnsTrueForEmptyStartingPositions)
{
	const unsigned int n = zebra::Rules::BOARD_SIZE;
	bool playable = false;
	size_t squares = 0;
	
	for(zebra::coord y = 0; y < n; ++y)
	{
		for(zebra::coord x = 0; x < n; ++x)
		{
			playable = ( x%2 == y%2 );
			
			if( playable )
			{
				++squares;
				if(
					( squares <= (zebra::Rules::BOARD_SQUARES - zebra::Rules::PLAYER_PIECES) )
					&&
					( squares > zebra::Rules::PLAYER_PIECES )
					)
				{
					ASSERT_TRUE( start.empty(x,y) ) << "Failed on (" << x << "," << y << ").";
				}
			}
		}
	}
}


TEST_F(TestBoard, EmptyXYReturnsFalseForWhiteStartingPositions)
{
	const unsigned int n = zebra::Rules::BOARD_SIZE;
	bool playable = false;
	size_t squares = 0;
	
	for(zebra::coord y = 0; y < n; ++y)
	{
		for(zebra::coord x = 0; x < n; ++x)
		{
			playable = ( x%2 == y%2 );
			
			if( playable )
			{
				++squares;
				if( squares < zebra::Rules::PLAYER_PIECES )
				{
					ASSERT_FALSE( start.empty(x,y) ) << "Failed on (" << x << "," << y << ").";
				}
			}
		}
	}
}


// std::vector<zebra::Move> jumps(const bool& is_black) const;


TEST_F(TestBoard, JumpsBoolIsEmptyForSingleBlackKing)
{
	ASSERT_TRUE( single_black_king.jumps(true).empty() );
}


TEST_F(TestBoard, JumpsBoolIsEmptyForSingleWhiteKing)
{
	ASSERT_TRUE( single_white_king.jumps(false).empty() );
}


TEST_F(TestBoard, JumpsBoolIsEmptyForSingleBlackMan)
{
	ASSERT_TRUE( single_black_man.jumps(true).empty() );
}


TEST_F(TestBoard, JumpsBoolIsEmptyForSingleWhiteMan)
{
	ASSERT_TRUE( single_white_man.jumps(false).empty() );
}


TEST_F(TestBoard, JumpsBoolBlackHasOneEntryForTwoMen)
{
	ASSERT_EQ( 1, two_men.jumps(true).size() );
}


TEST_F(TestBoard, JumpsBoolWhiteHasOneEntryForTwoMen)
{
	ASSERT_EQ( 1, two_men.jumps(false).size() );
}


TEST_F(TestBoard, JumpsBoolBlackIsEmptyForTwoMenBackwards)
{
	ASSERT_TRUE( two_men_backwards.jumps(true).empty() );
}


TEST_F(TestBoard, JumpsBoolWhiteIsEmptyForTwoMenBackwards)
{
	ASSERT_TRUE( two_men_backwards.jumps(false).empty() );
}


TEST_F(TestBoard, JumpsBoolBlackHasOneEntryForTwoKingsBackwards)
{
	ASSERT_EQ( 1, two_kings_backwards.jumps(true).size() );
}


TEST_F(TestBoard, JumpsBoolWhiteHasOneEntryForTwoKingsBackwards)
{
	ASSERT_EQ( 1, two_kings_backwards.jumps(false).size() );
}


TEST_F(TestBoard, JumpsBoolBlackReturnsNoMovesForOverTheEdgeMan)
{
	ASSERT_EQ( 0, over_the_edge_man.jumps(true).size() );
}


TEST_F(TestBoard, JumpsBoolWhiteReturnsNoMovesForOverTheEdgeMan)
{
	ASSERT_EQ( 0, over_the_edge_man.jumps(false).size() );
}


// std::vector<zebra::Move> jumps(const square& from) const;
// todo


// bool king(const square& s) const;


TEST_F(TestBoard, KingSquareThrowsOutOfRangeIfSquareIsZero)
{
	ASSERT_THROW( start.king(0), std::out_of_range );
}


TEST_F(TestBoard, KingSquareThrowsOutOfRangeIfSquareIsTooLarge)
{
	ASSERT_THROW( start.king(zebra::Rules::BOARD_SQUARES+1), std::out_of_range );
}


TEST_F(TestBoard, KingSquareReturnsFalseForAllStartingPositions)
{
	for(zebra::square s = 1; s <= zebra::Rules::BOARD_SQUARES; ++s)
	{
		ASSERT_FALSE( start.king(s) ) << "Failed on square " << s << ".";
	}
}


// bool king(const coord& x, const coord& y) const;


TEST_F(TestBoard, KingXYThrowsOutOfRangeIfXIsTooLarge)
{
	unsigned int n = zebra::Rules::BOARD_SIZE;
	ASSERT_THROW( start.king(n, 0), std::out_of_range );
}


TEST_F(TestBoard, KingXYThrowsOutOfRangeIfYIsTooLarge)
{
	unsigned int n = zebra::Rules::BOARD_SIZE;
	ASSERT_THROW( start.king(0, n), std::out_of_range );
}


TEST_F(TestBoard, KingXYThrowsInvalidArgumentIfXYIsNotAPlayableSquare)
{
	unsigned int n = zebra::Rules::BOARD_SIZE;
	ASSERT_THROW( start.king(0, n-1), std::invalid_argument );
}


TEST_F(TestBoard, KingXYReturnsFalseForAllStartingPositions)
{
	const unsigned int n = zebra::Rules::BOARD_SIZE;
	bool playable = false;
	size_t squares = 0;
	
	for(zebra::coord y = 0; y < n; ++y)
	{
		for(zebra::coord x = 0; x < n; ++x)
		{
			playable = ( x%2 == y%2 );
			
			if( playable )
			{
				++squares;
				if( squares > (zebra::Rules::BOARD_SQUARES - zebra::Rules::PLAYER_PIECES) )
				{
					ASSERT_FALSE( start.king(x,y) ) << "Failed on (" << x << "," << y << ").";
				}
			}
		}
	}
}


// bool man(const square& s) const;


TEST_F(TestBoard, ManSquareThrowsOutOfRangeIfSquareIsZero)
{
	ASSERT_THROW( start.man(0), std::out_of_range );
}


TEST_F(TestBoard, ManSquareThrowsOutOfRangeIfSquareIsTooLarge)
{
	ASSERT_THROW( start.man(zebra::Rules::BOARD_SQUARES+1), std::out_of_range );
}


TEST_F(TestBoard, ManSquareReturnsTrueForBlackStartingPositions)
{
	for(zebra::square s = 1; s <= zebra::Rules::PLAYER_PIECES; ++s)
	{
		ASSERT_TRUE( start.man(s) ) << "Failed on square " << s << ".";
	}
}


TEST_F(TestBoard, ManSquareReturnsFalseForEmptyStartingPositions)
{
	const zebra::square begin = zebra::Rules::PLAYER_PIECES + 1;
	const zebra::square end = (zebra::Rules::BOARD_SQUARES - zebra::Rules::PLAYER_PIECES);
	for(zebra::square s = begin; s <= end; ++s)
	{
		ASSERT_FALSE( start.man(s) ) << "Failed on square " << s << ".";
	}
}


TEST_F(TestBoard, ManSquareReturnsTrueForWhiteStartingPositions)
{
	zebra::square begin = (zebra::Rules::BOARD_SQUARES - zebra::Rules::PLAYER_PIECES) + 1;
	for(zebra::square s = begin; s <= zebra::Rules::BOARD_SQUARES; ++s)
	{
		ASSERT_TRUE( start.man(s) ) << "Failed on square " << s << ".";
	}
}


// bool man(const coord& x, const coord& y) const;


TEST_F(TestBoard, ManXYThrowsOutOfRangeIfXIsTooLarge)
{
	unsigned int n = zebra::Rules::BOARD_SIZE;
	ASSERT_THROW( start.man(n, 0), std::out_of_range );
}


TEST_F(TestBoard, ManXYThrowsOutOfRangeIfYIsTooLarge)
{
	unsigned int n = zebra::Rules::BOARD_SIZE;
	ASSERT_THROW( start.man(0, n), std::out_of_range );
}


TEST_F(TestBoard, ManXYThrowsInvalidArgumentIfXYIsNotAPlayableSquare)
{
	unsigned int n = zebra::Rules::BOARD_SIZE;
	ASSERT_THROW( start.man(0, n-1), std::invalid_argument );
}


TEST_F(TestBoard, ManXYReturnsTrueForBlackStartingPositions)
{
	const unsigned int n = zebra::Rules::BOARD_SIZE;
	bool playable = false;
	size_t squares = 0;
	
	for(zebra::coord y = 0; y < n; ++y)
	{
		for(zebra::coord x = 0; x < n; ++x)
		{
			playable = ( x%2 == y%2 );
			
			if( playable )
			{
				++squares;
				if( squares > (zebra::Rules::BOARD_SQUARES - zebra::Rules::PLAYER_PIECES) )
				{
					ASSERT_TRUE( start.man(x,y) ) << "Failed on (" << x << "," << y << ").";
				}
			}
		}
	}
}


TEST_F(TestBoard, ManXYReturnsFalseForEmptyStartingPositions)
{
	const unsigned int n = zebra::Rules::BOARD_SIZE;
	bool playable = false;
	size_t squares = 0;
	
	for(zebra::coord y = 0; y < n; ++y)
	{
		for(zebra::coord x = 0; x < n; ++x)
		{
			playable = ( x%2 == y%2 );
			
			if( playable )
			{
				++squares;
				if(
					( squares <= (zebra::Rules::BOARD_SQUARES - zebra::Rules::PLAYER_PIECES) )
					&&
					( squares > zebra::Rules::PLAYER_PIECES )
					)
				{
					ASSERT_FALSE( start.man(x,y) ) << "Failed on (" << x << "," << y << ").";
				}
			}
		}
	}
}


TEST_F(TestBoard, ManXYReturnsTrueForWhiteStartingPositions)
{
	const unsigned int n = zebra::Rules::BOARD_SIZE;
	bool playable = false;
	size_t squares = 0;
	
	for(zebra::coord y = 0; y < n; ++y)
	{
		for(zebra::coord x = 0; x < n; ++x)
		{
			playable = ( x%2 == y%2 );
			
			if( playable )
			{
				++squares;
				if( squares < zebra::Rules::PLAYER_PIECES )
				{
					ASSERT_TRUE( start.man(x,y) ) << "Failed on (" << x << "," << y << ").";
				}
			}
		}
	}
}


// std::vector<zebra::Move> moves(const bool& is_black) const;


TEST_F(TestBoard, MovesBoolReturnsSevenSlideMovesAtStart)
{
	std::vector<zebra::Move> moves = start.moves(true);
	
	ASSERT_EQ( 7, moves.size() ) << "Incorrect number of moves";
	
	for(std::vector<zebra::Move>::const_iterator mv = moves.begin(); mv != moves.end(); ++mv)
	{
		ASSERT_TRUE( mv->slide() ) << "Non-slide move encountered";
	}
}


// std::vector<zebra::Move> moves(const square& from) const;
// todo


// bool occupied(const square& s) const;


TEST_F(TestBoard, OccupiedSquareThrowsOutOfRangeIfSquareIsZero)
{
	ASSERT_THROW( start.occupied(0), std::out_of_range );
}


TEST_F(TestBoard, OccupiedSquareThrowsOutOfRangeIfSquareIsTooLarge)
{
	ASSERT_THROW( start.occupied(zebra::Rules::BOARD_SQUARES+1), std::out_of_range );
}


TEST_F(TestBoard, OccupiedSquareReturnsTrueForBlackStartingPositions)
{
	for(zebra::square s = 1; s <= zebra::Rules::PLAYER_PIECES; ++s)
	{
		ASSERT_TRUE( start.occupied(s) ) << "Failed on square " << s << ".";
	}
}


TEST_F(TestBoard, OccupiedSquareReturnsFalseForEmptyStartingPositions)
{
	const zebra::square begin = zebra::Rules::PLAYER_PIECES + 1;
	const zebra::square end = (zebra::Rules::BOARD_SQUARES - zebra::Rules::PLAYER_PIECES);
	for(zebra::square s = begin; s <= end; ++s)
	{
		ASSERT_FALSE( start.occupied(s) ) << "Failed on square " << s << ".";
	}
}


TEST_F(TestBoard, OccupiedSquareReturnsTrueForWhiteStartingPositions)
{
	zebra::square begin = (zebra::Rules::BOARD_SQUARES - zebra::Rules::PLAYER_PIECES) + 1;
	for(zebra::square s = begin; s <= zebra::Rules::BOARD_SQUARES; ++s)
	{
		ASSERT_TRUE( start.occupied(s) ) << "Failed on square " << s << ".";
	}
}


// bool occupied(const coord& x, const coord& y) const;


TEST_F(TestBoard, OccupiedXYThrowsOutOfRangeIfXIsTooLarge)
{
	unsigned int n = zebra::Rules::BOARD_SIZE;
	ASSERT_THROW( start.occupied(n, 0), std::out_of_range );
}


TEST_F(TestBoard, OccupiedXYThrowsOutOfRangeIfYIsTooLarge)
{
	unsigned int n = zebra::Rules::BOARD_SIZE;
	ASSERT_THROW( start.occupied(0, n), std::out_of_range );
}


TEST_F(TestBoard, OccupiedXYThrowsInvalidArgumentIfXYIsNotAPlayableSquare)
{
	unsigned int n = zebra::Rules::BOARD_SIZE;
	ASSERT_THROW( start.occupied(0, n-1), std::invalid_argument );
}


TEST_F(TestBoard, OccupiedXYReturnsTrueForBlackStartingPositions)
{
	const unsigned int n = zebra::Rules::BOARD_SIZE;
	bool playable = false;
	size_t squares = 0;
	
	for(zebra::coord y = 0; y < n; ++y)
	{
		for(zebra::coord x = 0; x < n; ++x)
		{
			playable = ( x%2 == y%2 );
			
			if( playable )
			{
				++squares;
				if( squares > (zebra::Rules::BOARD_SQUARES - zebra::Rules::PLAYER_PIECES) )
				{
					ASSERT_TRUE( start.occupied(x,y) ) << "Failed on (" << x << "," << y << ").";
				}
			}
		}
	}
}


TEST_F(TestBoard, OccupiedXYReturnsFalseForEmptyStartingPositions)
{
	const unsigned int n = zebra::Rules::BOARD_SIZE;
	bool playable = false;
	size_t squares = 0;
	
	for(zebra::coord y = 0; y < n; ++y)
	{
		for(zebra::coord x = 0; x < n; ++x)
		{
			playable = ( x%2 == y%2 );
			
			if( playable )
			{
				++squares;
				if(
					( squares <= (zebra::Rules::BOARD_SQUARES - zebra::Rules::PLAYER_PIECES) )
					&&
					( squares > zebra::Rules::PLAYER_PIECES )
					)
				{
					ASSERT_FALSE( start.occupied(x,y) ) << "Failed on (" << x << "," << y << ").";
				}
			}
		}
	}
}


TEST_F(TestBoard, OccupiedXYReturnsTrueForWhiteStartingPositions)
{
	const unsigned int n = zebra::Rules::BOARD_SIZE;
	bool playable = false;
	size_t squares = 0;
	
	for(zebra::coord y = 0; y < n; ++y)
	{
		for(zebra::coord x = 0; x < n; ++x)
		{
			playable = ( x%2 == y%2 );
			
			if( playable )
			{
				++squares;
				if( squares < zebra::Rules::PLAYER_PIECES )
				{
					ASSERT_TRUE( start.occupied(x,y) ) << "Failed on (" << x << "," << y << ").";
				}
			}
		}
	}
}


// std::vector<zebra::Move> slides(const bool& is_black) const;


TEST_F(TestBoard, SlidesBoolReturnsFourMovesForSingleBlackKing)
{
	ASSERT_EQ( 4, single_black_king.slides(true).size() );
}


TEST_F(TestBoard, SlidesBoolReturnsFourMovesForSingleWhiteKing)
{
	ASSERT_EQ( 4, single_white_king.slides(false).size() );
}


TEST_F(TestBoard, SlidesBoolReturnsTwoMovesForSingleBlackMan)
{
	ASSERT_EQ( 2, single_black_man.slides(true).size() );
}


TEST_F(TestBoard, SlidesBoolReturnsTwoMovesForSingleWhiteMan)
{
	ASSERT_EQ( 2, single_white_man.slides(false).size() );
}


TEST_F(TestBoard, SlidesBoolBlackReturnsOneMoveForTwoMen)
{
	ASSERT_EQ( 1, two_men.slides(true).size() );
}


TEST_F(TestBoard, SlidesBoolWhiteReturnsOneMoveForTwoMen)
{
	ASSERT_EQ( 1, two_men.slides(false).size() );
}


TEST_F(TestBoard, SlidesBoolBlackReturnsTwoMovesForTwoMenBackwards)
{
	ASSERT_EQ( 2, two_men_backwards.slides(true).size() );
}


TEST_F(TestBoard, SlidesBoolWhiteReturnsTwoMovesForTwoMenBackwards)
{
	ASSERT_EQ( 2, two_men_backwards.slides(false).size() );
}


TEST_F(TestBoard, SlidesBoolBlackReturnsThreeMovesForTwoKingsBackwards)
{
	ASSERT_EQ( 3, two_kings_backwards.slides(true).size() );
}


TEST_F(TestBoard, SlidesBoolWhiteReturnsThreeMovesForTwoKingsBackwards)
{
	ASSERT_EQ( 3, two_kings_backwards.slides(false).size() );
}


// std::vector<zebra::Move> slides(const square& from) const;
// todo


// bool white(const square& s) const;


TEST_F(TestBoard, WhiteSquareThrowsOutOfRangeIfSquareIsZero)
{
	ASSERT_THROW( start.white(0), std::out_of_range );
}


TEST_F(TestBoard, WhiteSquareThrowsOutOfRangeIfSquareIsTooLarge)
{
	ASSERT_THROW( start.white(zebra::Rules::BOARD_SQUARES+1), std::out_of_range );
}


TEST_F(TestBoard, WhiteSquareReturnsFalseForBlackStartingPositions)
{
	for(zebra::square s = 1; s <= zebra::Rules::PLAYER_PIECES; ++s)
	{
		ASSERT_FALSE( start.white(s) ) << "Failed on square " << s << ".";
	}
}


TEST_F(TestBoard, WhiteSquareReturnsFalseForEmptyStartingPositions)
{
	const zebra::square begin = zebra::Rules::PLAYER_PIECES + 1;
	const zebra::square end = (zebra::Rules::BOARD_SQUARES - zebra::Rules::PLAYER_PIECES);
	for(zebra::square s = begin; s <= end; ++s)
	{
		ASSERT_FALSE( start.white(s) ) << "Failed on square " << s << ".";
	}
}


TEST_F(TestBoard, WhiteSquareReturnsTrueForWhiteStartingPositions)
{
	zebra::square begin = (zebra::Rules::BOARD_SQUARES - zebra::Rules::PLAYER_PIECES) + 1;
	for(zebra::square s = begin; s <= zebra::Rules::BOARD_SQUARES; ++s)
	{
		ASSERT_TRUE( start.white(s) ) << "Failed on square " << s << ".";
	}
}


// bool white(const coord& x, const coord& y) const;


TEST_F(TestBoard, WhiteXYThrowsOutOfRangeIfXIsTooLarge)
{
	unsigned int n = zebra::Rules::BOARD_SIZE;
	ASSERT_THROW( start.white(n, 0), std::out_of_range );
}


TEST_F(TestBoard, WhiteXYThrowsOutOfRangeIfYIsTooLarge)
{
	unsigned int n = zebra::Rules::BOARD_SIZE;
	ASSERT_THROW( start.white(0, n), std::out_of_range );
}


TEST_F(TestBoard, WhiteXYThrowsInvalidArgumentIfXYIsNotAPlayableSquare)
{
	unsigned int n = zebra::Rules::BOARD_SIZE;
	ASSERT_THROW( start.white(0, n-1), std::invalid_argument );
}


TEST_F(TestBoard, WhiteXYReturnsFalseForBlackStartingPositions)
{
	const unsigned int n = zebra::Rules::BOARD_SIZE;
	bool playable = false;
	size_t squares = 0;
	
	for(zebra::coord y = 0; y < n; ++y)
	{
		for(zebra::coord x = 0; x < n; ++x)
		{
			playable = ( x%2 == y%2 );
			
			if( playable )
			{
				++squares;
				if( squares > (zebra::Rules::BOARD_SQUARES - zebra::Rules::PLAYER_PIECES) )
				{
					ASSERT_FALSE( start.white(x,y) ) << "Failed on (" << x << "," << y << ").";
				}
			}
		}
	}
}


TEST_F(TestBoard, WhiteXYReturnsFalseForEmptyStartingPositions)
{
	const unsigned int n = zebra::Rules::BOARD_SIZE;
	bool playable = false;
	size_t squares = 0;
	
	for(zebra::coord y = 0; y < n; ++y)
	{
		for(zebra::coord x = 0; x < n; ++x)
		{
			playable = ( x%2 == y%2 );
			
			if( playable )
			{
				++squares;
				if(
					( squares <= (zebra::Rules::BOARD_SQUARES - zebra::Rules::PLAYER_PIECES) )
					&&
					( squares > zebra::Rules::PLAYER_PIECES )
					)
				{
					ASSERT_FALSE( start.white(x,y) ) << "Failed on (" << x << "," << y << ").";
				}
			}
		}
	}
}


TEST_F(TestBoard, WhiteXYReturnsTrueForWhiteStartingPositions)
{
	const unsigned int n = zebra::Rules::BOARD_SIZE;
	bool playable = false;
	size_t squares = 0;
	
	for(zebra::coord y = 0; y < n; ++y)
	{
		for(zebra::coord x = 0; x < n; ++x)
		{
			playable = ( x%2 == y%2 );
			
			if( playable )
			{
				++squares;
				if( squares < zebra::Rules::PLAYER_PIECES )
				{
					ASSERT_TRUE( start.white(x,y) ) << "Failed on (" << x << "," << y << ").";
				}
			}
		}
	}
}


//
// Modify


// void move(const Move& m);


TEST_F(TestBoard, MoveThrowsInvalidArgumentIfMoveIsFromEmptySquare)
{
	const zebra::square from = 18;
	zebra::Move mv(from, zebra::slideNE(from));
	
	ASSERT_THROW( start.move(mv), std::invalid_argument );
}


TEST_F(TestBoard, MoveThrowsInvalidArgumentIfMoveIsToOccupiedSquare)
{
	const zebra::square to = 23;
	zebra::Move mv(zebra::slideSW(to), to);
	
	ASSERT_THROW( start.move(mv), std::invalid_argument );
}


TEST_F(TestBoard, MoveThrowsInvalidArgumentIfMoveIsJumpOverEmptySquare)
{
	const zebra::square from = 23;
	zebra::Move mv(from, zebra::jumpNE(from));
	
	ASSERT_THROW( start.move(mv), std::invalid_argument );
}


TEST_F(TestBoard, MoveThrowsInvalidArgumentIfMoveIsJumpOverSameColour)
{
	const zebra::square from = 26;
	zebra::Move mv(from, zebra::jumpNE(from));
	
	ASSERT_THROW( start.move(mv), std::invalid_argument );
}


TEST_F(TestBoard, MoveLeavesInitialPositionEmpty)
{
	const zebra::Move mv(22, 18);
	
	start.move(mv);
	
	ASSERT_TRUE( start.empty(mv.from()) );
}


TEST_F(TestBoard, MoveLeavesFinalPositionOccupied)
{
	const zebra::Move mv(22, 18);
	
	start.move(mv);
	
	ASSERT_TRUE( start.occupied(mv.to()) );
}


TEST_F(TestBoard, MoveLeavesFinalPositionWithSameColour)
{
	const zebra::Move mv(22, 18);
	
	bool is_black = start.black(mv.from());
	start.move(mv);
	
	ASSERT_EQ( is_black, start.black(mv.to()) );
}


TEST_F(TestBoard, MoveLeavesManWithSameRank)
{
	const zebra::Move mv(22, 18);
	
	start.move(mv);
	
	ASSERT_TRUE( start.man(mv.to()) );
}


TEST_F(TestBoard, MoveLeavesKingWithSameRank)
{
	const zebra::Move mv(18, 11);
	
	royal_attack.move(mv);
	
	ASSERT_TRUE( royal_attack.king(mv.to()) );
}


TEST_F(TestBoard, MoveSetsJumpedPositionEmpty)
{
	const zebra::Move mv(18, 11);
	
	attack.move(mv);
	
	ASSERT_TRUE( attack.empty(mv.jumped()) );
}


TEST_F(TestBoard, MoveSetsManToKingIfFinishingOnFinalRow)
{
	const zebra::Move mv1(18, 11);
	const zebra::Move mv2(11,  4);
	
	attack.move(mv1);
	attack.move(mv2);
	
	ASSERT_TRUE( attack.king(mv2.to()) );
}


// void turn(const Turn& t);
// todo


//
// Utilities


// std::pair<coord,coord> getCoordinates(const square& s) const;


TEST_F(TestBoard, GetCoordinatesThrowsOutOfRangeIfSquareIsZero)
{
	ASSERT_THROW( start.getCoordinates(0), std::out_of_range );
}


TEST_F(TestBoard, GetCoordinatesThrowsOutOfRangeIfSquareIsTooLarge)
{
	ASSERT_THROW( start.getCoordinates(zebra::Rules::BOARD_SQUARES+1), std::out_of_range );
}


TEST_F(TestBoard, GetCoordinatesReturnsExpectedValues)
{
	typedef zebra::coord coord;
	
	const size_t n = zebra::Rules::BOARD_SIZE;
	zebra::square s = 0;
	
	coord y = n-1;
	for(coord row = 0; row < n; ++row, --y)
	{
		for(coord x = 0; x < n; ++x)
		{
			if( x%2 == y%2 )
			{
				++s;
				std::pair<coord,coord> result(x,y);
				ASSERT_EQ( result, start.getCoordinates(s) ) << "Failed for square=" << s << " expecting x=" << x << ", y=" << y;
			}
		}
	}
}


// square getSquare(const coord& x, const coord& y) const;


TEST_F(TestBoard, GetSquareThrowsOutOfRangeIfXIsTooLarge)
{
	const size_t n = zebra::Rules::BOARD_SQUARES + 1;
	ASSERT_THROW( start.getSquare(n, 0), std::out_of_range );
}


TEST_F(TestBoard, GetSquareThrowsOutOfRangeIfYIsTooLarge)
{
	const size_t n = zebra::Rules::BOARD_SQUARES + 1;
	ASSERT_THROW( start.getSquare(0, n), std::out_of_range );
}


TEST_F(TestBoard, GetSquareThrowsInvalidArgumentForUnplayableSquares)
{
	typedef zebra::coord coord;
	
	const size_t n = zebra::Rules::BOARD_SIZE;
	zebra::square s = 0;
	
	coord y = n-1;
	for(coord row = 0; row < n; ++row, --y)
	{
		for(coord x = 0; x < n; ++x)
		{
			if( x%2 == y%2 )
			{
				++s;
			}
			else
			{
				ASSERT_THROW( start.getSquare(x, y), std::invalid_argument ) << "Failed to throw for x=" << x << ", y=" << y;
			}
		}
	}
}


TEST_F(TestBoard, GetSquareReturnsExpectedValues)
{
	typedef zebra::coord coord;
	
	const size_t n = zebra::Rules::BOARD_SIZE;
	zebra::square s = 0;
	
	coord y = n-1;
	for(coord row = 0; row < n; ++row, --y)
	{
		for(coord x = 0; x < n; ++x)
		{
			if( x%2 == y%2 )
			{
				++s;
				ASSERT_EQ( s, start.getSquare(x, y) ) << "Failed for x=" << x << ", y=" << y << ", expecting square=" << s;
			}
		}
	}
}


// std::ostream& operator<< (std::ostream& oss, const zebra::Board& b);


TEST_F(TestBoard, StreamReturnsExpectedStringForStart)
{
	std::ostringstream result_oss;
	result_oss << start;
	
	std::ostringstream expected_oss;
	expected_oss << "| |B| |B| |B| |B\n";
	expected_oss << "|B| |B| |B| |B| \n";
	expected_oss << "| |B| |B| |B| |B\n";
	expected_oss << "| | | | | | | | \n";
	expected_oss << "| | | | | | | | \n";
	expected_oss << "|W| |W| |W| |W| \n";
	expected_oss << "| |W| |W| |W| |W\n";
	expected_oss << "|W| |W| |W| |W| \n";
	
	ASSERT_EQ( expected_oss.str(), result_oss.str() );
}
