#pragma once
#include "HasFile.h"
#include "DecisiveSystem.h"
#include <boost/algorithm/string.hpp>


namespace AI
{
	class DecisiveSystemReader 
	{
	private:
		HasFile *_system, *_descriptor;
	public:
		DecisiveSystemReader(std::string systemPath, std::string descriptorPath) 
			: _system(new HasFile(systemPath))
		{
			if (descriptorPath.size())
				_descriptor = new HasFile(descriptorPath);
		}
		~DecisiveSystemReader()
		{
			delete _system;

			if(_descriptor)
				delete _descriptor;
		}

		DecisiveSystem ReadDecisiveSystem()
		{
			Array2D<std::string> matrix;
			Array<std::string> types,decisions,splitted;
			std::string buff;

			while (std::getline(_system->GetFile(), buff, '\n'))
			{
				boost::split(splitted, buff, boost::is_any_of(" "));
				Array<std::string> to_add;
				auto i = 0;
				for (auto entry : splitted)
				{
					to_add.push_back(entry);
					i++;
				}
				matrix.push_back(to_add);

				if (_system->GetFile().eof()) break;
			}
			
			buff.clear(); splitted.clear();

			if(_descriptor)
			{
				while (std::getline(_descriptor->GetFile(), buff, '\n'))
				{
					boost::split(splitted, buff, boost::is_any_of(" "));
					types.push_back(splitted[1]);
					if (_descriptor->GetFile().eof()) break;
				}
			}
			for(auto& el : matrix)
			{
				decisions.push_back(el.back());
				el.pop_back();
			}
			// Syntax sugar
			return{ matrix, decisions ,types };
		}
	};
}
