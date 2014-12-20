#include "Move.hxx"

#include <stdexcept>



zebra::Move::Move(const square& from, const square& to)
	: positions(from, to)
{
	if( ! this->valid() )
	{
		throw std::invalid_argument("Squares do not form a valid move");
	}
}



zebra::Move::Move(const Move& mv)
	: positions(mv.positions)
{}



zebra::Move& zebra::Move::operator= (const Move& mv)
{
	this->positions = mv.positions;
	return *this;
}



bool zebra::Move::operator== (const Move& mv) const
{
	return ( this->positions == mv.positions );
}



bool zebra::Move::operator!= (const Move& mv) const
{
	return ! (*this == mv);
}



zebra::square zebra::Move::from() const
{
	return this->positions.first;
}



bool zebra::Move::jump() const
{
	if( this->positions.first % Rules::BOARD_ROW != 0 )
	{
		// Check possible jumps in an easterly direction
		
		if( this->positions.first - Rules::JUMP_SHORT == this->positions.second ) return true;
		
		if( this->positions.first + Rules::JUMP_LONG  == this->positions.second ) return true;
	}
	
	if( this->positions.first % Rules::BOARD_ROW != 1 )
	{
		// Check possible jumps in a westerly direction
		
		if( this->positions.first + Rules::JUMP_SHORT == this->positions.second ) return true;
		
		if( this->positions.first - Rules::JUMP_LONG  == this->positions.second ) return true;
	}
	
	return false;
}



zebra::square zebra::Move::jumped() const
{
	if( ! this->jump() ) return 0;
	
	if( this->positions.second > this->positions.first )
	{
		if( this->positions.first + Rules::JUMP_SHORT == this->positions.second )
		{
			return ( this->positions.first + Rules::SLIDE_SHORT );
		}
		else
		{
			return ( this->positions.first + Rules::SLIDE_LONG );
		}
	}
	else
	{
		if( this->positions.first - Rules::JUMP_SHORT == this->positions.second )
		{
			return ( this->positions.first - Rules::SLIDE_SHORT );
		}
		else
		{
			return ( this->positions.first - Rules::SLIDE_LONG );
		}
	}
}



bool zebra::Move::slide() const
{
	if( this->positions.first % Rules::BOARD_ROW != 0 )
	{
		// Check possible slides in an easterly direction
		
		if( this->positions.first - Rules::SLIDE_SHORT == this->positions.second ) return true;
		
		if( this->positions.first + Rules::SLIDE_LONG  == this->positions.second ) return true;
	}
	
	if( this->positions.first % Rules::BOARD_ROW != 1 )
	{
		// Check possible slides in a westerly direction
		
		if( this->positions.first + Rules::SLIDE_SHORT == this->positions.second ) return true;
		
		if( this->positions.first - Rules::SLIDE_LONG  == this->positions.second ) return true;
	}
	
	return false;
}



zebra::square zebra::Move::to() const
{
	return this->positions.second;
}



bool zebra::Move::valid() const
{
	if( this->positions.first == 0 || this->positions.second == 0 || this->positions.first > Rules::BOARD_SQUARES || this->positions.second > Rules::BOARD_SQUARES )
	{
		throw std::out_of_range("Square is out of valid range [1,BOARD_SQUARES].");
	}
	
	return ( this->slide() || this->jump() );
}



std::ostream& operator<< (std::ostream& oss, const zebra::Move& mv)
{
	oss << mv.from() << ( mv.jump() ? "x" : "-" ) << mv.to();
	return oss;
}
