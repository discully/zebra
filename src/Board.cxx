#include "Board.hxx"

#include <stdexcept>



zebra::Board::Board()
	:
	blacks("00000000000000000000111111111111"),
	whites("11111111111100000000000000000000"),
	kings(0)
{}



zebra::Board::Board(
	const std::bitset<Rules::BOARD_SQUARES>& black_pieces,
	const std::bitset<Rules::BOARD_SQUARES>& white_pieces,
	const std::bitset<Rules::BOARD_SQUARES>& king_pieces
	)
	: blacks(black_pieces), whites(white_pieces), kings(king_pieces)
{
	if(
		( this->blacks.count() > Rules::PLAYER_PIECES )
		||
		( this->whites.count() > Rules::PLAYER_PIECES )
		||
		( (this->blacks & this->whites).any() )
		||
		( (this->kings & (this->blacks | this->whites)) != this->kings )
	)
	{
		throw std::invalid_argument("Invalid board specification");
	}
}



zebra::Board::Board(const Board& b)
	: blacks(b.blacks), whites(b.whites), kings(b.kings)
{}



zebra::Board& zebra::Board::operator= (const Board& b)
{
	this->kings = b.kings;
	this->blacks = b.blacks;
	this->whites = b.whites;
	return *this;
}



bool zebra::Board::operator== (const Board& b) const
{
	return ( this->whites == b.whites && this->blacks == b.blacks && this->kings == b.kings );
}



bool zebra::Board::operator!= (const Board& b) const
{
	return ! (*this == b);
}



bool zebra::Board::black(const square& s) const
{
	this->validateSquare(s);
	return this->blacks.test(s-1);
}



bool zebra::Board::black(const coord& x, const coord& y) const
{
	return this->black( this->getSquare(x, y) );
}



bool zebra::Board::empty(const square& s) const
{
	this->validateSquare(s);
	return ! ( this->whites.test(s-1) || this->blacks.test(s-1) );
}



bool zebra::Board::empty(const coord& x, const coord& y) const
{
	return this->empty( this->getSquare(x, y) );
}



bool zebra::Board::king(const square& s) const
{
	return ( this->occupied(s) && this->kings.test(s-1) );
}



bool zebra::Board::king(const coord& x, const coord& y) const
{
	return this->king( this->getSquare(x, y) );
}



bool zebra::Board::man(const square& s) const
{
	return ( this->occupied(s) && ! this->kings.test(s-1) );
}



bool zebra::Board::man(const coord& x, const coord& y) const
{
	return this->man( this->getSquare(x, y) );
}



bool zebra::Board::occupied(const square& s) const
{
	this->validateSquare(s);
	return ( this->whites.test(s-1) || this->blacks.test(s-1) );
}



bool zebra::Board::occupied(const coord& x, const coord& y) const
{
	return this->occupied( this->getSquare(x, y) );
}



bool zebra::Board::white(const square& s) const
{
	this->validateSquare(s);
	return this->whites.test(s-1);
}



bool zebra::Board::white(const coord& x, const coord& y) const
{
	return this->white( this->getSquare(x, y) );
}



void zebra::Board::move(const Move& mv)
{
	const square jumped = mv.jumped();
	const bool is_jump = (jumped != 0);
	const bool is_white = this->white(mv.from());
	const bool is_king = this->king(mv.from());
	
	if(
		this->empty(mv.from())
		||
		this->occupied(mv.to())
		||
		( is_jump && this->empty(jumped) )
		||
		( is_jump && is_white == this->white(jumped) )
		||
		( is_king && is_white && (mv.from() < mv.to()) )
		||
		( is_king && ! is_white && (mv.from() > mv.to()) )
		)
	{
		throw std::invalid_argument("Invalid move");
	}
	
	std::bitset<Rules::BOARD_SQUARES>& player = is_white ? this->whites : this->blacks;
	
	player.reset( mv.from() - 1 );
	player.set( mv.to() - 1 );
	
	if( is_king )
	{
		this->kings.reset( mv.from() - 1 );
		this->kings.set( mv.from() - 1 );
	}
	
	if( is_jump )
	{
		std::bitset<Rules::BOARD_SQUARES>& opponent = is_white ? this->blacks : this->whites;
		const square jumped = mv.jumped();
		
		opponent.reset( jumped - 1 );
		this->kings.reset( jumped - 1 );
	}
}



std::pair<zebra::coord, zebra::coord> zebra::Board::getCoordinates(const square& s) const
{
	this->validateSquare(s);
	
	const coord y = (s - 1) / (Rules::BOARD_SIZE / 2);
	const coord x = (((s - 1) % 4) * 2) + ((y+1) % 2);
	
	return std::pair<coord, coord>(x, Rules::BOARD_SIZE - 1 - y);
}



zebra::square zebra::Board::getSquare(const coord& x, const coord& y) const
{
	if( x > Rules::BOARD_SIZE || y > Rules::BOARD_SIZE )
	{
		throw std::out_of_range("The specified x,y co-ordinates are out of range.");
	}
	else if( x%2 != y%2 )
	{
		throw std::invalid_argument("The specified x,y co-ordinate are not a playable square.");
	}
	
	return ( ((Rules::BOARD_SIZE - 1 - y) * (Rules::BOARD_SIZE / 2)) + (1 + (x/2)) );
}



void zebra::Board::validateSquare(const square& s) const
{
	if( s < 1 || s > Rules::BOARD_SQUARES )
	{
		throw std::out_of_range("The specified square is out of range");
	}
}

