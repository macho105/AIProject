#include "Rule.h"
#include "DecisiveSystem.h"

AI::Rule::Rule(Array<Attribute> attributes, float decision, std::shared_ptr<DecisiveSystem> system)
	: _system(system),
	  _fragments(attributes),
	  _decision(decision)
{
	
}

bool AI::Rule::Check()
{
	auto system = _system.GetFather();
	if (!system)
		throw std::exception("Error, system was not set.");
	
	auto good = 0;
	for(auto i = 0; i < system->GetObjectsCount();i++)
	{
		for(auto& el : _fragments)
		{
			if (system->GetObjectAtIndex(i)->At(el.GetIndex()).GetAsFloat() == el.GetAsFloat() &&
				_system.GetFather()->GetObjectAtIndex(i)->GetDecision() != _decision)
				good++;
			if (good == _fragments.size())
				return false;
		}
		good = 0;
	}
	return !good;
}


AI::Array<AI::Rule> AI::Rule::GeneratePotentialRules(
	std::shared_ptr<Object> object,
	int level,
	std::shared_ptr<DecisiveSystem> system
)
{
	Array<AI::Rule> ret;
	auto decision = object->GetDecision();
	auto rules = comb(object->GetSize(), level);
	for(auto i = 0; i < rules.size(); i++)
	{
		Array<Attribute> fragments;
		for(auto d = 0; d < rules[i].size(); d++)
		{
			auto val = object->At(rules[i][d]).GetAsString();
			auto index = rules[i][d];

			fragments.push_back(Attribute(val, index));
		}
		ret.push_back(Rule(fragments, decision, system));
	}
	return ret;
}

std::vector<std::vector<int>> AI::Rule::comb(int size, int level)
{
	std::vector<std::vector<int>> ret;
	std::string bitmask(level, 1); // level leading 1's
	bitmask.resize(size, 0); // size-level trailing 0's

							 // print integers and permute bitmask
	do {
		std::vector<int> toAdd;
		for (auto i = 0; i < size; ++i) // [0..size-1] integers
		{
			if (bitmask[i]) toAdd.push_back(i);
		}
		ret.push_back(toAdd);
	} while (std::prev_permutation(bitmask.begin(), bitmask.end()));
	return ret;
}


std::string AI::Rule::Dump()
{
	std::string ret;
	char buffer[255];
	for(auto i  = 0; i < _fragments.size(); i++)
	{
		sprintf_s(buffer, "(a%i=%i)",_fragments[i].GetIndex() + 1,_fragments[i].GetAsInt());
		ret += buffer;
		if(i + 1 < _fragments.size())
		{
			ret += "^";
		}
		memset(buffer, 0, 255);
	}
	ret += "=>";
	ret += std::to_string(int(_decision));
	return ret;
}

AI::Rule::Rule(Array<int> attributes, int index, std::shared_ptr<DecisiveSystem> system)
{
	_system = system;
	_decision = system->GetDecision(index);
	_object = system->GetObjectAtIndex(index);
	for (auto i : attributes)
		_fragments.push_back(system->GetObjectAtIndex(index)->At(i));

}
