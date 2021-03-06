#pragma once
#include "HasFather.h"
#include "Typedefs.h"

namespace AI
{
	class DecisiveSystem;
	class Object;
	class Attribute;

	class Rule
	{
		HasFather<DecisiveSystem> _system;
		std::shared_ptr<Object>	  _object = nullptr;
		Array<Attribute>		  _fragments;
		float					  _decision;
		int						  _support = 0;
	public:
		explicit Rule(Array<Attribute> attributes,
			float decision,
			std::shared_ptr<DecisiveSystem> system = nullptr);
		Rule(Array<int> attributes,
			int index, 
			std::shared_ptr<DecisiveSystem> system);

		size_t GetLevel() const { return _fragments.size(); }
		bool Check();
		Array<Attribute>& GetFragments() { return _fragments; }
		std::shared_ptr<Object> GetObj() { return _object; }
		static Array<Rule> GeneratePotentialRules(std::shared_ptr<Object> object, int level, std::shared_ptr<DecisiveSystem> system = nullptr);
		static std::vector<std::vector<int>> comb(int size, int level);
		Array<int> GetIndexesRuleCovers();
		std::string Dump();
		void IncreaseSupport() { _support++; }
		void SetSupport(int val) { _support = val; }
		int GetSupport() { return _support; }
		bool operator==(Rule other);
		int GetDecision() { return _decision; }
	};
}
