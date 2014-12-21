#include "Rules.hxx"



zebra::square zebra::slideNE(const zebra::square& s)
{
	if( ( ((s % Rules::BOARD_ROW) == 0) && ((s % Rules::BOARD_SIZE) != 0) ) || ( s <= Rules::BOARD_ROW ) )
	{
		return 0;
	}
	else if( ((s % Rules::BOARD_SIZE) != 0) && ((s % Rules::BOARD_SIZE) == (s % Rules::BOARD_ROW)) )
	{
		return (s - (Rules::BOARD_ROW - 1));
	}
	else
	{
		return (s - Rules::BOARD_ROW);
	}
}



zebra::square zebra::slideNW(const zebra::square& s)
{
	if( ( ((s % Rules::BOARD_ROW) == 1) && ((s % Rules::BOARD_SIZE) != 1) ) || ( s <= Rules::BOARD_ROW ) )
	{
		return 0;
	}
	else if( ((s % Rules::BOARD_SIZE) != 0) && ((s % Rules::BOARD_SIZE) == (s % Rules::BOARD_ROW)) )
	{
		return (s - (Rules::BOARD_ROW));
	}
	else
	{
		return (s - (Rules::BOARD_ROW + 1));
	}
}



zebra::square zebra::slideSE(const zebra::square& s)
{
	if( ( ((s % Rules::BOARD_ROW) == 0) && ((s % Rules::BOARD_SIZE) != 0) ) || (s > (Rules::BOARD_SQUARES - Rules::BOARD_ROW)) )
	{
		return 0;
	}
	else if( ((s % Rules::BOARD_SIZE) != 0) && ((s % Rules::BOARD_SIZE) == (s % Rules::BOARD_ROW)) )
	{
		return (s + (Rules::BOARD_ROW + 1));
	}
	else
	{
		return (s + Rules::BOARD_ROW);
	}
}



zebra::square zebra::slideSW(const zebra::square& s)
{
	if( ( ((s % Rules::BOARD_ROW) == 1) && ((s % Rules::BOARD_SIZE) != 1) ) || (s > (Rules::BOARD_SQUARES - Rules::BOARD_ROW)) )
	{
		return 0;
	}
	else if( ((s % Rules::BOARD_SIZE) != 0) && ((s % Rules::BOARD_SIZE) == (s % Rules::BOARD_ROW)) )
	{
		return (s + Rules::BOARD_ROW);
	}
	else
	{
		return (s + (Rules::BOARD_ROW - 1));
	}
}



zebra::square zebra::jumpNE(const zebra::square& s)
{
	if( ((s % Rules::BOARD_ROW) == 0) || ( s <= Rules::BOARD_SIZE ) )
	{
		return 0;
	}
	else
	{
		return (s - (Rules::BOARD_SIZE - 1));
	}
}



zebra::square zebra::jumpNW(const zebra::square& s)
{
	if( ((s % Rules::BOARD_ROW) == 1) || ( s <= Rules::BOARD_SIZE ) )
	{
		return 0;
	}
	else
	{
		return (s - (Rules::BOARD_SIZE + 1));
	}
}



zebra::square zebra::jumpSE(const zebra::square& s)
{
	if( ((s % Rules::BOARD_ROW) == 0) || (s > (Rules::BOARD_SQUARES - Rules::BOARD_SIZE)) )
	{
		return 0;
	}
	else
	{
		return (s + (Rules::BOARD_SIZE + 1));
	}
}



zebra::square zebra::jumpSW(const zebra::square& s)
{
	if( ((s % Rules::BOARD_ROW) == 1) || (s > (Rules::BOARD_SQUARES - Rules::BOARD_SIZE)) )
	{
		return 0;
	}
	else
	{
		return (s + (Rules::BOARD_SIZE - 1));
	}
}


