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
				std::bitset<zebra::Rules::BOARD_SQUARES> black_pieces("00000000000000000000111100001111"),
				std::bitset<zebra::Rules::BOARD_SQUARES> white_pieces("11110000111100000000000000000000"),
				std::bitset<zebra::Rules::BOARD_SQUARES> king_pieces( "00000000111100000000111100000000")
				);
		}
		
		zebra::Board start;
		zebra::Board rows;
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


TEST_F(TestBoard, BlackSThrowsOutOfRangeIfSquareIsZero)
{
	ASSERT_THROW( start.black(0), std::out_of_range );
}


TEST_F(TestBoard, BlackSThrowsOutOfRangeIfSquareIsTooLarge)
{
	ASSERT_THROW( start.black(zebra::Rules::BOARD_SQUARES+1), std::out_of_range );
}


TEST_F(TestBoard, BlackSReturnsTrueForBlackStartingPositions)
{
	for(zebra::square s = 1; s <= zebra::Rules::PLAYER_PIECES; ++s)
	{
		ASSERT_TRUE( start.black(s) ) << "Failed on square " << s << ".";
	}
}


TEST_F(TestBoard, BlackSReturnsFalseForEmptyStartingPositions)
{
	const zebra::square begin = zebra::Rules::PLAYER_PIECES + 1;
	const zebra::square end = (zebra::Rules::BOARD_SQUARES - zebra::Rules::PLAYER_PIECES);
	for(zebra::square s = begin; s <= end; ++s)
	{
		ASSERT_FALSE( start.black(s) ) << "Failed on square " << s << ".";
	}
}


TEST_F(TestBoard, BlackSReturnsFalseForWhiteStartingPositions)
{
	zebra::square begin = (zebra::Rules::BOARD_SQUARES - zebra::Rules::PLAYER_PIECES) + 1;
	for(zebra::square s = begin; s <= zebra::Rules::BOARD_SQUARES; ++s)
	{
		ASSERT_FALSE( start.black(s) ) << "Failed on square " << s << ".";
	}
}


// bool black(const coord& x, const coord& y) const;
// todo


// bool empty(const square& s) const;


TEST_F(TestBoard, EmptyThrowsOutOfRangeIfSquareIsZero)
{
	ASSERT_THROW( start.empty(0), std::out_of_range );
}


TEST_F(TestBoard, EmptyThrowsOutOfRangeIfSquareIsTooLarge)
{
	ASSERT_THROW( start.empty(zebra::Rules::BOARD_SQUARES+1), std::out_of_range );
}


TEST_F(TestBoard, EmptyReturnsFalseForBlackStartingPositions)
{
	for(zebra::square s = 1; s <= zebra::Rules::PLAYER_PIECES; ++s)
	{
		ASSERT_FALSE( start.empty(s) ) << "Failed on square " << s << ".";
	}
}


TEST_F(TestBoard, EmptyReturnsTrueForEmptyStartingPositions)
{
	const zebra::square begin = zebra::Rules::PLAYER_PIECES + 1;
	const zebra::square end = (zebra::Rules::BOARD_SQUARES - zebra::Rules::PLAYER_PIECES);
	for(zebra::square s = begin; s <= end; ++s)
	{
		ASSERT_TRUE( start.empty(s) ) << "Failed on square " << s << ".";
	}
}


TEST_F(TestBoard, EmptyReturnsFalseForWhiteStartingPositions)
{
	zebra::square begin = (zebra::Rules::BOARD_SQUARES - zebra::Rules::PLAYER_PIECES) + 1;
	for(zebra::square s = begin; s <= zebra::Rules::BOARD_SQUARES; ++s)
	{
		ASSERT_FALSE( start.empty(s) ) << "Failed on square " << s << ".";
	}
}


// bool empty(const coord& x, const coord& y) const;
// todo


// bool king(const square& s) const;


TEST_F(TestBoard, KingThrowsOutOfRangeIfSquareIsZero)
{
	ASSERT_THROW( start.king(0), std::out_of_range );
}


TEST_F(TestBoard, KingThrowsOutOfRangeIfSquareIsTooLarge)
{
	ASSERT_THROW( start.king(zebra::Rules::BOARD_SQUARES+1), std::out_of_range );
}


TEST_F(TestBoard, KingReturnsFalseForAllStartingPositions)
{
	for(zebra::square s = 1; s <= zebra::Rules::BOARD_SQUARES; ++s)
	{
		ASSERT_FALSE( start.king(s) ) << "Failed on square " << s << ".";
	}
}


// bool king(const coord& x, const coord& y) const;
// todo


// bool man(const square& s) const;


TEST_F(TestBoard, ManThrowsOutOfRangeIfSquareIsZero)
{
	ASSERT_THROW( start.man(0), std::out_of_range );
}


TEST_F(TestBoard, ManThrowsOutOfRangeIfSquareIsTooLarge)
{
	ASSERT_THROW( start.man(zebra::Rules::BOARD_SQUARES+1), std::out_of_range );
}


TEST_F(TestBoard, ManReturnsTrueForBlackStartingPositions)
{
	for(zebra::square s = 1; s <= zebra::Rules::PLAYER_PIECES; ++s)
	{
		ASSERT_TRUE( start.man(s) ) << "Failed on square " << s << ".";
	}
}


TEST_F(TestBoard, ManReturnsFalseForEmptyStartingPositions)
{
	const zebra::square begin = zebra::Rules::PLAYER_PIECES + 1;
	const zebra::square end = (zebra::Rules::BOARD_SQUARES - zebra::Rules::PLAYER_PIECES);
	for(zebra::square s = begin; s <= end; ++s)
	{
		ASSERT_FALSE( start.man(s) ) << "Failed on square " << s << ".";
	}
}


TEST_F(TestBoard, ManReturnsTrueForWhiteStartingPositions)
{
	zebra::square begin = (zebra::Rules::BOARD_SQUARES - zebra::Rules::PLAYER_PIECES) + 1;
	for(zebra::square s = begin; s <= zebra::Rules::BOARD_SQUARES; ++s)
	{
		ASSERT_TRUE( start.man(s) ) << "Failed on square " << s << ".";
	}
}


// bool man(const coord& x, const coord& y) const;
// todo


// bool occupied(const square& s) const;


TEST_F(TestBoard, OccupiedThrowsOutOfRangeIfSquareIsZero)
{
	ASSERT_THROW( start.occupied(0), std::out_of_range );
}


TEST_F(TestBoard, OccupiedThrowsOutOfRangeIfSquareIsTooLarge)
{
	ASSERT_THROW( start.occupied(zebra::Rules::BOARD_SQUARES+1), std::out_of_range );
}


TEST_F(TestBoard, OccupiedReturnsTrueForBlackStartingPositions)
{
	for(zebra::square s = 1; s <= zebra::Rules::PLAYER_PIECES; ++s)
	{
		ASSERT_TRUE( start.occupied(s) ) << "Failed on square " << s << ".";
	}
}


TEST_F(TestBoard, OccupiedReturnsFalseForEmptyStartingPositions)
{
	const zebra::square begin = zebra::Rules::PLAYER_PIECES + 1;
	const zebra::square end = (zebra::Rules::BOARD_SQUARES - zebra::Rules::PLAYER_PIECES);
	for(zebra::square s = begin; s <= end; ++s)
	{
		ASSERT_FALSE( start.occupied(s) ) << "Failed on square " << s << ".";
	}
}


TEST_F(TestBoard, OccupiedReturnsTrueForWhiteStartingPositions)
{
	zebra::square begin = (zebra::Rules::BOARD_SQUARES - zebra::Rules::PLAYER_PIECES) + 1;
	for(zebra::square s = begin; s <= zebra::Rules::BOARD_SQUARES; ++s)
	{
		ASSERT_TRUE( start.occupied(s) ) << "Failed on square " << s << ".";
	}
}


// bool occupied(const coord& x, const coord& y) const;
// todo


// bool white(const square& s) const;


TEST_F(TestBoard, WhiteThrowsOutOfRangeIfSquareIsZero)
{
	ASSERT_THROW( start.white(0), std::out_of_range );
}


TEST_F(TestBoard, WhiteThrowsOutOfRangeIfSquareIsTooLarge)
{
	ASSERT_THROW( start.white(zebra::Rules::BOARD_SQUARES+1), std::out_of_range );
}


TEST_F(TestBoard, WhiteReturnsFalseForBlackStartingPositions)
{
	for(zebra::square s = 1; s <= zebra::Rules::PLAYER_PIECES; ++s)
	{
		ASSERT_FALSE( start.white(s) ) << "Failed on square " << s << ".";
	}
}


TEST_F(TestBoard, WhiteReturnsFalseForEmptyStartingPositions)
{
	const zebra::square begin = zebra::Rules::PLAYER_PIECES + 1;
	const zebra::square end = (zebra::Rules::BOARD_SQUARES - zebra::Rules::PLAYER_PIECES);
	for(zebra::square s = begin; s <= end; ++s)
	{
		ASSERT_FALSE( start.white(s) ) << "Failed on square " << s << ".";
	}
}


TEST_F(TestBoard, WhiteReturnsTrueForWhiteStartingPositions)
{
	zebra::square begin = (zebra::Rules::BOARD_SQUARES - zebra::Rules::PLAYER_PIECES) + 1;
	for(zebra::square s = begin; s <= zebra::Rules::BOARD_SQUARES; ++s)
	{
		ASSERT_TRUE( start.white(s) ) << "Failed on square " << s << ".";
	}
}


// bool white(const coord& x, const coord& y) const;
// todo


//
// Modify


// void move(const Move& m);


TEST_F(TestBoard, MoveThrowsInvalidArgumentIfMoveIsFromEmptySquare)
{
	const zebra::square from = 18;
	zebra::Move mv(from, from - zebra::Rules::SLIDE_SHORT);
	
	ASSERT_THROW( start.move(mv), std::invalid_argument );
}


TEST_F(TestBoard, MoveThrowsInvalidArgumentIfMoveIsToOccupiedSquare)
{
	const zebra::square to = 23;
	zebra::Move mv(to + zebra::Rules::SLIDE_SHORT, to);
	
	ASSERT_THROW( start.move(mv), std::invalid_argument );
}


TEST_F(TestBoard, MoveThrowsInvalidArgumentIfMoveIsJumpOverEmptySquare)
{
	const zebra::square from = 23;
	zebra::Move mv(from, from - zebra::Rules::JUMP_SHORT);
	
	ASSERT_THROW( start.move(mv), std::invalid_argument );
}


TEST_F(TestBoard, MoveThrowsInvalidArgumentIfMoveIsJumpOverSameColour)
{
	const zebra::square from = 26;
	zebra::Move mv(from, from - zebra::Rules::JUMP_SHORT);
	
	ASSERT_THROW( start.move(mv), std::invalid_argument );
}


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

