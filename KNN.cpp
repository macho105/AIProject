#include "KNN.h"

AI::KNN::KNN(Type algo, int k)
{
	_algorithm = AlgorithmProvider::Instance().Get(algo);
	this->k = k;
}

void AI::KNN::Run()
{
	

	for (auto i = 0; i < _test->GetObjectsCount(); i++)
	{
		auto map = GetKNearest(i);
		std::pair<double, std::string> minScore = { std::numeric_limits<double>::max(),"" };

		for (auto& decision : _test->GetUniqueDecisions())
		{
			auto score = 0.f;
			auto arr = map[decision];
			for (auto el : arr)
				score += el.first;

			if (minScore.first == score)
			{
				minScore = { std::numeric_limits<double>::max(),"" };
				continue;
			}

			if (minScore.first > score)
				minScore = { score,decision };
		}
		if (minScore.second.empty())
			printf("Couldn't classify %d object \n", i);
		else
			printf("Object %i was classiefied as :%s\n",i, minScore.second.c_str());

		minScore = { std::numeric_limits<double>::max(),"" };
	}
}

AI::KNNMap AI::KNN::GetKNearest(int xIndex)
{
	KNNMap ret;
	auto testObj = _test->GetObjectAtIndex(xIndex);
	
	for(auto& decision : _train->GetUniqueDecisions())
	{
		AI::Array<std::pair<double, std::shared_ptr<AI::Object>>> toAdd;
		AI::Array<std::pair<double, std::shared_ptr<Object>>> scores;
		auto objects = _train->GetObjectsWithDecision(decision);
		for (auto i = 0; i < objects.size(); i++)
		{
			auto trainObj = objects.at(i);

			auto score = _algorithm->Calculate(*testObj, *trainObj);

			scores.push_back({ score,trainObj });
		}
		std::sort(scores.begin(), scores.end());

		for (auto i = 0; i < k; i++)
			toAdd.push_back(scores[i]);	
		
		ret[decision] = toAdd;
	}
	

	
	return ret;
}
