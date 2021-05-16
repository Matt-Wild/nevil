#include "StatsHandler.h"

void StatsHandler::UpdateHeight(int _height)
{
	if (_height > height)	// checks if height needs update
	{
		height = _height;	// updating height

		if (stage == 0 && height >= 50)	// move onto next difficult stage?
			stage++;	// increasing difficult

		if (stage == 1 && height >= 10000)
			stage++;

		if (stage == 2 && height >= 30000)
			stage++;

		if (stage == 3 && height >= 70000)
			stage++;

		if (stage == 4 && height >= 120000)
			stage++;
	}
}

std::string StatsHandler::GetScore()
{
	std::string string = std::to_string(score);	// converts score to int

	while (string.length() < 7)
	{
		string = "0" + string;	// creates string for displaying
	}

	return string;	// returns string
}

std::string StatsHandler::GetHeight()
{
	std::string string = std::to_string(height);	// converts height to int

	while (string.length() < 7)
	{
		string = "0" + string;	// creates string for displaying
	}

	return string;	// returns string
}

void StatsHandler::Reset()
{
	score = 0;	// resetting values
	height = 0;
	stage = 0;
}
