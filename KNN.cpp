#include "KNN.h"
#include <iomanip>


template <typename T>
static std::string to_string_with_precision(const T a_value, const int n = 6)
{
	std::ostringstream out;
	out << std::setprecision(n) << a_value;
	return out.str();
}

AI::KNN::KNN(Type algo, int k)
{
	_algorithm = AlgorithmProvider::Instance().Get(algo);
	this->k = k;
}

AI::KNN::Report AI::KNN::Run()
{
	Report report;

	report.test = _test;
	report.train = _train;

	if (k > _test->GetObjectAtIndex(0)->GetSize())
		return report;

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

		auto isPositivelyClassified = false;

		if (minScore.second.empty())
		{
			printf("Couldn't classify %d object \n", i);
		}
		else
		{
			isPositivelyClassified = std::stoi(minScore.second) == _test->GetObjectAtIndex(i)->GetDecision();

			printf("Object %i was classiefied as :%s isPositivelyClassified: %s\n", i, minScore.second.c_str(),
				isPositivelyClassified ? "TRUE" : "FALSE");
		}
		
		Report::DecisionReport toAdd;

		toAdd.decision = minScore.second;
		toAdd.index = i;
		toAdd.originalDecision = std::to_string(_test->GetObjectAtIndex(i)->GetDecision());

		report.reports.push_back(toAdd);

		minScore = { std::numeric_limits<double>::max(),"" };
	}

	return report;
}

AI::KNNMap AI::KNN::GetKNearest(int xIndex)
{
	KNNMap ret;
	auto testObj = _test->GetObjectAtIndex(xIndex);
	
	for(auto& decision : _train->GetUniqueDecisions())
	{
		AI::Array<std::pair<double, std::shared_ptr<AI::Object>>> toAdd,scores;
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

std::string AI::KNN::Report::Dump()
{
	std::string ret;
	std::map<std::string, std::map<std::string, int>> countMap;
	auto decisionCounts = test->GetDecisionsCount();

	ret += "\t\t\t\t";
	for(auto decision : this->test->GetUniqueDecisions())
	{
		ret += decision;
		ret += "\t";
	}
	ret += "No. of obj.\t";
	ret += "Accuracy\t";
	ret += "Coverage\n";


	for(auto report : this->reports)
	{		
		countMap[report.decision][report.originalDecision]++;
	}
	
	for(auto decision : this->test->GetUniqueDecisions())
	{
		ret += "\t\t\t";
		ret += decision;
		ret += "\t";
		for(auto second : this->test->GetUniqueDecisions())
		{
			ret += std::to_string(countMap[second][decision]);
			ret += "\t";
		}
		ret += std::to_string(decisionCounts[decision]);
		ret += "\t\t";

		// Accuracy:
		double score = 0;
		double total = 0;

		for(auto& obj : reports)
		{
			if(obj.originalDecision == decision)
			{
				total++;
				if (obj.decision == obj.originalDecision || obj.decision.empty())
					score++;
			}
		}
		score /= total;

		ret += to_string_with_precision(score, 2);
		ret += "\t\t";

		// Coverage:
		score = 0;
		total = 0;
		for (auto& obj : reports)
		{
			if (obj.originalDecision == decision)
			{
				if (!obj.decision.empty())
					score++;
			}
		}
		score /= decisionCounts[decision];
		ret += to_string_with_precision(score, 2);
		ret += "\n";
	}
	
	ret += "True Positive Rate\t";
	float tpr = 0, wrong = 0;
	for(auto decision : test->GetUniqueDecisions())
	{
		for (auto obj : reports)
		{
			if (obj.decision == decision)
			{
				if (obj.originalDecision == obj.decision || obj.decision.empty())
					tpr++;
				else
					wrong++;
			}
		}
		tpr = tpr / (tpr + wrong);
		ret += to_string_with_precision(tpr, 2);
		ret += "\t";
		tpr = 0;
		wrong = 0;
	}
	
	ret += "\n";

	double accGlobal = 0, catchedObjects = 0, classifiedGood = 0 , covGlobal = 0, objCount = 0;
	objCount = test->GetObjectsCount();
	
	for(auto& report : reports)
	{
		if (!report.decision.empty())
			catchedObjects++;

		if (report.decision == report.originalDecision && !report.decision.empty())
			classifiedGood++;
	}

	accGlobal = classifiedGood / catchedObjects;
	covGlobal = catchedObjects / objCount;
	
	ret += "Global Accuracy: ";
	ret += to_string_with_precision(accGlobal, 2);
	ret += " Global Coverage: ";
	ret += to_string_with_precision(covGlobal, 2);
	ret += "\n";

	return ret;
}


