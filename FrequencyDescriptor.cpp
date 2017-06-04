#include "FrequencyDescriptor.h"

std::map<int, AI::Array<AI::AttributeScore>> AI::FrequencyDescriptor::Produce()
{
	std::map<int, AI::Array<AI::AttributeScore>> ret;



	auto decisions = _system->GetUniqueDecisions();

	for (auto& decision : decisions)
	{
		Array<AttributeScore> scores;
		for (auto i = 0; i < _system->GetObjectsCount(); i++)
		{
			if (!ShouldInclude(i))
				continue;

			auto object = _system->GetObjectAtIndex(i);
			object->SetFather(_system);

			if (object->GetDecision() != stoi(decision))
				continue;

			for (auto d = 0; d < object->GetSize(); d++)
			{
				//AttributeScore score = AttributeScore(object->At(d));
				auto attribute = object->At(d);
				attribute.SetFather(object);

				auto score = AttributeScore(attribute, _system);
				
				if (IsAlreadyConsidered(score))
					continue;

				auto indexes = score.indexes;

				for(auto index : indexes)
				{
					if(!ShouldInclude(index))
					{
						score.count--;
						score.indexes.erase(
							std::find(std::begin(score.indexes), std::end(score.indexes), index));
					}
				}

				scores.push_back(score);
			}
		}
		std::sort(std::begin(scores), std::end(scores));
		ret[std::stoi(decision)] = scores;
	}
	return ret;
}

bool AI::FrequencyDescriptor::ShouldInclude(int index)
{
	if (_indexesToInclude.empty()) return true;

	return std::find(std::begin(_indexesToInclude), std::end(_indexesToInclude), index) 
	!= std::end(_indexesToInclude);
}

AI::FrequencyDescriptor::FrequencyDescriptor(std::shared_ptr<DecisiveSystem> system)
{
	_system = system;
}

void AI::FrequencyDescriptor::IncludeIndexes(AI::Array<int> _in)
{
	_indexesToInclude.insert(std::end(_indexesToInclude), std::begin(_in), std::end(_in));
	std::sort(std::begin(_indexesToInclude), std::end(_indexesToInclude));
	_indexesToInclude.erase(std::unique(std::begin(_indexesToInclude), std::end(_indexesToInclude)),std::end(_indexesToInclude));
}

void AI::FrequencyDescriptor::ExcludeIndexes(AI::Array<int> _in)
{
	//for(auto el : _in)
	//{
	//	auto it = std::find(std::begin(_indexesToInclude), std::end(_indexesToInclude), el);
	//	if (it != std::end(_indexesToInclude))
	//		_indexesToInclude.erase(it);
	//}
	_indexesToInclude = _in;
}

void AI::FrequencyDescriptor::SetAsConsidered(AttributeScore score)
{
	_alreadyConsidered.push_back(score);
}

bool AI::FrequencyDescriptor::IsAlreadyConsidered(AttributeScore score)
{
	return std::find(std::begin(_alreadyConsidered), std::end(_alreadyConsidered), score) != std::end(_alreadyConsidered);
}
