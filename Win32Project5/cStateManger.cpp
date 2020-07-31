#include "My_Include.h"

cStateManger::cStateManger()
{
	m_State = new cLogo;
	m_InnerState = INIT;
}

cStateManger::~cStateManger()
{
	if (m_State != NULL)
	{
		delete m_State;
	}
}

void cStateManger::GameFC(float et)
{
	int returnValue;
	switch (m_InnerState)
	{
	case INIT:
		m_State->Init();
		m_InnerState = LOOP;
		break;

	case LOOP:
		m_State->Update(et);
		m_State->Render();
		break;

	case DESTROY:
		returnValue = m_State->Destroy();
		delete m_State;

		m_InnerState = INIT;

		switch (returnValue)
		{
		case LOGO:
			m_State = new cLogo;
			break;
		case MENU:
			m_State = new cMenu;
			break;
		case GAME:
			m_State = new cGame;
			break;
		}
		break;
	}
}

void cStateManger::SetInnerState(int value)
{
	m_InnerState = value;
}