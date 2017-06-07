#pragma once
#include "Algorithm.h"


namespace AI
{
	class Euclid 
		: public Algorithm
	{
		double Calculate(Object first, Object second) override
		{
			assert(first.GetSize() == second.GetSize());
			double ret = 0;
			
			for(auto i = 0; i < first.GetSize(); i++)
			{
				double temp = 0;
				temp = first.At(i).GetAsFloat() - second.At(i).GetAsFloat();
				ret += std::pow(temp, 2);
			}

			return std::sqrt(ret);
		}
		Type GetType() override { return Type::kEuclid; }
	};
}
