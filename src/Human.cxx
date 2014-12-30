#include "Human.hxx"

#include "Board.hxx"
#include "Game.hxx"
#include "Move.hxx"



zebra::Human::Human()
	: zebra::Player()
{}



bool zebra::Human::onlyHuman() const
{
	return true;
}



void zebra::Human::startGame()
{
	std::cout << ( this->is_black ? "Black" : "White" ) << ": Enter player's name ";
	std::cin >> this->id;
}



std::vector<zebra::Move> zebra::Human::turn()
{
	std::vector<Move> result;
	
	square from = 0;
	square to = 0;
	
	std::cout << "From: ";
	std::cin >> from;
	
	std::cout << "To: ";
	std::cin >> to;
	
	zebra::Move first_move(from, to);
	result.push_back( first_move );
	
	if( first_move.jump() )
	{
		zebra::Board b( this->game()->board() );
		b.move(first_move);
		
		while( ! b.jumps(to).empty() )
		{
			from = to;
			
			std::cout << "To: ";
			std::cin >> to;
			
			zebra::Move next(from, to);
			result.push_back(next);
			
			b.move(next);
		}
	}
	
	return result;
}
