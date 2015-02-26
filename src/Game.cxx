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



const zebra::Player* zebra::Game::blackPlayer() const
{
	return this->black;
}



const zebra::Board& zebra::Game::board() const
{
	return this->state;
}



bool zebra::Game::end() const
{
	return ! (this->winner() == nullptr);
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
	return ! (this->history == nullptr);
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
		this->white->play(nullptr, false);
	}
	this->white = white_player;
	if( this->white != nullptr )
	{
		this->white->play( this, false );
	}
}



const zebra::Player* zebra::Game::whitePlayer() const
{
	return this->white;
}



const zebra::Player* zebra::Game::winner() const
{
	bool black_has_pieces = false;
	bool white_has_pieces = false;
	
	for(square s = 1; s <= Rules::BOARD_SQUARES; ++s)
	{
		if( ! black_has_pieces && this->state.black(s) )
		{
			black_has_pieces = true;
		}
		else if( ! white_has_pieces && this->state.white(s) )
		{
			white_has_pieces = true;
		}
		
		if( black_has_pieces && white_has_pieces ) break;
	}
	
	if( black_has_pieces && white_has_pieces )
	{
		return nullptr;
	}
	else if( black_has_pieces )
	{
		return this->black;
	}
	else
	{
		return this->white;
	}
}



//
// Private
//



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
	//std::cout << "\n\n" << this->board() << "\n\n";
	
	zebra::Turn turn = player->turn();
	
	//std::cout << ( (player == this->black) ? "Black" : "White" ) << ": ";
	//for(zebra::Turn::const_iterator mv = turn.begin(); mv != turn.end(); ++mv)
	//{
	//	std::cout << *mv << " ";
	//}
	//std::cout << std::endl;
	
	this->state.turn(turn);
	
	if( this->logging() ) this->logTurn( turn );

	this->next = ( *(this->next) == this->black ) ? &(this->white) : &(this->black);
}



//
// Other
//



std::ostream& operator<< (std::ostream& oss, const zebra::Game& g)
{
	bool game_over = g.end();
	bool black_wins = game_over && (g.winner() == g.blackPlayer());
	
	oss << "[Black \"" << g.blackPlayer()->name() << "\"]\n";
	oss << "[White \"" << g.whitePlayer()->name() << "\"]\n";
	oss << "[Result \"" << ( game_over ? ( black_wins ? "0-1" : "1-0" ) : "*" ) << "\"]\n";
	
	std::vector< std::vector<zebra::Move> > turns = g.log();
	unsigned int i = 0;
	for(std::vector< std::vector<zebra::Move> >::const_iterator turn = turns.begin(); turn != turns.end(); ++turn)
	{
		if( i % 2 == 0 )
		{
			std::cout << ((i/2)+1) << ". ";
		}
		++i;
		
		for(std::vector<zebra::Move>::const_iterator move = turn->begin(); move != turn->end(); ++move)
		{
			oss << *move << " ";
		}
	}
	
	if( game_over ) oss << (black_wins ? "BW" : "WW");
	
	oss << "\n";
	
	return oss;
}


