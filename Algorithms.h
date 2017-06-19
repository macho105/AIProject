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

			for (auto i = 0; i < first.GetSize(); i++)
			{
				double temp = 0;
				temp = first.At(i).GetAsFloat() - second.At(i).GetAsFloat();
				ret += std::pow(temp, 2);
			}

			return std::sqrt(ret);
		}

		Type GetType() override { return Type::kEuclid; }
	};

	class Manhattan
			: public Algorithm
	{
		double Calculate(Object first, Object second) override
		{
			assert(first.GetSize() == second.GetSize());
			double ret = 0;
			for (auto i = 0; i < first.GetSize(); i++)
			{
				double temp = 0;
				temp = first.At(i).GetAsFloat() - second.At(i).GetAsFloat();
				ret += std::abs(temp);
			}
			return ret;
		}

		Type GetType() override { return Type::kManhattan; }
	};

	class Canberr
			: public Algorithm
	{
		double Calculate(Object first, Object second) override
		{
			assert(first.GetSize() == second.GetSize());
			double ret = 0;
			for (auto i = 0; i < first.GetSize(); i++)
			{
				double temp = 0;
				temp = (first.At(i).GetAsFloat() - second.At(i).GetAsFloat()) / (first.At(i).GetAsFloat() + second.At(i).GetAsFloat());
				ret += std::abs(temp);
			}
			return ret;
		}

		Type GetType() override { return Type::kCanberr; }
	};

	class Chebyshev
			: public Algorithm
	{
		double Calculate(Object first, Object second) override
		{
			assert(first.GetSize() == second.GetSize());
			double ret = 0;

			for (auto i = 0; i < first.GetSize(); i++)
			{
				double temp = 0;
				temp = std::abs(first.At(i).GetAsFloat() - second.At(i).GetAsFloat());
				if (temp > ret) ret = temp;
			}
			return ret;
		}

		Type GetType() override { return Type::kChebyshev; }
	};
	class Pearson
		: public Algorithm
	{
		double Calculate(Object first, Object second) override
		{
			assert(first.GetSize() == second.GetSize());
			//double ret = 0,x = 0,y = 0, n = 1 / (double)first.GetSize();

			auto fCalcMeanforObj = [&](Object obj)->double
			{
				double sum = 0;
				for (auto i = 0; i < obj.GetSize(); i++)
					sum += obj.At(i).GetAsFloat();
				sum /= obj.GetSize();
				return sum;
			};
			//auto calcYetAnotherParam = [&](Object obj, double param)->double
			//{
			//	double out = 0;
			//	double top = 0, bottom = 0;
			//	for(auto i = 0; i < obj.GetSize(); i++)
			//	{

			//		//top
			//		top += (obj.At(i).GetAsFloat() - param);
			//		//bottom
			//		for(auto d = 0; d < obj.GetSize(); d++)
			//		{
			//			bottom += std::pow((obj.At(d).GetAsFloat() - param), 2);
			//		}

			//	}
			//	bottom *= n;
			//	bottom = std::sqrt(bottom);
			//	out += top / bottom;
			//	return out;
			//};
			//x = calcSomeParam(first); y = calcSomeParam(second);

			//ret = n * calcYetAnotherParam(first, x) * calcYetAnotherParam(second, y);

			//return 1 - std::abs(ret);
			
			auto fDenominator = [](Object obj, double mean)->double
			{
				AI::Array<double> ret;
				for(auto i = 0; i < obj.GetSize(); i++)
				{
					ret.push_back(std::pow(obj.At(i).GetAsFloat() - mean, 2));
				}
				return std::sqrt(STD_CALCULATE_MEAN(ret));
			};
			AI::Array<double> ret;
			double x = fCalcMeanforObj(first), y = fCalcMeanforObj(second),
				xDenominator = fDenominator(first, x), yDenominator = fDenominator(second, y);

			for(auto i = 0; i < first.GetSize(); i++)
			{
				ret.push_back(((first.At(i).GetAsFloat() - x) / xDenominator) *
					((second.At(i).GetAsFloat() - y) / yDenominator));
			}

			return std::abs(STD_CALCULATE_MEAN(ret));
		}

		Type GetType() override { return Type::kPearson; }
	};
}
