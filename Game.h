//ishikawa reona
//game��ʃ}�l�[�W���[
//2021/03/01
//�w���p�[�̊֌W���ʑJ�ځi���f���̓ǂݍ��ݒ������ł��Ȃ����߁j�ł��Ȃ�
#pragma once

class CGame:public CScene
{
private:
	int m_Score = 0;
	bool m_TitleFlag = false;
	bool m_ClearFlag = false;
public:
	void Init();

	//game object
	Object m_Bullet;
	Object m_Enemy;

	//ui object
	Object m_One;
	Object m_Two;
	Object m_Three;
	Object m_Four;
	Object m_Five;
	Object m_Six;
	Object m_Seven;
	Object m_Eight;
	Object m_Nine;
	Object m_Zero;
	//ui
	Object m_Title;
	Object m_Clear;

	void Reset();

};

