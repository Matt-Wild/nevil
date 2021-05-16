#pragma once

#include <string>

class StatsHandler
{
protected:
	int score = 0, height = 0, stage = 0;	// storing score, height and stage

public:
	void AddScore(int _amount) { score += _amount; };	// adds amount to score
	void UpdateHeight(int _height);	// updates max height reached

	void Reset();	// resets stats

	// getters
	std::string GetScore();	// gets score
	int GetScoreInt() { return score; }	// get score in integer form
	std::string GetHeight();	// gets max height reached
	int GetStage() { return stage; }	// returns difficult level
};
