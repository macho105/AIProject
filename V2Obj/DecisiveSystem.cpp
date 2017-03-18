#include "DecisiveSystem.h"
AI::DecisiveSystem::DecisiveSystem(Array2D<std::string> matrix, Array<std::string> decisions, Array<std::string> types)
: InformativeSystem(matrix, types), _decisions(decisions) { }
