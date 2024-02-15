#include "ResultScene.h"
#include "GameMainScene.h"
#include"../Utility/InputControl.h"
#include"DxLib.h"

ResultScene::ResultScene() : back_ground(NULL)
{

}

ResultScene::~ResultScene()
{

}

//����������
void ResultScene::Initialize()
{
	
	switch (GameMainScene::Wineer)
	{
	case 1:
		back_ground = LoadGraph("Resource/images/player1win.png");
		break;
	case 2:
		//�摜�̓ǂݍ���
		back_ground = LoadGraph("Resource/images/player2win.png");
		break;
	case 3:
		back_ground = LoadGraph("Resource/images/player3win.png");
		break;
	case 4:
		back_ground = LoadGraph("Resource/images/player4win.png");
		break;
	default:
		break;
	}


	//�G���[�`�F�b�N
	if (back_ground == -1)
	{
		throw("Resource/image/back.bmp������܂���\n");
	}

}

//�X�V����
eSceneType ResultScene::Update()
{
	//B�{�^���Ń����L���O�ɑJ�ڂ���
	if (InputControl::GetButtonDown(XINPUT_BUTTON_B,0))
	{
		return eSceneType::E_TITLE;
	}
	return GetNowScene();
}

//�`�揈��
void ResultScene::Draw() const
{
	//�w�i�摜��`��
	DrawGraph(0, 0, back_ground, TRUE);
	switch (GameMainScene::Wineer)
	{
	case 1:
		DrawString(600, 0, "player1win!", GetColor(255, 255, 255));
		break;
	case 2:
		DrawString(600, 0, "player2win!", GetColor(255, 255, 255));
		break;
	case 3:
		DrawString(600, 0, "player3win!", GetColor(255, 255, 255));
		break;
	case 4:
		DrawString(600, 0, "player4win!", GetColor(255, 255, 255));
		break;
	default:
		break;
	}
}

//�I��������
void ResultScene::Finalize()
{
	//�ǂݍ��񂾉摜���폜
	DeleteGraph(back_ground);
}

//���݂̃V�[�������擾
eSceneType ResultScene::GetNowScene() const
{
	return eSceneType::E_RESULT;
}
