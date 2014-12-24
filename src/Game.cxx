#include "Game.hxx"



zebra::Game::Game()
	: state(), black(nullptr), next(&black), white(nullptr)
{}



zebra::Game::Game(zebra::Player* black_player, zebra::Player* white_player)
	: state(), black(black_player), next(&black), white(white_player)
{}



zebra::Game::Game(const zebra::Game& g)
	: state(g.state), black(nullptr), next(nullptr), white(nullptr)
{
	this->next = ( g.next == &(g.black) ) ? &(this->black) : &(this->white);
}



const zebra::Board& zebra::Game::board() const
{
	return this->state;
}


