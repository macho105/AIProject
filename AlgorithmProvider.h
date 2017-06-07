#pragma once
#include <memory>
#include "Algorithm.h"
#include <map>
#include "Euclid.h"


namespace AI
{
	class AlgorithmProvider
	{
	private:
		std::map<Type, std::shared_ptr<Algorithm>> _map;
		AlgorithmProvider()
		{
			_map[kEuclid] = std::make_shared<Euclid>(Euclid());
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
