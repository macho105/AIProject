#pragma once
#include <array>
#include "InformativeSystem.h"


namespace AI
{
	class DecisiveSystem 
		: public InformativeSystem
	{
	private:

		Array<std::string> _decisions;
	public:
		DecisiveSystem(Array2D<std::string> matrix, Array<std::string> decisions, Array<std::string> types);

		virtual int GetDecision(int index)
		{
			return std::stoi(_decisions[index]);
		}
		const Array<std::string>& GetDecisions() const 
		{
			return _decisions;
		}
		Array<std::string> GetUniqueDecisions() const
		{
			auto vec = _decisions;
			std::sort(vec.begin(), vec.end());
			vec.erase(
				std::unique(vec.begin(), vec.end())
				, vec.end());
			return vec;
		}
		Array<Attribute> GetUniqueAttributes(int index)
		{
			auto ret = GetAttributesAtIndex(index);
			return Attribute::GetUniques(ret);
			
		}
	};
}

