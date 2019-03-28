#pragma once
#include <string>

class HypothesisFactory
{
public:
	float a, b, c;
	HypothesisFactory() :a(0), b(0), c(0) {}
	virtual float getY(float x) = 0;

	static HypothesisFactory *what(std::string str);

};
