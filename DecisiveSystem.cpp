#include "DecisiveSystem.h"
#include "Object.h"
#include <cassert>

AI::DecisiveSystem::DecisiveSystem(Array2D<std::string> matrix, Array<std::string> decisions, Array<std::string> types)
:  _decisions(decisions), _attributeTypes(types)
{
	auto this_ptr = std::make_shared<DecisiveSystem>(*this);
	for (auto i = 0; i < matrix.size(); i++)
		_matrix.push_back(std::make_shared<Object>(matrix[i], i, this_ptr));
}


AI::AtributeType AI::DecisiveSystem::GetAtributeType(int index) const
{
	return _attributeTypes.size() ? _attributeTypesMap.at(_attributeTypes[index]) : kNumeric;
}

AI::Array<AI::Attribute>& AI::DecisiveSystem::GetAttributesAtIndex(int index)
{
	assert(index < _matrix.size());

	// Lazy initialization:
	auto& ret = _mapByIndex[index];
	if (ret.empty())
	{
		for (auto i = 0; i < _matrix.size(); i++)
		{
			ret.push_back(_matrix[i]->At(index));
		}
	}
	return ret;
}

AI::Array<float>& AI::DecisiveSystem::GetAttributesValues(int index)
{
	assert(index == -1 || index < _matrix.size());

	if (index != -1)
	{
		if (!_atributeToFloat.count(index))
		{
			auto& att = GetAttributesAtIndex(index);
			std::vector<float> ret;
			for (Attribute& ent : att)
				ret.push_back(ent.GetAsFloat());

			_atributeToFloat[index] = ret;
		}

		return _atributeToFloat[index];
	}

	if (_fDecisions.size())
		return _fDecisions;

	if (index == -1)
		for (auto i = 0; i < GetDecisions().size(); i++)
			_fDecisions.push_back(GetDecision(i));
	else
		throw std::exception("Invalid index");

	return _fDecisions;
}

AI::Array3D<AI::Attribute> AI::DecisiveSystem::ProduceDiffArray()
{
	Array3D<AI::Attribute> ret;

	for (auto i = 0; i < GetObjectsCount(); i++)
	{
		auto obj = GetObjectAtIndex(i);
		auto decision = GetDecision(i);

		Array2D<AI::Attribute> toAdd;

		for (auto d = 0; d < GetObjectsCount(); d++)
		{
			Array<AI::Attribute> diff;
			auto secDecision = GetDecision(d);
			if (secDecision == decision)
			{
				toAdd.push_back(diff);
				continue;
			}

			auto secLine = GetObjectAtIndex(d);
			for (auto x = 0; x < secLine->GetSize(); x++)
			{
				if (secLine->At(x).GetAsFloat() == obj->At(x).GetAsFloat())
					diff.push_back(secLine->At(x));
			}
			toAdd.push_back(diff);
		}
		ret.push_back(toAdd);
	}
	return ret;
}

AI::Array<std::shared_ptr<AI::Object>> AI::DecisiveSystem::GetObjectsWithDecision(std::string decision)
{
	return GetObjectsWithDecision(std::stoi(decision));
}

std::vector<std::shared_ptr<AI::Object>> AI::DecisiveSystem::GetObjectsWithDecision(int decision)
{
	AI::Array<std::shared_ptr<AI::Object>> ret;
	for (auto obj : _matrix)
	{
		if (obj->GetDecision() == decision)
			ret.push_back(obj);
	}
	return ret;
}
