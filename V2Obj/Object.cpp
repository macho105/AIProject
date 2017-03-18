#include "Object.h"

AI::Object::Object(Array<std::string> attributes, int index, std::shared_ptr<InformativeSystem> father) 
: HasFather<AI::InformativeSystem>(father), _index(index)
{
	auto this_ptr = std::make_shared<Object>(*this);
	for (auto i = 0; i < attributes.size(); i++)
		_attributes.push_back(Attribute(attributes[i], i, this_ptr, GetAtributeType(i)));
}

AI::AtributeType AI::Object::GetAtributeType(int index) { return GetFather()->GetAtributeType(index); }

int AI::Object::GetDecision()
{
	auto father = std::dynamic_pointer_cast<DecisiveSystem>(this->GetFather());
	if (father) { return father->GetDecision(_index); }
	return -1;
}

AI::Attribute AI::Object::operator[](int index) { return At(index); }
AI::Attribute AI::Object::At(int index) { return _attributes[index]; }
