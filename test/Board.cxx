#include <gtest/gtest.h>
#include "../src/Board.hxx"
#include "../src/Rules.hxx"
#include <stdexcept>



class TestBoard : public ::testing::Test
{
	public:
	
		void SetUp()
		{
			this->start = zebra::Board();
		}
		
		zebra::Board start;
};



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

