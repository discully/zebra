#include <gtest/gtest.h>
#include "../src/Move.hxx"
#include "../src/Rules.hxx"
#include <stdexcept>
#include <string>



class TestMove : public ::testing::Test
{
	public:
		
		void SetUp()
		{
			start = 18;
			
			short_slide_fwd = new zebra::Move(start, zebra::slideNE(start));
			short_slide_bwd = new zebra::Move(start, zebra::slideSW(start));
			long_slide_fwd  = new zebra::Move(start, zebra::slideNW(start));
			long_slide_bwd  = new zebra::Move(start, zebra::slideSW(start));
			short_jump_fwd  = new zebra::Move(start, zebra::jumpNE(start));
			short_jump_bwd  = new zebra::Move(start, zebra::jumpSW(start));
			long_jump_fwd   = new zebra::Move(start, zebra::jumpNW(start));
			long_jump_bwd   = new zebra::Move(start, zebra::jumpSE(start));
			
			short_slide = short_slide_fwd;
			long_slide  = long_slide_bwd;
			short_jump  = short_jump_bwd;
			long_jump   = long_jump_fwd;
		}
		
		void TearDown()
		{
			if( short_slide_fwd != 0 ) { delete(short_slide_fwd); short_slide_fwd = 0; }
			if( short_slide_bwd != 0 ) { delete(short_slide_bwd); short_slide_bwd = 0; }
			if(  long_slide_fwd != 0 ) { delete( long_slide_fwd);  long_slide_fwd = 0; }
			if(  long_slide_bwd != 0 ) { delete( long_slide_bwd);  long_slide_bwd = 0; }
			if( short_jump_fwd != 0 ) { delete(short_jump_fwd); short_jump_fwd = 0; }
			if( short_jump_bwd != 0 ) { delete(short_jump_bwd); short_jump_bwd = 0; }
			if(  long_jump_fwd != 0 ) { delete( long_jump_fwd);  long_jump_fwd = 0; }
			if(  long_jump_bwd != 0 ) { delete( long_jump_bwd);  long_jump_bwd = 0; }
		}
		
		zebra::square start;
		
		zebra::Move* short_slide_fwd;
		zebra::Move* short_slide_bwd;
		zebra::Move* long_slide_fwd;
		zebra::Move* long_slide_bwd;
		zebra::Move* short_jump_fwd;
		zebra::Move* short_jump_bwd;
		zebra::Move* long_jump_fwd;
		zebra::Move* long_jump_bwd;
		
		zebra::Move* short_slide;
		zebra::Move* long_slide;
		zebra::Move* short_jump;
		zebra::Move* long_jump;
};


// square from() const;


TEST_F(TestMove, FromReturnsExpectedValue)
{
	ASSERT_EQ(start, short_slide->from());
}


// bool jump() const;


TEST_F(TestMove, JumpReturnsTrueForShortJump)
{
	ASSERT_TRUE( short_jump->jump() );
}


TEST_F(TestMove, JumpReturnsTrueForLongJump)
{
	ASSERT_TRUE( long_jump->jump() );
}


TEST_F(TestMove, JumpReturnsFalseForLongSlide)
{
	ASSERT_FALSE( long_slide->jump() );
}


TEST_F(TestMove, JumpReturnsFalseForShortSlide)
{
	ASSERT_FALSE( short_slide->jump() );
}


// square jumped() const;


TEST_F(TestMove, JumpedReturnsZeroForSlide)
{
	ASSERT_EQ( 0, short_slide->jumped() );
}


TEST_F(TestMove, JumpedReturnsExpectedForLongJumpForward)
{
	ASSERT_EQ( zebra::slideNW(start), long_jump_fwd->jumped() );
}


TEST_F(TestMove, JumpedReturnsExpectedForLongJumpBackward)
{
	ASSERT_EQ( zebra::slideSE(start), long_jump_bwd->jumped() );
}


TEST_F(TestMove, JumpedReturnsExpectedForShortJumpForward)
{
	ASSERT_EQ( zebra::slideNE(start), short_jump_fwd->jumped() );
}


TEST_F(TestMove, JumpedReturnsExpectedForShortJumpBackward)
{
	ASSERT_EQ( zebra::slideSW(start), short_jump_bwd->jumped() );
}


// bool slide() const;


TEST_F(TestMove, SlideReturnsTrueForShortJump)
{
	ASSERT_FALSE( short_jump->slide() );
}


TEST_F(TestMove, SlideReturnsTrueForLongJump)
{
	ASSERT_FALSE( long_jump->slide() );
}


TEST_F(TestMove, SlideReturnsFalseForLongSlide)
{
	ASSERT_TRUE( long_slide->slide() );
}


TEST_F(TestMove, SlideReturnsFalseForShortSlide)
{
	ASSERT_TRUE( short_slide->slide() );
}


// square to() const;


TEST_F(TestMove, ToReturnsExpectedValue)
{
	ASSERT_EQ( zebra::slideNE(start), short_slide_fwd->to());
}


// std::ostream& operator<< (std::ostream& oss, const zebra::Move& mv);


TEST_F(TestMove, StreamReturnsExpectedStringForJump)
{
	zebra::Move mv( *short_jump );
	
	std::ostringstream expected;
	expected << mv.from() << "x" << mv.to();
	
	std::ostringstream result;
	result << mv;
	
	ASSERT_EQ( expected.str(), result.str() );
}


TEST_F(TestMove, StreamReturnsExpectedStringForSlide)
{
	zebra::Move mv( *long_slide );
	
	std::ostringstream expected_oss;
	expected_oss << mv.from() << "-" << mv.to();
	const std::string expected = expected_oss.str();
	
	std::ostringstream result_oss;
	result_oss << mv;
	const std::string result = result_oss.str();
	
	ASSERT_EQ( expected, result );
}

