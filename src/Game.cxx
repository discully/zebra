#include "Game.hxx"

#include <iostream>
#include <stdexcept>

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



void zebra::Game::play()
{
	if( this->black == nullptr || this->white == nullptr )
	{
		throw std::invalid_argument("Two players have not been set");
	}
	
	this->black->startGame();
	this->white->startGame();
	
	while( ! this->end() )
	{
		this->playTurn();
	}
}



void zebra::Game::players(zebra::Player* black_player, zebra::Player* white_player)
{
	if( this->black != nullptr && this->black->game() == this )
	{
		this->black->play(nullptr, true);
	}
	this->black = black_player;
	if( this->black != nullptr )
	{
		this->black->play( this, true );
	}
	
	if( this->white != nullptr && this->white->game() == this )
	{
		this->white->play(nullptr, true);
	}
	this->white = white_player;
	if( this->white != nullptr )
	{
		this->white->play( this, true );
	}
}



//
// Private
//



bool zebra::Game::end() const
{
	bool black = false;
	bool white = false;
	
	for(square s = 1; s <= Rules::BOARD_SQUARES; ++s)
	{
		if( ! black && this->state.black(s) )
		{
			black = true;
		}
		else if( ! white && this->state.white(s) )
		{
			white = true;
		}
		
		if( black && white ) break;
	}
	
	return ( ! black || ! white );
}



void zebra::Game::logTurn(const std::vector<Move>& turn)
{
	this->history->push_back( turn );
}



void zebra::Game::playTurn()
{
	Player *const player = *(this->next);
	
	try
	{
		this->playerTurn(player);
	}
	catch(std::invalid_argument& e)
	{
		// If the player is human, they can learn from their mistake and
		// try again. If the player is not-human, then we may as well
		// give up the game.
		if( player->onlyHuman() )
		{
			std::cout << "Error: " << e.what() << std::endl;
		}
		else
		{
			throw e;
		}
	}
}


void zebra::Game::playerTurn(zebra::Player* player)
{
	std::cout << "\n\n" << this->board() << "\n\n";
	
	zebra::Turn turn = player->turn();
	
	std::cout << ( (player == this->black) ? "Black" : "White" ) << ": ";
	for(zebra::Turn::const_iterator mv = turn.begin(); mv != turn.end(); ++mv)
	{
		std::cout << *mv << " ";
	}
	std::cout << std::endl;
	
	this->state.turn(turn);
	
	if( this->logging() ) this->logTurn( turn );

	this->next = ( *(this->next) == this->black ) ? &(this->white) : &(this->black);
}


