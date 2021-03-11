#pragma once
class CUIManager
{private:
	static bool* ma_TitleFlagPointer;
	static bool* ma_ClearFlagPointer;
public:
	//Get 
	static bool GetTitleFlag() { return *ma_TitleFlagPointer; }
	static bool GetClearFlag() { return *ma_ClearFlagPointer; }
	//Set
	static void SetTitleFlagPointer(bool* titleflag) { ma_TitleFlagPointer = titleflag; }
	static void SetClearFlagPointer(bool* clearflag) { ma_ClearFlagPointer = clearflag; }

	static void SetTitleFlag(bool titleflag) {*ma_TitleFlagPointer = titleflag; }
	static void SetClearFlag(bool clearflag) {*ma_ClearFlagPointer = clearflag; }

};

