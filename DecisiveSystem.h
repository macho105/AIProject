#pragma once
#include "Object.h"
#include <map>

namespace AI
{
	class DecisiveSystem 
	{
	protected:
		const std::map<std::string, AtributeType> _attributeTypesMap =
		{ { "s",kSymbolic },{ "n", kNumeric } };
		Array<std::string> _attributeTypes;
		Array<std::shared_ptr<Object>> _matrix;
		std::map<int, Array<Attribute>> _mapByIndex;
		std::map<int, Array<float>>		_atributeToFloat;
	private:

		Array<std::string> _decisions;
		Array<float>		_fDecisions;
		//Array<std::shared_ptr<Rule>> _rules;
	public:
		virtual ~DecisiveSystem() = default;
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
		AtributeType GetAtributeType(int index) const;
		size_t GetObjectsCount() { return _matrix.size(); }
		std::shared_ptr<Object> GetObjectAtIndex(int index) { return _matrix[index]; }
		Array<Attribute>& GetAttributesAtIndex(int index);
		Array<float>& GetAttributesValues(int index);
		Array3D<Attribute> ProduceDiffArray();
		int CountDecision(int decision)
		{
			int ret = 0;
			for (auto obj : _matrix)
				if (obj->GetDecision() == decision)
					ret++;
			return ret;
		}
		Array<std::shared_ptr<Object>> GetObjectsWithDecision(std::string decision);
		Array<std::shared_ptr<Object>> GetObjectsWithDecision(int decision);

		std::map<std::string, int> GetDecisionsCount();
	};
}

