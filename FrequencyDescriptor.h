#pragma once
#include "DecisiveSystem.h"

namespace AI
{
	struct AttributeScore
	{
		short upIndex, leftIndex, count, decision;
		std::shared_ptr<Attribute> attribute;
		Array<int> indexes;

		AttributeScore(Attribute _in,std::shared_ptr<DecisiveSystem> _system)
		{
			system = _system;
			auto object = _in.GetFather();
			//Bauto system = object->GetFather();

			attribute = std::make_shared<Attribute>(_in);
			leftIndex = _in.GetIndex();
			upIndex = object->GetIndex();
			decision = object->GetDecision();
			count = 0;
			
			for (auto i = 0; i < system->GetObjectsCount(); i++)
			{
				auto attribute = system->GetObjectAtIndex(i)->At(leftIndex);

				if (attribute.GetAsInt() == _in.GetAsInt() &&
					attribute.GetFather()->GetDecision() == object->GetDecision())
				{
					indexes.push_back(i);
					count++;
				}
			}
		}
	
		std::shared_ptr<DecisiveSystem> system;

		bool operator==(const AttributeScore& other) const
		{
			return upIndex == other.upIndex && leftIndex == other.leftIndex;
		}
		bool operator==(Attribute& _attribute) const
		{
			return _attribute == *attribute;
		}
		bool operator<(AttributeScore& other) const
		{
			if (count == other.count)
			{
				if (leftIndex == other.leftIndex)
				{
					return upIndex < other.upIndex;
				}
				return leftIndex < other.leftIndex;
			}
			return count > other.count;
		}
	};
	/*
	 * @brief Class responsible for depicting @Attributes frequency among @DecisiveSystem 
	 */
	class FrequencyDescriptor
	{
	private:
		std::shared_ptr<DecisiveSystem> _system;
		AI::Array<int>					_indexesToInclude;
		AI::Array<AttributeScore>		_alreadyConsidered;
		bool ShouldInclude(int index);
	public:
		AI::Array<int> GetIndexesToInclude() const { return _indexesToInclude; }
		FrequencyDescriptor(std::shared_ptr<DecisiveSystem> system);

		void SetAsConsidered(AttributeScore score);
		bool IsAlreadyConsidered(AttributeScore score);

		void IncludeIndexes(AI::Array<int> _in);
		void ExcludeIndexes(AI::Array<int> _in);
		std::map<int, Array<AI::AttributeScore>> AI::FrequencyDescriptor::Produce();

	};
}