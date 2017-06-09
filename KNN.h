#pragma once
#include "Algorithm.h"
#include "AlgorithmProvider.h"
#include "DecisiveSystem.h"
#include <memory>

namespace AI
{
	struct KNNResult
	{
		Array<Attribute> xAttribute;
		Array<Attribute> yAttributes;
		double power;
	};
	
	using KNNMap = std::map<std::string, AI::Array<std::pair<double, std::shared_ptr<AI::Object>>>>;

	

	class KNN
	{
	struct Report
	{
		struct DecisionReport
		{
			int index;
			std::string decision, originalDecision;
		};
		Array<DecisionReport> reports;
		std::shared_ptr<DecisiveSystem> test, train;

		std::string Dump();
	};
	public:
		KNN(Type algo, int k);
		KNN() = default;

		void SetAlgorithm(Type algo)
		{
			_algorithm = AlgorithmProvider::Instance().Get(algo);
		}
		void SetSystems(std::shared_ptr<DecisiveSystem> train,
			std::shared_ptr<DecisiveSystem> test)
		{
			_train = train; _test = test;
		}

		AI::KNN::Report Run();


	private:
		int k;
		KNNMap AI::KNN::GetKNearest(int xIndex);
		
		


		std::shared_ptr<DecisiveSystem> _train, _test;
		std::shared_ptr<Algorithm> _algorithm;

	};
}
