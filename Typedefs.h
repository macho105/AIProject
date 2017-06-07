#pragma once
#include <vector>

#define STD_FIND(vec, item) \
	std::find(std::begin(vec),std::end(vec),item)

#define STD_DELETE_ITEM_FROM_VECTOR(vec,item) \
	if(STD_FIND(vec,item) != std::end(vec)) \
		vec.erase(STD_FIND(vec,item));

#define STD_DELETE_VECTOR_FROM_VECTOR(first,second) \
	for(auto& el : first) \
		STD_DELETE_ITEM_FROM_VECTOR(first,el);

#define STD_INSERT_VECTOR_ON_BACK(first, second) \
	first.insert(std::end(first),std::begin(second),std::end(second));

#define STD_INSERT_AND_ENSURE_UNIQUENESS(first, second) \
	first.insert(std::end(first),std::begin(second),std::end(second));\
	std::sort(std::begin(first),std::end(first));\
	first.erase(std::unique(std::begin(first), std::end(first)),std::end(first));

namespace AI
{
	template<typename T>
	using Array = std::vector<T>;

	template<typename T>
	using Array2D = Array<Array<T>>;

	template<typename T>
	using Array3D = Array<Array2D<T>>;

}
