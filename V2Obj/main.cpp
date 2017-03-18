#include <Windows.h>
#include <string>
#include <iostream>
#include "DecisiveSystemReader.h"
#include "Object.h"

#define AUSTRALIAN_SYSTEM_FILENAME	"C:\\australian.txt"
#define AUSTRALIAN_TYPES_FILENAME	"C:\\australian-type.txt"

void DisplayExercise(std::string zestaw, std::string pkt,bool end = false)
{
	if (!end)
		std::cout << "========== " << zestaw << (pkt.size() ? (" pkt: " + pkt) : "") << "===========" << std::endl;
	else
		std::cout << "=============== Koniec ===============" << std::endl << std::endl << std::endl;
}

void Zestaw1()
{
	AI::DecisiveSystemReader reader(AUSTRALIAN_SYSTEM_FILENAME, AUSTRALIAN_TYPES_FILENAME);
	auto system = reader.ReadDecisiveSystem();

	auto Pkt1_A = [&]()
	{
		DisplayExercise("Zestaw 1", "A 1 ");
		auto uniques = system.GetUniqueDecisions();
		for (auto& uniq : uniques)
			std::cout << uniq << std::endl;
		DisplayExercise("", "", true);
	};
	auto Pkt1_B = [&]()
	{
		DisplayExercise("Zestaw 1", "A 2 ");

		auto uniques = system.GetUniqueDecisions();
		auto decisions = system.GetDecisions();
		for (auto& uniq : uniques)
			std::cout << uniq << " : " 
				<< std::count(decisions.begin(), decisions.end(), uniq) << std::endl;

		DisplayExercise("", "", true);
	};

	auto Pkt1_C = [&]()
	{
		DisplayExercise("Zestaw 1", "A 3 ");
		std::vector<std::pair<AI::Attribute, AI::Attribute>> ret;

		for(auto i = 0; i < system.GetObjectAtIndex(0)->GetSize(); i++)
		{
			if(system.GetAtributeType(i) == AI::kSymbolic)
			{
				ret.push_back({{"",-1},{"",-1}});
				continue;
			}
			auto attributes = system.GetAttributesAtIndex(i);
			auto toAdd = std::minmax_element(attributes.begin(), attributes.end(),
				[](AI::Attribute first, AI::Attribute seccond) {return first.GetAsFloat() < seccond.GetAsFloat(); });
		
			ret.push_back({ attributes[toAdd.first-attributes.begin()],attributes[toAdd.second - attributes.begin()] });
		}
		for (auto i = 0; i < ret.size(); i++)
			if (ret[i].first.GetAsString().empty())
				std::cout << "Index : " << i << " was symbolic." << std::endl;
			else
				std::cout << "Index : " << i << " min : " << ret[i].first.ToString() << " max : " << ret[i].second.ToString() << std::endl;
		DisplayExercise("", "", true);
	};
	auto Pkt2_A = [&]()
	{
		DisplayExercise("Zestaw 1", "B 1 ");
		AI::Array2D<AI::Attribute> ret;
		for (auto i = 0; i < system.GetObjectAtIndex(0)->GetSize(); i++)
			ret.push_back(system.GetUniqueAttributes(i));

		for (auto i = 0; i < ret.size(); i++)
		{
			std::cout << "Attribute " << i << " : " << "size : " << ret[i].size() << std::endl;
		}
		DisplayExercise("", "", true);
	};
	auto Pkt2_B = [&]()
	{
		DisplayExercise("Zestaw 1", "B 2 ");
		AI::Array2D<AI::Attribute> ret;
		for (auto i = 0; i < system.GetObjectAtIndex(0)->GetSize(); i++)
			ret.push_back(system.GetUniqueAttributes(i));

		for(auto i = 0; i < ret.size(); i++)
		{
			std::cout << "Attribute " << i << " : ";
			for (auto d = 0; d < ret[i].size(); d++)
			{
				std::cout << ret[i][d].GetAsString();
				std::cout << (d != ret[i].size() - 1 ? ", " : "\n");
			}
		}
		DisplayExercise("", "", true);

	};



	Pkt1_A();
	Pkt1_B();
	Pkt1_C();

	Pkt2_A();
	Pkt2_B();

}

DWORD main(int argc, char* argv[])
{
	Zestaw1();
	

	return S_OK;
}
