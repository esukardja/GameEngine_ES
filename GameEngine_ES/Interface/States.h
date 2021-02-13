#pragma once
static class States
{
public:
	static bool GetPausedstate();
	static void SetPausedState(bool bState);

private:
	static bool bPaused;
};

