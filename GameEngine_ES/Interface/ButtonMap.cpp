#include "ButtonMap.h"

std::map<std::string, Button*> buttons;

std::map<std::string, Button*>& ButtonMap::GetMap()
{
	return buttons;
}
