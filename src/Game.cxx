#include "Game.hxx"

#include "Player.hxx"



zebra::Game::Game(bool logging)
	: state(),
	black(nullptr),
	next(&black),
	white(nullptr),
	history( logging ? new std::vector<std::vector<zebra::Move>>() : nullptr )
{}



zebra::Game::Game(zebra::Player* black_player, zebra::Player* white_player, bool logging)
	: state(),
	black(black_player),
	next(&black),
	white(white_player),
	history( logging ? new std::vector<std::vector<zebra::Move>>() : nullptr )
{
	this->black->play( this, true );
	this->white->play( this, false );
}



zebra::Game::Game(const zebra::Game& g)
	: state(g.state),
	black(nullptr),
	next( (g.next == &(g.black)) ? &(black) : &(white) ),
	white(nullptr),
	history( g.logging() ? new std::vector<std::vector<zebra::Move>>(*(g.history)) : nullptr)
{}



zebra::Game::~Game()
{
	if( this->history != nullptr )
	{
		delete(this->history);
	}
	
	if( (this->black != nullptr) && (this->black->game() == this) )
	{
		this->black->play(nullptr, true);
		this->black = nullptr;
	}
	
	if( (this->white != nullptr) && (this->white->game() == this) )
	{
		this->white->play(nullptr, false);
		this->white = nullptr;
	}
}



const zebra::Board& zebra::Game::board() const
{
	return this->state;
}



std::vector< std::vector<zebra::Move> > zebra::Game::log() const
{
	if( this->history == nullptr )
	{
		return std::vector< std::vector<Move> >();
	}
	else
	{
		return *(this->history);
	}
}



bool zebra::Game::logging() const
{
	return (this->history == nullptr);
}



void zebra::Game::logTurn(const std::vector<Move>& turn)
{
	this->history->push_back( turn );
}


