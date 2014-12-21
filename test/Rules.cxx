#include <gtest/gtest.h>
#include "../src/Board.hxx"
#include "../src/Rules.hxx"



class TestRules : public ::testing::Test
{
	public:
		
		void SetUp()
		{
			start = zebra::Board();
			first_row = 3;
			second_row = 7;
			penultimate_row = 26;
			last_row = 31;
			first_col = 13;
			second_col = 17;
			penultimate_col = 16;
			last_col = 20;
			odd_row = 10;
			even_row = 15;
		}
	
		zebra::Board start;
		zebra::square first_row;
		zebra::square second_row;
		zebra::square penultimate_row;
		zebra::square last_row;
		zebra::square first_col;
		zebra::square second_col;
		zebra::square penultimate_col;
		zebra::square last_col;
		zebra::square odd_row;
		zebra::square even_row;
};


// square slideNE(const square& s);


TEST_F(TestRules, SlideNEReturnsZeroForFirstRow)
{
	ASSERT_EQ( 0, zebra::slideNE(first_row) );
}


TEST_F(TestRules, SlideNEReturnsZeroForLastColumn)
{
	ASSERT_EQ( 0, zebra::slideNE(last_col) );
}


TEST_F(TestRules, SlideNEReturnsExpectedValueOnEvenRow)
{
	ASSERT_EQ( 11, zebra::slideNE(even_row) );
}


TEST_F(TestRules, SlideNEReturnsExpectedValueOnOddRow)
{
	ASSERT_EQ( 7, zebra::slideNE(odd_row) );
}


// square slideSE(const square& s);


TEST_F(TestRules, SlideSEReturnsZeroForLastRow)
{
	ASSERT_EQ( 0, zebra::slideSE(last_row) );
}


TEST_F(TestRules, SlideSEReturnsZeroForLastColumn)
{
	ASSERT_EQ( 0, zebra::slideSE(last_col) );
}


TEST_F(TestRules, SlideSEReturnsExpectedValueForPenultimateColumn)
{
	ASSERT_EQ( 20, zebra::slideSE(penultimate_col) );
}


TEST_F(TestRules, SlideSEReturnsExpectedValueOnEvenRow)
{
	ASSERT_EQ( 19, zebra::slideSE(even_row) );
}


TEST_F(TestRules, SlideSEReturnsExpectedValueOnOddRow)
{
	ASSERT_EQ( 15, zebra::slideSE(odd_row) );
}


// square slideSW(const square& s);


TEST_F(TestRules, SlideSWReturnsZeroForLastRow)
{
	ASSERT_EQ( 0, zebra::slideSW(last_row) );
}


TEST_F(TestRules, SlideSWReturnsZeroForFirstColumn)
{
	ASSERT_EQ( 0, zebra::slideSW(first_col) );
}


TEST_F(TestRules, SlideSWReturnsExpectedValueOnEvenRow)
{
	ASSERT_EQ( 18, zebra::slideSW(even_row) );
}


TEST_F(TestRules, SlideSWReturnsExpectedValueOnOddRow)
{
	ASSERT_EQ( 14, zebra::slideSW(odd_row) );
}


// square slideNW(const square& s);


TEST_F(TestRules, SlideNWReturnsZeroForFirstRow)
{
	ASSERT_EQ( 0, zebra::slideNW(first_row) );
}


TEST_F(TestRules, SlideNWReturnsZeroForFirstColumn)
{
	ASSERT_EQ( 0, zebra::slideNW(first_col) );
}


TEST_F(TestRules, SlideNWReturnsExpectedValueOnEvenRow)
{
	ASSERT_EQ( 10, zebra::slideNW(even_row) );
}


TEST_F(TestRules, SlideNWReturnsExpectedValueOnOddRow)
{
	ASSERT_EQ( 6, zebra::slideNW(odd_row) );
}


// square jumpNE(const square& s);


TEST_F(TestRules, JumpNEReturnsZeroForFirstRow)
{
	ASSERT_EQ( 0, zebra::jumpNE(first_row) );
}


TEST_F(TestRules, JumpNEReturnsZeroForSecondRow)
{
	ASSERT_EQ( 0, zebra::jumpNE(second_row) );
}


TEST_F(TestRules, JumpNEReturnsZeroForLastColumn)
{
	ASSERT_EQ( 0, zebra::jumpNE(last_col) );
}


TEST_F(TestRules, JumpNEReturnsZeroForPenultimateColumn)
{
	ASSERT_EQ( 0, zebra::jumpNE(penultimate_col) );
}


TEST_F(TestRules, JumpNEReturnsExpectedValueOnEvenRow)
{
	ASSERT_EQ( 8, zebra::jumpNE(even_row) );
}


TEST_F(TestRules, JumpNEReturnsExpectedValueOnOddRow)
{
	ASSERT_EQ( 3, zebra::jumpNE(odd_row) );
}


// square jumpSE(const square& s);


TEST_F(TestRules, JumpSEReturnsZeroForLastRow)
{
	ASSERT_EQ( 0, zebra::jumpSE(last_row) );
}


TEST_F(TestRules, JumpSEReturnsZeroForPenultimateRow)
{
	ASSERT_EQ( 0, zebra::jumpSE(penultimate_row) );
}


TEST_F(TestRules, JumpSEReturnsZeroForLastColumn)
{
	ASSERT_EQ( 0, zebra::jumpSE(last_col) );
}


TEST_F(TestRules, JumpSEReturnsZeroForPenultimateColumn)
{
	ASSERT_EQ( 0, zebra::jumpSE(penultimate_col) );
}


TEST_F(TestRules, JumpSEReturnsExpectedValueOnEvenRow)
{
	ASSERT_EQ( 24, zebra::jumpSE(even_row) );
}


TEST_F(TestRules, JumpSEReturnsExpectedValueOnOddRow)
{
	ASSERT_EQ( 19, zebra::jumpSE(odd_row) );
}


// square jumpSW(const square& s);


TEST_F(TestRules, JumpSWReturnsZeroForLastRow)
{
	ASSERT_EQ( 0, zebra::jumpSW(last_row) );
}


TEST_F(TestRules, JumpSWReturnsZeroForPenultimateRow)
{
	ASSERT_EQ( 0, zebra::jumpSW(penultimate_row) );
}


TEST_F(TestRules, JumpSWReturnsZeroForFirstColumn)
{
	ASSERT_EQ( 0, zebra::jumpSW(first_col) );
}


TEST_F(TestRules, JumpSWReturnsZeroForSecondColumn)
{
	ASSERT_EQ( 0, zebra::jumpSW(second_col) );
}


TEST_F(TestRules, JumpSWReturnsExpectedValueOnEvenRow)
{
	ASSERT_EQ( 22, zebra::jumpSW(even_row) );
}


TEST_F(TestRules, JumpSWReturnsExpectedValueOnOddRow)
{
	ASSERT_EQ( 17, zebra::jumpSW(odd_row) );
}


// square jumpNW(const square& s);


TEST_F(TestRules, JumpNWReturnsZeroForFirstRow)
{
	ASSERT_EQ( 0, zebra::jumpNW(first_row) );
}


TEST_F(TestRules, JumpNWReturnsZeroForSecondRow)
{
	ASSERT_EQ( 0, zebra::jumpNW(second_row) );
}


TEST_F(TestRules, JumpNWReturnsZeroForFirstColumn)
{
	ASSERT_EQ( 0, zebra::jumpNW(first_col) );
}


TEST_F(TestRules, JumpNWReturnsZeroForSecondColumn)
{
	ASSERT_EQ( 0, zebra::jumpNW(second_col) );
}


TEST_F(TestRules, JumpNWReturnsExpectedValueOnEvenRow)
{
	ASSERT_EQ( 6, zebra::jumpNW(even_row) );
}


TEST_F(TestRules, JumpNWReturnsExpectedValueOnOddRow)
{
	ASSERT_EQ( 1, zebra::jumpNW(odd_row) );
}

