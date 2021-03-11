//ishikawa reona
//key manager
// 2021/01/28
#include "stdafx.h"
#include<Windows.h>
#include "Input.h"

UINT8 CInput::m_OldKeyState[256];
UINT8 CInput::m_KeyState[256];

void CInput::Init()
{
	memset(m_OldKeyState, 0, sizeof(UINT8)*256);
	memset(m_KeyState, 0, sizeof(UINT8) * 256);
}

void CInput::Uninit()
{
}

void CInput::Update()
{
	memcpy(m_OldKeyState, m_KeyState, sizeof(UINT8) * 256);


	GetKeyboardState(m_KeyState);

	int error=GetLastError();



}

bool CInput::GetKeyPress(UINT8 key)
{
	return (m_KeyState[key]&0x80);
}

bool CInput::GetKeyTrigger(UINT8 key)
{
	return ((m_KeyState[key] & 0x80)&& !(m_OldKeyState[key] & 0x80));
}
