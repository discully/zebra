#include "Player.hxx"



zebra::Player::Player()
	: g(nullptr), side(false)
{}



zebra::Player::Player(const zebra::Player& p)
	: g(nullptr), side(p.side)
{}



zebra::Player& zebra::Player::operator= (const zebra::Player& p)
{
	this->side = p.side;
	return *this;
}



const zebra::Game* zebra::Player::game() const
{
	return this->g;
}



void zebra::Player::play(const zebra::Game *const game, const bool is_black)
{
	this->g = game;
	this->side = is_black;
}



void zebra::Player::finishGame()
{
	return;
}



void zebra::Player::startGame()
{
	return;
}
