#include "Game.hxx"



zebra::Game::Game()
	: state()
{}



zebra::Game::Game(const zebra::Game& g)
	: state(g.board())
{}



const zebra::Board& zebra::Game::board() const
{
	return this->state;
}


