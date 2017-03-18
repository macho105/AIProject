#pragma once
#include <memory>


namespace AI
{
	template<typename T>
	class HasFather
	{
	private:
		std::shared_ptr<T> _father;
	public:
		virtual ~HasFather() = default;
		HasFather(std::shared_ptr<T> father = nullptr) : _father(father) {};

		void SetFather(std::shared_ptr<T> father)
		{
			_father = father;
		}
		std::shared_ptr<T> GetFather()
		{
			return _father;
		}
	};
}
