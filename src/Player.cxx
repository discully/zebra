#include "Player.hxx"

#include "Game.hxx"



zebra::Player::Player()
	: g(nullptr), id(""), is_black(false)
{}



zebra::Player::Player(const zebra::Player& p)
	: g(nullptr), id(""), is_black(p.is_black)
{}



zebra::Player& zebra::Player::operator= (const zebra::Player& p)
{
	this->id = p.id;
	this->is_black = p.is_black;
	return *this;
}



const zebra::Game* zebra::Player::game() const
{
	return this->g;
}



void zebra::Player::play(const zebra::Game *const game, const bool is_playing_black)
{
	this->g = game;
	this->is_black = is_playing_black;
}



void zebra::Player::finishGame()
{
	return;
}



std::string zebra::Player::name() const
{
	return this->id;
}



void zebra::Player::startGame()
{
	return;
}
