#pragma once
#include "Object.h"

namespace AI
{
	
	enum Type
	{
		kManhattan,
		kEuclid,
		kCanberr,
		kChebyshev,
		kPearson
	};

	class Algorithm
	{
	public:
		virtual ~Algorithm() = default;
		Algorithm() = default;
		virtual double Calculate(Object first, Object second) = 0;
		virtual Type GetType() = 0;
	};
	
}
