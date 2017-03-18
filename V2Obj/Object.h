#pragma once
#include "Typedefs.h"
#include "Attribute.h"
#include "HasFather.h"
#include "DecisiveSystem.h"

namespace AI
{
	class InformativeSystem;
	class DecisiveSystem;

	class Object 
		: public HasFather<InformativeSystem> 
		, std::enable_shared_from_this<Object>
	{
	private:
		Array<Attribute> _attributes;
		int _index;
	public:
		Object(Array<std::string> attributes, int index, std::shared_ptr<InformativeSystem> father = nullptr);

		AtributeType GetAtributeType(int index);

		int GetDecision();

		Attribute operator[](int index);

		virtual Attribute At(int index);

		size_t GetSize() const { return _attributes.size(); }
	};
}

