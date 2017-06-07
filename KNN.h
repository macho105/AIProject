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

	class KNN
	{
	public:
		KNN(Type algo, int k, int d);
		KNN() = default;

		void SetAlgorithm(Type algo)
		{
			_algorithm = AlgorithmProvider::Instance().Get(algo);
		}
		void SetSystems(std::shared_ptr<DecisiveSystem> train, std::shared_ptr<DecisiveSystem> test)
		{
			_train = train; _test = test;
		}

		void Run();


	private:
		int k,d;
		Array<double> Calculate(int x);
		Array<int> GetKNearest(Array<double> _in);

		std::shared_ptr<DecisiveSystem> _train, _test;
		std::shared_ptr<Algorithm> _algorithm;

	};
}
