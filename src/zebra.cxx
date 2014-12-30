#include <iostream>

#include "Game.hxx"
#include "Random.hxx"



//int main(int argc, char* argv[])
int main()
{
	zebra::Game g( new zebra::Random(), new zebra::Random() );
	g.play();
	return 0;
}
