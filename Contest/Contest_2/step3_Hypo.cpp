#include "step3_Linear_Quad.h"


HypothesisFactory *HypothesisFactory::what(std::string str)
{
	if (str == "Linear")
		return new Linear;
	else if (str == "Quadra")
		return new Quadratic;
	else
		return new Linear;
}