#pragma once
#include "Typedefs.h"
#include "Attribute.h"
#include <map>

namespace AI
{
	class Object;
	class InformativeSystem 
	{
	protected:
		const std::map<std::string, AtributeType> _attributeTypesMap =
		{ { "s",kSymbolic },{ "n", kNumeric } };
		Array<std::string> _attributeTypes;
		Array<std::shared_ptr<Object>> _matrix;
		std::map<int, Array<Attribute>> _mapByIndex;
	public:
		virtual ~InformativeSystem() = default;
		InformativeSystem(Array2D<std::string> matrix, Array<std::string> types);
		virtual AtributeType GetAtributeType(int index) const;
		virtual size_t GetObjectsCount() { return _matrix.size(); }
		virtual std::shared_ptr<Object> GetObjectAtIndex(int index) { return _matrix[index]; }
		virtual Array<Attribute> GetAttributesAtIndex(int index);
	};
}
