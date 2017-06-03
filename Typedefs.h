#pragma once
#include <vector>


namespace AI
{
	template<typename T>
	using Array = std::vector<T>;

	template<typename T>
	using Array2D = Array<Array<T>>;

	template<typename T>
	using Array3D = Array<Array2D<T>>;

}
