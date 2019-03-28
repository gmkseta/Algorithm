#pragma once
#include "step3_Hypo.h"

class Linear :public HypothesisFactory
{
public:
	float getY(float x)
	{
		return a*x + b;
	}
};


class Quadratic :public HypothesisFactory
{
public:
	float getY(float x)
	{
		return a*x*x + b*x + c;
	}
};


