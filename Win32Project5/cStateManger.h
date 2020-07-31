#pragma once

class cState;

class cStateManger
{
public:
	cState* m_State;
	int m_InnerState;

public:
	cStateManger();
	~cStateManger();

	void GameFC(float et);
	void SetInnerState(int value);
};