#pragma once
#include "DecisiveSystem.h"

namespace AI
{
	/*
	 * @brief Class responsible for depicting @Attributes frequency among @DecisiveSystem 
	 */
	class FrequencyDescriptor
	{
	private:
		std::shared_ptr<DecisiveSystem> _system;
		AI::Array<int>					_indexesToInclude;
	public:
		FrequencyDescriptor(std::shared_ptr<DecisiveSystem> system);

		void IncludeIndexes(AI::Array<int> _in);

		std::map</*Decision*/int,
		>
	};
}