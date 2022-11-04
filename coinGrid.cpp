
#include"coinGrid.h"
using namespace sf;

//row specific functions for creating coins and placing them as per maze pattern

void createRow1(int x, int y, std::vector<CircleShape>& vecCoins)
{
	vecCoins.clear();
	for (int i = 1; i < 25; i++)
	{
		vecCoins.push_back(CircleShape(2.0f));
		vecCoins.back().setPosition(x, y);
		if (i % 2)
		{
			x += 21;
		}
		else
		{
			x += 20;
		}
		if (i == 12)
		{
			x += 40;
		}

	}
}

void createRow2(int x, int y, std::vector<CircleShape>& vecCoins)
{
	vecCoins.clear();

	for (int i = 1; i < 7; i++)
	{
		vecCoins.push_back(CircleShape(2.0f));
		vecCoins.back().setPosition(x, y);

		if (i == 3)
		{
			x += 63;
		}
		else if (i == 1 || i == 5)
		{
			if (i % 2)
			{
				x += 104;
			}
			else
			{
				x += 100;
			}
		}
		else
		{
			if (i % 2)
			{
				x += 126;
			}
			else
			{
				x += 120;
			}
		}

	}
}

void createRow5(int x, int y, std::vector<CircleShape>& vecCoins)
{
	vecCoins.clear();
	for (int i = 1; i < 27; i++)
	{
		vecCoins.push_back(CircleShape(2.0f));
		vecCoins.back().setPosition(x, y);
		if (i % 2)
		{
			x += 21;
		}
		else
		{
			x += 20;
		}

	}
}

void createRow6(int x, int y, std::vector<CircleShape>& vecCoins)
{
	vecCoins.clear();
	for (int i = 1; i < 7; i++)
	{
		vecCoins.push_back(CircleShape(2.0f));
		vecCoins.back().setPosition(x, y);
		if (i == 1 || i == 5)
		{
			if (i % 2)
			{
				x += 105;
			}
			else
			{
				x += 100;
			}
		}
		else if (i == 3)
		{
			x += 185;
		}
		else
		{
			if (i % 2)
			{
				x += 63;
			}
			else
			{
				x += 60;
			}
		}

	}
}

void createRow8(int x, int y, std::vector<CircleShape>& vecCoins)
{
	vecCoins.clear();
	for (int i = 1; i < 21; i++)
	{
		vecCoins.push_back(CircleShape(2.0f));
		vecCoins.back().setPosition(x, y);
		if (i % 2)
		{
			x += 21;
		}
		else
		{
			x += 20;
		}
		if (i == 6 || i == 10 || i == 14)
		{
			if (i % 2)
			{
				x += 42; //add two more spaces to the existing one space
			}
			else
			{
				x += 40;
			}
		}

	}
}

void createRow9(int x, int y, std::vector<CircleShape>& vecCoins)
{
	vecCoins.clear();
	vecCoins.push_back(CircleShape(2.0f));
	vecCoins.back().setPosition(x + 105, y);
	vecCoins.push_back(CircleShape(2.0f));
	vecCoins.back().setPosition(x + 105 + (20.4 * 15), y);
}

void createRow23(int x, int y, std::vector<CircleShape>& vecCoins)
{
	vecCoins.clear();
	for (int i = 1; i < 23; i++)
	{
		vecCoins.push_back(CircleShape(2.0f));
		vecCoins.back().setPosition(x, y);
		if (i % 2)
		{
			x += 21;
		}
		else
		{
			x += 20;
		}
		if (i == 3 || i == 19)
		{
			if (i % 2)
			{
				x += 42;
			}
			else
			{
				x += 40;
			}
		}

	}
}


void createRow24(int x, int y, std::vector<CircleShape>& vecCoins)
{
	vecCoins.clear();
	x += 42;
	for (int i = 1; i < 7; i++)
	{
		
		vecCoins.push_back(CircleShape(2.0f));
		vecCoins.back().setPosition(x, y);
		if (i == 3)
		{
			x += 189;
		}
		else
		{
			x += 61;
		
		}
	}
}


void createRow27(int x, int y, std::vector<CircleShape>& vecCoins)
{
	vecCoins.clear();
	vecCoins.push_back(CircleShape(2.0f));
	vecCoins.back().setPosition(x, y);
	vecCoins.push_back(CircleShape(2.0f));
	vecCoins.back().setPosition(x + (20.5 * 11), y);
	vecCoins.push_back(CircleShape(2.0f));
	vecCoins.back().setPosition(x + (20.5 * 14), y);
	vecCoins.push_back(CircleShape(2.0f));
	vecCoins.back().setPosition(x + (20.5 * 25), y);
}