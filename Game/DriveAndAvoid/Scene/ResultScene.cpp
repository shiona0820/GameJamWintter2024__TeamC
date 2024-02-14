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
	//�摜�̓ǂݍ���
	back_ground = LoadGraph("Resource/images/back.bmp");

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
	if (GameMainScene::Wineer == 1);
	switch (GameMainScene::Wineer)
	{
	case 1:
		DrawString(0, 0, "player1", GetColor(255, 255, 255));
		break;
	case 2:
		DrawString(0, 0, "player2", GetColor(255, 255, 255));
		break;
	case 3:
		DrawString(0, 0, "player3", GetColor(255, 255, 255));
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
