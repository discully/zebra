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
	this->validate(s);
	return this->blacks.test(s-1);
}



bool zebra::Board::black(const coord& x, const coord& y) const
{
	return this->black( this->getSquare(x, y) );
}



bool zebra::Board::empty(const square& s) const
{
	this->validate(s);
	return ! ( this->whites.test(s-1) || this->blacks.test(s-1) );
}



bool zebra::Board::empty(const coord& x, const coord& y) const
{
	return this->empty( this->getSquare(x, y) );
}



std::vector<zebra::Move> zebra::Board::jumps(const bool& is_black) const
{
	std::vector<zebra::Move> results;
	std::vector<zebra::Move> piece_results;
	
	for(square s = 1; s <= Rules::BOARD_SQUARES; ++s)
	{
		if( this->occupied(s) && (this->black(s) == is_black) )
		{
			piece_results = this->jumps(s);
			results.insert( results.end(), piece_results.begin(), piece_results.end() );
		}
	}
	
	return results;
}



std::vector<zebra::Move> zebra::Board::jumps(const square& from) const
{
	this->validate(from);
	if( this->empty(from) )
	{
		throw std::invalid_argument("Square is empty");
	}
	
	const std::pair<coord,coord> from_xy = this->getCoordinates(from);
	
	const bool go_east = ( from_xy.first < (Rules::BOARD_SIZE - 2) );
	const bool go_west = ( from_xy.first > 1 );
	const bool go_north = ( from_xy.second < (Rules::BOARD_SIZE - 2) );
	const bool go_south = ( from_xy.second > 1 );
	const bool is_black = this->black(from);
	const bool is_king = this->king(from);
	
	square to;
	square over;
	std::vector<zebra::Move> results;
	
	if( go_north && go_east && ( ! is_black || is_king ) )
	{
		to = jumpNE(from);
		over = slideNE(from);
		if( this->empty(to) && this->occupied(over) && (is_black != this->black(over)) )
		{
			results.push_back( zebra::Move(from, to) );
		}
	}
	
	if( go_north && go_west && ( ! is_black || is_king ) )
	{
		to = jumpNW(from);
		over = slideNW(from);
		if( this->empty(to) && this->occupied(over) && (is_black != this->black(over)) )
		{
			results.push_back( zebra::Move(from, to) );
		}
	}
	
	if( go_south && go_east && ( is_black || is_king ) )
	{
		to = jumpSE(from);
		over = slideSE(from);
		if( this->empty(to) && this->occupied(over) && (is_black != this->black(over)) )
		{
			results.push_back( zebra::Move(from, to) );
		}
	}
	
	if( go_south && go_west && ( is_black || is_king ) )
	{
		to = jumpSW(from);
		over = slideSW(from);
		if( this->empty(to) && this->occupied(over) && (is_black != this->black(over)) )
		{
			results.push_back( zebra::Move(from, to) );
		}
	}
	
	return results;
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



std::vector<zebra::Move> zebra::Board::moves(const bool& is_black) const
{
	std::vector<zebra::Move> jump_moves = this->jumps(is_black);
	return jump_moves.empty() ? this->slides(is_black) : jump_moves;
}



std::vector<zebra::Move> zebra::Board::moves(const square& from) const
{
	std::vector<zebra::Move> jump_moves = this->jumps(from);
	return jump_moves.empty() ? this->slides(from) : jump_moves;
}



bool zebra::Board::occupied(const square& s) const
{
	this->validate(s);
	return ( this->whites.test(s-1) || this->blacks.test(s-1) );
}



bool zebra::Board::occupied(const coord& x, const coord& y) const
{
	return this->occupied( this->getSquare(x, y) );
}



std::vector<zebra::Move> zebra::Board::slides(const bool& is_black) const
{
	std::vector<zebra::Move> results;
	std::vector<zebra::Move> piece_results;
	
	for(square s = 1; s <= Rules::BOARD_SQUARES; ++s)
	{
		if( this->occupied(s) && (this->black(s) == is_black) )
		{
			piece_results = this->slides(s);
			results.insert( results.end(), piece_results.begin(), piece_results.end() );
		}
	}
	
	return results;
}



std::vector<zebra::Move> zebra::Board::slides(const square& from) const
{
	this->validate(from);
	if( this->empty(from) )
	{
		throw std::invalid_argument("Square is empty");
	}
	
	const std::pair<coord,coord> from_xy = this->getCoordinates(from);
	
	const bool go_east = ( from_xy.first < (Rules::BOARD_SIZE - 1) );
	const bool go_west = ( from_xy.first > 0 );
	const bool go_north = ( from_xy.second < (Rules::BOARD_SIZE - 1) );
	const bool go_south = ( from_xy.second > 0 );
	const bool is_black = this->black(from);
	const bool is_king = this->king(from);
	
	square to;
	std::vector<zebra::Move> results;
	
	if( go_south && go_west && ( is_black || is_king ) )
	{
		to = slideSW(from);
		if( this->empty(to) )
		{
			results.push_back( zebra::Move(from, to) );
		}
	}
	
	if( go_south && go_east && ( is_black || is_king ) )
	{
		to = slideSE(from);
		if( this->empty(to) )
		{
			results.push_back( zebra::Move(from, to) );
		}
	}
	
	if( go_north && go_west && ( ! is_black || is_king ) )
	{
		to = slideNW(from);
		if( this->empty(to) )
		{
			results.push_back( zebra::Move(from, to) );
		}
	}
	
	if( go_north && go_east && ( ! is_black || is_king ) )
	{
		to = slideNE(from);
		if( this->empty(to) )
		{
			results.push_back( zebra::Move(from, to) );
		}
	}
	
	return results;
}



bool zebra::Board::white(const square& s) const
{
	this->validate(s);
	return this->whites.test(s-1);
}



bool zebra::Board::white(const coord& x, const coord& y) const
{
	return this->white( this->getSquare(x, y) );
}



void zebra::Board::move(const Move& mv)
{
	this->validate(mv);
	
	const bool is_black = this->black(mv.from());
	
	// Update position of player's piece
	std::bitset<Rules::BOARD_SQUARES>& player = is_black ? this->blacks : this->whites;
	
	if( this->king(mv.from()) )
	{
		this->kings.reset( mv.from() - 1 );
		this->kings.set( mv.to() - 1 );
	}
	
	player.reset( mv.from() - 1 );
	player.set( mv.to() - 1 );
	
	// Remove taken-pieces
	const square jumped = mv.jumped();
	if( jumped != 0 )
	{
		std::bitset<Rules::BOARD_SQUARES>& opponent = is_black ? this->whites : this->blacks;
		const square jumped = mv.jumped();
		
		opponent.reset( jumped - 1 );
		this->kings.reset( jumped - 1 );
	}
	
	// Promote pieces which made it to the far side
	if( ( is_black ? (mv.to() > (Rules::BOARD_SQUARES - Rules::BOARD_ROW)) : (mv.to() <= Rules::BOARD_ROW) ) )
	{
		this->kings.set( mv.to() - 1 );
	}
}



void zebra::Board::turn(const zebra::Turn& t)
{
	this->validate(t);
	
	for(zebra::Turn::const_iterator mv = t.begin(); mv != t.end(); ++mv)
	{
		this->move( *mv );
	}
}



std::pair<zebra::coord, zebra::coord> zebra::Board::getCoordinates(const square& s) const
{
	this->validate(s);
	
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



void zebra::Board::validate(const zebra::Move& mv) const
{
	const square jumped = mv.jumped();
	const bool is_jump = (jumped != 0);
	const bool is_black = this->black(mv.from());
	const bool is_king = this->king(mv.from());
	
	if(	this->empty(mv.from()) )
	{
		throw std::invalid_argument("Attempt to move from empty square.");
	}
	else if( this->occupied(mv.to()) )
	{
		throw std::invalid_argument("Attempt to move to occupied square.");
	}
	else if( is_jump && this->empty(jumped) )
	{
		throw std::invalid_argument("Attempt to jump empty square.");
	}
	else if( is_jump && is_black == this->black(jumped) )
	{
		throw std::invalid_argument("Attempt to jump own piece.");
	}
	else if( is_king && ( is_black ? (mv.from() > mv.to()) : (mv.from() < mv.to()) ) )
	{
		throw std::invalid_argument("Attempt to move regular piece backwards.");
	}
	else if( ! is_jump && ! this->jumps(is_black).empty() )
	{
		throw std::invalid_argument("Attempt to make a slide when a jump is available");
	}
}



void zebra::Board::validate(const zebra::Turn& t) const
{
	zebra::Board temp(*this);
	
	square last = t.front().from();
	
	for(zebra::Turn::const_iterator mv = t.begin(); mv != t.end(); ++mv)
	{
		if( ! temp.king(mv->from()) && temp.king(last) )
		{
			throw std::invalid_argument("Attempt to move after king was crowned.");
		}
		
		if( mv->from() != last )
		{
			throw std::invalid_argument("Attempt to move multiple pieces in one turn.");
		}
		
		temp.move(*mv);
		
		last = mv->to();
	}
}



void zebra::Board::validate(const square& s) const
{
	if( s < 1 || s > Rules::BOARD_SQUARES )
	{
		throw std::out_of_range("The specified square is out of range");
	}
}



std::ostream& operator<< (std::ostream& oss, const zebra::Board& b)
{
	for(zebra::square s = 1; s <= zebra::Rules::BOARD_SQUARES; ++s)
	{
		if( (s % zebra::Rules::BOARD_ROW) != 1 || (s % zebra::Rules::BOARD_SIZE) == 1 )
		{
			// non-playable square before all but the first square on every other row
			oss << "| ";
		}
		
		oss << "|";
		if( b.empty(s) )
		{
			oss << " ";
		}
		else if( b.black(s) )
		{
			oss << ( b.king(s)  ? "B" : "b" );
		}
		else
		{
			oss << ( b.king(s)  ? "W" : "w" );
		}
		
		if( (s % zebra::Rules::BOARD_ROW) == 0 )
		{
			if( (s % zebra::Rules::BOARD_SIZE) == 0 )
			{
				// non-playable square at the end of every other row
				oss << "| ";
			}
			
			// after last square on every row
			oss << "\n";
		}
	}
	
	return oss;
}

