#include "Random.hxx"

#include "Board.hxx"
#include "Game.hxx"
#include "Move.hxx"



zebra::Random::Random()
	: zebra::Player(),
	r_generator( std::random_device()() ),
	r(0,1024)
{}



bool zebra::Random::onlyHuman() const
{
	return false;
}



std::vector<zebra::Move> zebra::Random::turn()
{
	std::vector<Move> result;
	
	Move first = this->choose( this->game()->board().moves( this->is_black ) );
	result.push_back(first);
	
	if( first.jump() )
	{
		Board b( this->game()->board() );
		b.move(first);
		std::vector<Move> available = b.jumps(first.to());
		
		while( ! available.empty() )
		{
			Move next = this->choose(available);
			
			result.push_back(next);
			
			b.move(next);
			available = b.jumps(next.to());
		}
	}
	
	return result;
}



zebra::Move zebra::Random::choose(const std::vector<zebra::Move>& moves)
{
	int choose = this->r(this->r_generator) % moves.size();
	return moves.at(choose);
}
