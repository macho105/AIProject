#pragma once
#include <memory>
#include "Algorithm.h"
#include <map>
#include "Algorithms.h"

#define ALGO_PROVIDER_ADD(name) _map[k##name] = std::make_shared<name>(name())

#define ALGO_PROVIDER_ADD_NAME(name) _names[k##name] = std::string(##"name##")
namespace AI
{
	class AlgorithmProvider
	{
	private:
		std::map<Type, std::shared_ptr<Algorithm>> _map;
		std::map<Type, std::string> _names;
		AlgorithmProvider()
		{
			//_map[kEuclid] = std::make_shared<Euclid>(Euclid());

			ALGO_PROVIDER_ADD(Euclid);
			ALGO_PROVIDER_ADD(Manhattan);
			ALGO_PROVIDER_ADD(Chebyshev);
			ALGO_PROVIDER_ADD(Canberr);
			ALGO_PROVIDER_ADD(Pearson);
		}
		~AlgorithmProvider() = default;

	public:
		static AlgorithmProvider& Instance()
		{
			static AlgorithmProvider provider;
			return provider;
		}
		std::shared_ptr<Algorithm> Get(Type type)
		{
			return _map[type];
		}
	};
}
