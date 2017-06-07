#include <Windows.h>
#include <string>
#include <iostream>
#include "DecisiveSystemReader.h"
#include "Object.h"
#include "FrequencyDescriptor.h"
#include <numeric>

#define AUSTRALIAN_SYSTEM_FILENAME	"C:\\australian.txt"
#define AUSTRALIAN_TYPES_FILENAME	"C:\\australian-type.txt"

#define DECISIVE_SYSTEM_FILENAME	"C:\\SystemDecyzyjny.txt"
#define LEM2_SYSTEM_FILENAME		"C:\\LEM2System.txt"




void DisplayExercise(std::string zestaw, std::string pkt = "")
{
	if (zestaw.size())
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
		DisplayExercise("");
	};
	auto Pkt1_B = [&]()
	{
		DisplayExercise("Zestaw 1", "A 2 ");

		auto uniques = system.GetUniqueDecisions();
		auto decisions = system.GetDecisions();
		for (auto& uniq : uniques)
			std::cout << uniq << " : " 
				<< std::count(decisions.begin(), decisions.end(), uniq) << std::endl;

		DisplayExercise("");
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
		DisplayExercise("");
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
		DisplayExercise("");
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
			std::cout << std::endl;
		}
		DisplayExercise("");

	};
	auto Pkt2_C = [&]()
	{
		DisplayExercise("Zestaw 1", "B 3 ");
		auto calcStandardDeviation = [&](std::vector<float> col)->float {
			auto sum = std::accumulate(col.begin(), col.end(), 0.0);
			double mean = sum / col.size();

			double sq_sum = std::inner_product(col.begin(), col.end(), col.begin(), 0.0);
			return std::sqrt(sq_sum / col.size() - mean * mean);
		};
		AI::Array<float> ret;
		for(auto i = 0; i < system.GetObjectAtIndex(0)->GetSize(); i++)
		{
			const auto& attributes = system.GetAttributesValues(i);
			ret.push_back(calcStandardDeviation(attributes));
		}
		auto decisions = system.GetAttributesValues(-1);
		ret.push_back(calcStandardDeviation(decisions));
		for(auto i = 0; i < ret.size(); i++)
		{
			if (i != ret.size() - 1)
				std::cout << "[" << i << "] : ";
			else
				std::cout << "Decision : ";

			std::cout << ret[i] << std::endl;
		}

		auto uniques = system.GetUniqueDecisions();
		for(auto i = 0; i < uniques.size(); i++)
		{
			for(auto d = 0; d < system.GetObjectAtIndex(0)->GetSize(); d++)
			{
				auto col = system.GetAttributesAtIndex(d);
				AI::Array<float> toCalc;
				for(auto x = 0; x < col.size(); x++)
				{
					if (col[x].GetFather()->GetDecision() == std::stoi(uniques[i]))
						toCalc.push_back(col[x].GetAsFloat());

				}
				std::cout << "std dev for att " << d << " decision " << uniques[i] << 
					" is: " <<calcStandardDeviation(toCalc) << "\n";


			}
		}

		DisplayExercise("");
	};


	Pkt1_A();
	Pkt1_B();
	Pkt1_C();

	Pkt2_A();
	Pkt2_B();
	Pkt2_C();
}
void Zestaw2()
{
	AI::DecisiveSystemReader reader(DECISIVE_SYSTEM_FILENAME);
	auto system = reader.ReadDecisiveSystem();
	auto finished = [](AI::DecisiveSystem* system)
	{
		for (auto i = 0; i < system->GetObjectsCount(); i++)
			if (!system->GetObjectAtIndex(i)->HasRule())
				return false;
		return true;
	};


	auto Pkt1 = [&]()
	{
		auto sys = system;
		auto level = 1;
		AI::Array<AI::Rule> rules;
		while(!finished(&sys))
		{
			for(auto i = 0; i < sys.GetObjectsCount(); i++)
			{
				auto obj = sys.GetObjectAtIndex(i);
				auto possibilities = AI::Rule::GeneratePotentialRules(obj, level,std::make_shared<AI::DecisiveSystem>(sys));

				for(auto& pos : possibilities)
				{
					if(pos.Check() && !obj->HasRule())
					{
						obj->SetRule(std::make_shared<AI::Rule>(pos));
						rules.push_back(pos);
					}
				}
			}
			level++;
		}
	};
	auto Pkt2 = [&]()
	{
		// We wanna operate on cpy:
		auto sys = system;
		auto diff = sys.ProduceDiffArray();
		
		// @brief 
		// checks for combination within @obj indexes
		// deletes occurances in @indexes
		auto checkCombinations = [&](AI::Array2D<int>& indexes, AI::Array<AI::Attribute> obj)
		{
			AI::Array2D<int> toRet;
			for(auto& vec : indexes)
			{
				auto count = 0;
				for(auto& index: vec)
				{
					for (auto& att : obj)
					{
						if (index == att.GetIndex())
							count++;
					}
				}
				if (count < vec.size())
					toRet.push_back(vec);
				count = 0;
			}
			indexes = toRet;
		};
		auto colContains = [&](AI::Array2D<int>& indexes, int colIndex)
		{
			auto i = 0;
			AI::Array<AI::Attribute> ret;
			// We finish when we reach size of any column.
			while(i < diff[0].size())
			{
				// We iterate through difference matrix column at @colIndex
				for(auto& arr : diff[colIndex])
				{
					checkCombinations(indexes, arr);
				}
				i++;
			}
		};
		
		// We want to check if any of combination in @indexes consists of already obtained rules.
		auto applyRulesToComb = [&](AI::Array2D<int>& indexes, AI::Array<AI::Rule> rules,int actualIndex)
		{
			// Check whether one of indexes covers rule
			auto applyRule = [&](AI::Array<int>& _indexes, AI::Rule rule)->bool
			{
				if (rule.GetObj()->GetIndex() != actualIndex)
					return false;

				bool foundAll = true;

				auto fragments = rule.GetFragments();
				for(auto& frag : fragments)
				{
					auto it = std::find(std::begin(_indexes), std::end(_indexes), frag.GetIndex());
					foundAll = foundAll && it != std::end(_indexes);						
				}
				return foundAll;

			};
			AI::Array2D<int> toRet = indexes;
			bool found = true;

			if (rules.empty())
				return;

			for(auto& rule : rules)
			{
				for(auto& vec : indexes)
					if(applyRule(vec,rule))
					{
						auto it = std::find(std::begin(toRet), std::end(toRet), vec);
						if(toRet.end() != it)
							toRet.erase(it);
					}
			}
			
			indexes = toRet;
		};
		auto level = 1;
		AI::Array<AI::Rule> ret;
		while(true)
		{
			AI::Array<AI::Array<int>> out;
			for(auto i = 0; i < diff.size(); i++)
			{
				out.clear();
				AI::Array2D<int> indexes = AI::Rule::comb(sys.GetObjectAtIndex(0)->GetSize(), level);
				AI::Array<AI::Attribute> buff;

				applyRulesToComb(indexes,ret,i);
				colContains(indexes, i);
				

				// Printing:
				if (indexes.size())
				{
					printf("dla o%i mamy:\n",i+1);
					for(auto vec : indexes)
					{
						for(auto d = 0; d < vec.size(); d++)
						{
							printf("(a%i=%i)", vec[d] + 1, sys.GetObjectAtIndex(i)->At(vec[d]).GetAsInt());
							if (d+1 < vec.size())
							{
								printf("&");
							}
						}
						printf("=>%i\n", sys.GetDecision(i));

					}
				}
		
				for (auto el : indexes)
				{
					ret.push_back({ el, i, std::make_shared<AI::DecisiveSystem>(sys) });
				}
				
			}


			// Footer:
			static int lastSize;
			if (lastSize == 0)
				lastSize = ret.size();
			else
				// No size gain, we can finish now:
				if (lastSize == ret.size())
					return;
				else
					lastSize = ret.size();

			level++;
			printf("**** Level %i ****\n", level);
		}

		return;
	};
	auto Pkt3 = [&]()
	{
		AI::DecisiveSystemReader lemReader(LEM2_SYSTEM_FILENAME);
		auto lemSystem = lemReader.ReadDecisiveSystem();
		auto uniqDecisions = lemSystem.GetUniqueDecisions();
		
		AI::FrequencyDescriptor frequencyDescriptor(std::make_shared<AI::DecisiveSystem>(lemSystem));

		auto map = frequencyDescriptor.Produce();
		AI::Array<AI::Rule> rules;
		AI::Array<int> covers;
		while (true)
		{
			for (auto decision : uniqDecisions)
			{
				while(covers.size() < lemSystem.CountDecision(std::stoi(decision)))
				{
					auto actualConcept = std::stoi(decision);
					AI::Array<AI::AttributeScore> scores;
					scores.push_back(map[actualConcept].front());

					AI::Rule rule({ *scores.front().attribute },
						actualConcept, std::make_shared<AI::DecisiveSystem>(lemSystem));

					auto& fragments = rule.GetFragments();
					auto score = scores.back();

					frequencyDescriptor.IncludeIndexes(score.indexes);
					while (!rule.Check())
					{

						for (auto i = 0; i < score.indexes.size(); i++)
							frequencyDescriptor.SetAsConsidered(map[actualConcept][i]);

						frequencyDescriptor.ExcludeIndexes(score.indexes);

						map = frequencyDescriptor.Produce();
						if(map[actualConcept].size() == 0)
							break;
						
						score = map[actualConcept].front();
						scores.push_back(score);
						fragments.push_back(*score.attribute);
					}
					printf("%s\n", rule.Dump().c_str());
					rules.push_back(rule);

					STD_INSERT_AND_ENSURE_UNIQUENESS(covers, score.indexes);
					scores.clear();
					frequencyDescriptor.Reset();
					frequencyDescriptor.ReverseAndExclude(covers);
					map = frequencyDescriptor.Produce();
				}	
				covers.clear();
			}
			break;
		}

		return;
	};
	//Pkt1();
	//Pkt2();
	//Pkt3();

	auto choinka = []()
	{
		int width = 237, treeWidth = 1;
		auto drawSpaces = [](int i) {while (i) { printf(" "); i--; }};
		for (int i = 0; i < 59; i++)
		{
			int start = abs(treeWidth / 2 + 1);
			start = width / 2 - start;
			drawSpaces(start - 1);
			for (int d = 0; d < treeWidth; d++)
				printf("*");
			//drawSpaces(start + treeWidth + 1);
			printf("\n");
			treeWidth += 2;
		}
	};
	//choinka();
	return;
}

DWORD main(int argc, char* argv[])
{
	//Zestaw1();
	//Zestaw2();

	system("pause");
	return S_OK;
}
