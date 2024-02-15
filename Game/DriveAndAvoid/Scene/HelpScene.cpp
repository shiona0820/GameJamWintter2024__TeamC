#include"HelpScene.h"
#include"../Utility/InputControl.h"
#include"DxLib.h"

HelpScene::HelpScene():help_image(NULL)
{

}

HelpScene::~HelpScene()
{

}

//����������
void HelpScene::Initialize()
{
	//�摜�̓ǂݍ���
	help_image = LoadGraph("Resource/images/Help.png");

	//SE�̓ǂݍ���
	buttonNO_sound = LoadSoundMem("Resource/sound/buttonNO.mp3");
	//���ʐݒ�
	ChangeVolumeSoundMem(255 * 80 / 100, buttonNO_sound);

	//�G���[�`�F�b�N
	if (help_image == -1)
	{
		throw("Resourse/images/Help.png������܂���\n");
	}
}

//�X�V����
eSceneType HelpScene::Update()
{
	//B�{�^���������ꂽ��A�^�C�g���ɖ߂�
	if (InputControl::GetButtonDown(XINPUT_BUTTON_B,0))
	{
		PlaySoundMem(buttonNO_sound, DX_PLAYTYPE_BACK, TRUE);
		return eSceneType::E_TITLE;
	}
	return GetNowScene();
}

//�`�揈��
void HelpScene::Draw() const
{
	//�w�i�摜�̕`��
	DrawGraph(0, 0, help_image, FALSE);

}

//�I��������
void HelpScene::Finalize()
{
	//�ǂݍ��񂾉摜�̍폜
	DeleteGraph(help_image);
}

//���݂̃V�[�������擾
eSceneType HelpScene::GetNowScene() const
{
	return eSceneType::E_HELP;
}