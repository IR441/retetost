//ishikawa reona
//key manager
// 2021/01/28
#pragma once

class CInput
{
private:
	static UINT8 m_OldKeyState[256];
	static UINT8 m_KeyState[256];
public:
	static void Init();
	static void Uninit();
	static void Update();

	static bool GetKeyPress(UINT8 key);
	static bool GetKeyTrigger(UINT8 key);

};

