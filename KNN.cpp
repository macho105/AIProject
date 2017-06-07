#include "KNN.h"

void AI::KNN::Run()
{
	for (auto i = 0; i < _test->GetObjectsCount(); i++)
	{
		auto uniqueDecisions = _train->GetUniqueDecisions();
		
		for (auto decision : uniqueDecisions)
		{
			
		}
		auto arr = Calculate(i);

		auto indexes = GetKNearest(arr);

	}
}

std::vector<double> AI::KNN::Calculate(int x)
{
	AI::Array<double> ret;

	auto xObj = _test->GetObjectAtIndex(x);
	for (auto i = 0; i < _train->GetObjectsCount(); i++)
	{
		auto yObj = _train->GetObjectAtIndex(i);
		auto result = _algorithm->Calculate(*xObj, *yObj);

		ret.push_back(result);
	}

	return ret;
}

std::vector<int> AI::KNN::GetKNearest(Array<double> _in)
{
	Array<int> ret;
	for(auto i = 0; i < k; i++)
	{
		auto max = std::max(_in.begin(),_in.end());
		auto it = max;/*STD_FIND(_in, _in.begin()-max);*/
		ret.push_back(it - _in.begin());
		STD_DELETE_ITEM_FROM_VECTOR(_in, it);
	}
	return ret;
}
