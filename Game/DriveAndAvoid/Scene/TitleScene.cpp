#include"TitleScene.h"
#include"../Utility/InputControl.h"
#include"DxLib.h"

TitleScene::TitleScene() : background_image(NULL), menu_image(NULL),
cursor_image(NULL), menu_cursor(0)
{

}

TitleScene::~TitleScene()
{

}

//����������
void TitleScene::Initialize()
{
	//�摜�̓ǂݍ���
	background_image = LoadGraph("Resource/images/Title.png");
	menu_image = LoadGraph("Resource/images/menu.png");
	cursor_image = LoadGraph("Resource/images/cone.bmp");
	end_image = LoadGraph("Resource/images/End.png");

	//BGM�̓ǂݍ���
	title_sound = LoadSoundMem("Resource/sound/Roll_Crash.mp3");
	button_sound = LoadSoundMem("Resource/sound/button.mp3");
	buttonON_sound = LoadSoundMem("Resource/sound/buttonON.mp3");
	buttonNO_sound = LoadSoundMem("Resource/sound/buttonNO.mp3");
	//BGM�̉��ʐݒ�
	ChangeVolumeSoundMem(255 * 80 / 150, title_sound);
	ChangeVolumeSoundMem(255 * 80 / 100, button_sound);
	ChangeVolumeSoundMem(255 * 80 / 100, buttonON_sound);
	ChangeVolumeSoundMem(255 * 80 / 100, buttonNO_sound);

	end_cun = 0;
	end = false;

	//�G���[�`�F�b�N
	if (background_image == -1)
	{
		throw("Resource/images/Title.bmp������܂���\n");
	}
	if (menu_image == -1)
	{
		throw("Resource/images/menu.bmp������܂���\n");
	}
	if (cursor_image == -1)
	{
		throw("Resource/images/cone.bmp������܂���\n");
	}
}

//�X�V����
eSceneType TitleScene::Update()
{

	if (end == false)
	{


		//bgm������Ă��Ȃ��Ƃ��ɍĐ�
		if (CheckSoundMem(title_sound) != TRUE)
		{
			PlaySoundMem(title_sound, DX_PLAYTYPE_BACK, TRUE);
		}



		//�J�[�\�����ړ�
		if (InputControl::GetButtonDown(XINPUT_BUTTON_DPAD_DOWN, 0))
		{
			PlaySoundMem(button_sound, DX_PLAYTYPE_BACK, TRUE);

			menu_cursor++;
			//1�ԉ��ɓ��B������A�P�ԏ�ɂ���
			if (menu_cursor > 2)
			{
				menu_cursor = 0;
			}
		}

		//�J�[�\����ړ�
		if (InputControl::GetButtonDown(XINPUT_BUTTON_DPAD_UP, 0))
		{
			PlaySoundMem(button_sound, DX_PLAYTYPE_BACK, TRUE);

			menu_cursor--;
			//1�ԏ�ɓ��B������A�P�ԉ��ɂ���
			if (menu_cursor < 0)
			{
				menu_cursor = 2;
			}
		}

		//�J�[�\������i���肵����ʂɑJ�ڂ���j
		if (InputControl::GetButtonDown(XINPUT_BUTTON_B, 0))
		{
			switch (menu_cursor)
			{
			case 0:
				PlaySoundMem(buttonON_sound, DX_PLAYTYPE_BACK, TRUE);
				StopSoundMem(title_sound);
				return eSceneType::E_MAIN;
			case 1:
				PlaySoundMem(buttonON_sound, DX_PLAYTYPE_BACK, TRUE);
				return eSceneType::E_HELP;
			default:
				end = true;
			}
		}

	}
	else
	{

		end_cun++;
		if (end_cun == 130)
		{
			return eSceneType::E_END;
		}
		
	}

	//���݂̃V�[���^�C�v��Ԃ�
	return GetNowScene();
}

//�`�揈��
void TitleScene::Draw() const
{


	//�^�C�g����ʂ̕`��
	DrawExtendGraph(0, 0, 1280, 720, background_image, FALSE);

	//���j���[��ʂ̕`��
	DrawGraph(150, 300, menu_image, TRUE);

	//�J�[�\���摜�̕`��
	DrawRotaGraph(110, 340 + menu_cursor * 90, 0.7, DX_PI / 2.0, cursor_image, TRUE);

	if (end == true)
	{
		DrawGraph(0, 0, end_image, TRUE);

	}
}

//�I������
void TitleScene::Finalize()
{

	DeleteSoundMem(button_sound);
	DeleteSoundMem(buttonON_sound);
	DeleteSoundMem(buttonNO_sound);

	//�ǂݍ��񂾉摜�̍폜
	DeleteGraph(background_image);
	DeleteGraph(menu_image);
	DeleteGraph(cursor_image);
}

//���݂̃V�[�������擾
eSceneType TitleScene::GetNowScene() const
{
	return eSceneType::E_TITLE;
}