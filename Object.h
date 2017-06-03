#pragma once
#include "Rule.h"
#include "Attribute.h"
#include "Typedefs.h"

#include <cassert>

namespace AI
{
	class DecisiveSystem;

	class Object 
		: public HasFather<DecisiveSystem> 
		, std::enable_shared_from_this<Object>
	{
	private:
		Array<Attribute> _attributes;
		int _index;
		std::shared_ptr<Rule> _rule;
	public:
		Object(Array<std::string> attributes, int index, std::shared_ptr<DecisiveSystem> father = nullptr);
		//Object(Object& other) = default;
		AtributeType GetAtributeType(int index);

		int GetDecision();

		Attribute operator[](int index);

		virtual Attribute At(int index);

		size_t GetSize() const { return _attributes.size(); }
		int GetIndex() const { return _index; }
		//Exercise 2 additions:
		bool HasRule() const { return _rule.get() != nullptr; }
		void SetRule(std::shared_ptr<Rule> rule) { assert(HasRule() == false); _rule = rule; }

	};
}

