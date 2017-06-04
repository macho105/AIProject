#include "FrequencyDescriptor.h"

std::map<int, std::vector<std::vector<AI::Attribute>>> AI::FrequencyDescriptor::Produce()
{
	std::map<int, std::vector<std::vector<AI::Attribute>>> ret;

	struct AttributeScore
	{
		short upIndex, leftIndex, count;
		AttributeScore(Attribute _in)
		{
			auto object = _in.GetFather();
			auto system = object->GetFather();
			
			leftIndex = _in.GetIndex();
			upIndex = object->GetIndex();
			count = 0;

			for(auto i = 0; i < system->GetObjectsCount(); i++)
			{
				auto attribute = system->GetObjectAtIndex(i)->At(leftIndex);

				if (attribute.GetAsInt() == _in.GetAsInt() &&
					attribute.GetFather()->GetDecision() == object->GetDecision())
					count++;
			}
		}
	};

	auto decisions = _system->GetUniqueDecisions();

	for(auto& decision : decisions)
	{
		for(auto i = 0; i < _system->GetObjectsCount(); i++)
		{
			auto object = _system->GetObjectAtIndex(i);

			if(object->GetDecision() != std::stoi(decision))
				continue;


		}
	}

}
