#include "States.h"

bool States::GetPausedstate()
{
	return States::bPaused;
}

void States::SetPausedState(bool bState)
{
	bPaused = bState;
}
