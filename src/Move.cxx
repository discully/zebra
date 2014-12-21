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
		if( this->positions.first <= (Rules::BOARD_SQUARES - Rules::BOARD_SIZE) )
		{
			if( jumpSE(this->positions.first) == this->positions.second ) return true;
		}
		
		if( this->positions.first > Rules::BOARD_SIZE )
		{
			if( jumpNE(this->positions.first) == this->positions.second ) return true;
		}
	}
	
	if( this->positions.first % Rules::BOARD_ROW != 1 )
	{
		if( this->positions.first <= (Rules::BOARD_SQUARES - Rules::BOARD_SIZE) )
		{
			if( jumpSW(this->positions.first) == this->positions.second ) return true;
		}
		
		if( this->positions.first > Rules::BOARD_SIZE )
		{
			if( jumpNW(this->positions.first) == this->positions.second ) return true;
		}
	}
	
	return false;
}



zebra::square zebra::Move::jumped() const
{
	if( ! this->jump() ) return 0;
	
	if( this->positions.second > this->positions.first )
	{
		if( jumpSE(this->positions.first) == this->positions.second )
		{
			return slideSE(this->positions.first);
		}
		else
		{
			return slideSW(this->positions.first);
		}
	}
	else
	{
		if( jumpNE(this->positions.first) == this->positions.second )
		{
			return slideNE(this->positions.first);
		}
		else
		{
			return slideNW(this->positions.first);
		}
	}
}



bool zebra::Move::slide() const
{
	if( ((this->positions.first % Rules::BOARD_ROW) != 0) || ((this->positions.first % Rules::BOARD_SIZE) == 0) )
	{
		if( this->positions.first > Rules::BOARD_ROW )
		{
			if( slideNE(this->positions.first) == this->positions.second ) return true;
		}
		
		if( this->positions.first <= (Rules::BOARD_SQUARES - Rules::BOARD_ROW) )
		{
			if( slideSE(this->positions.first) == this->positions.second ) return true;
		}
	}
	
	if( ((this->positions.first % Rules::BOARD_ROW) != 1) || ((this->positions.first % Rules::BOARD_SIZE) == 1) )
	{
		if( this->positions.first > Rules::BOARD_ROW )
		{
			if( slideNW(this->positions.first) == this->positions.second ) return true;
		}
		
		if( this->positions.first <= (Rules::BOARD_SQUARES - Rules::BOARD_ROW) )
		{
			if( slideSW(this->positions.first) == this->positions.second ) return true;
		}
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
