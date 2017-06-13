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
			double ret = 0;

			for (auto i = 0; i < first.GetSize(); i++)
			{
				double temp = 0;
				temp = std::abs(first.At(i).GetAsFloat() - second.At(i).GetAsFloat());
				if (temp > ret) ret = temp;
			}
			return ret;
		}

		Type GetType() override { return Type::kPearson; }
	};
}
