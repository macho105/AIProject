#pragma once
#include <string>
#include <memory>
#include "HasFather.h"
#include <algorithm>

namespace AI
{
	class Object;

	enum AtributeType
	{
		kNumeric,
		kSymbolic,
		kNone
	};
	class Attribute : public HasFather<Object>
	{
	private:
		std::string _raw;
		AtributeType _type;
		float* _fVal;
		int* _intVal;
		int _index;
	public:
		bool operator==(int index) const { return index == _index; }
		bool operator==(Attribute other) { return GetAsInt() == other.GetAsInt() && _index == other.GetIndex(); }


		int GetIndex() const { return _index; }
		Attribute(std::string val,int index,std::shared_ptr<AI::Object> father = nullptr, AtributeType type = kNone)
			: HasFather<AI::Object>(father), _raw(val)
			, _type(type)	, _fVal(nullptr)
			, _intVal(nullptr), _index(index)
		{

		}
		std::string ToString()
		{
			return _raw + " " + " type: " + std::to_string(GetType()) + " index: " + std::to_string(_index);
		}
		AtributeType GetType()
		{
			return _type;
		}

		template<typename T>
		T GetValue()
		{
			if (typeid(int) == typeid(T))
			{
				if(!_intVal)
				*_intVal = std::stoi(_raw);
				return *_intVal;
			}
			
			if (typeid(float) == typeid(T))
			{
				if (!_fVal)
					*_fVal = std::stof(_raw);
				return *_fVal;
			}

			if (typeid(std::string) == typeid(T))
				return _raw;

			throw std::exception("Unsupported GetValue call.");
		}

		float GetAsFloat()
		{
			if (!_fVal)
				_fVal =  new float(std::stof(_raw));
			return *_fVal;
		}
		int GetAsInt()
		{
			if (!_intVal)
				_intVal = new int(std::stoi(_raw));
			return *_intVal;
		}
		std::string GetAsString()
		{
			return _raw;
		}

		static Array<Attribute> GetUniques(Array<Attribute> ret)
		{
			std::sort(ret.begin(), ret.end(), [](Attribute first, Attribute second) {return first.GetAsFloat() > second.GetAsFloat(); });
			ret.erase(std::unique(ret.begin(), ret.end(),
				[](Attribute first, Attribute seccond) {return first.GetAsString() == seccond.GetAsString(); }), ret.end());
			return ret;
		}
		static Array<Attribute> GetUniqueIndexes(Array<Attribute> ret)
		{
			std::sort(ret.begin(), ret.end(), [](Attribute first, Attribute second) {return first.GetIndex() < second.GetIndex(); });
			ret.erase(std::unique(ret.begin(), ret.end(),
				[](Attribute first, Attribute seccond) {return first.GetIndex() == seccond.GetIndex(); }), ret.end());

			return ret;
		}

	};
}
