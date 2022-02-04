#include"sub.h"

//�E�B���h�E�֐�
LRESULT CALLBACK WindowProc(
	HWND	hWnd,		//�E�B���h�E�n���h��
	UINT	uMsg,		//���b�Z�[�W�i�L�[�������ꂽ�Ȃǁj
	WPARAM	wParam,		//���b�Z�[�W�ɑΉ��������
	LPARAM	lParam		//���b�Z�[�W�ɑΉ��������
)
{
	//�ϐ��錾
	HDC				hdc;	//�f�o�C�X�R���e�L�X�g�i�ȉ�DC�j�����
	PAINTSTRUCT		ps;		//�`��\����

	//static=�ÓI�ϐ��i�������̒��ɕێ������j
	static	HDC		hMemDC;		//������DC

	static HBITMAP	htitle;		//�^�C�g�� 0
	static HBITMAP	hbrack;		//�Ó]�P
	static HBITMAP	hentrance;	//���ւQ
	static HBITMAP	hbook;		//���ւR
	static HBITMAP	hkaidan;	//�K�i�S
	static HBITMAP	hout;		//�E�o�T
	static HBITMAP	hchild;		//�q�������U
	static HBITMAP	hdoor;		//�������h�A�V
	static HBITMAP	hroom;		//�������W
	static HBITMAP	hmirror;	//��l�����X
	static HBITMAP	hmary;		//���}���[�P�O
	static HBITMAP	hhand;		//��P�P
	static HBITMAP	hgameover;	//GAMEOVER�P�Q
	static HBITMAP  hrakugaki;	//�������Q�O

	static HBITMAP	hnormal;	//��l���m�[�}��
	static HBITMAP	haseri;		//��l�������
	static HBITMAP  hmsbox;

	static HFONT	hFont;	//�t�H���g�n���h��

	static int scene = 0;	//�V�[���J�E���^�i��ʐ؂�ւ��p�j
	static int sel = 0;		//�I��ԍ�
	static int nikki = 0;	//����t���O�F���L
	static int r = 0;		//����t���O�F������
	static int cnt = 0;		//�J�E���g

	//���b�Z�[�W�ʂ̏���
	switch (uMsg) {

	case WM_CREATE:			//�E�B���h�E���쐬���ꂽ�Ƃ��i1��̂݁j
		//===��������===//

		//�t�H���g�̍쐬
		hFont = CreateFont(
			20,			//�����̑傫��
			10,			//������
			0,			//�����̊p�x
			0,			//�x�[�X���C���p�x
			FW_REGULAR,	//�����̑����i�����FFW_BOLD�j
			FALSE,		//�΂߂ɂ��邩
			FALSE,		//����
			FALSE,		//�ł�������
			SHIFTJIS_CHARSET,	//�����Z�b�g
			OUT_DEFAULT_PRECIS,	//�o�͐��x
			CLIP_DEFAULT_PRECIS,//�N���b�s���O���x
			DEFAULT_QUALITY,	//�o�͕i��
			VARIABLE_PITCH | FF_ROMAN,	//�σs�b�`�ƃt�H���g�t�@�~��
			"�l�r ����");	//���́iNULL�F���ݎg���Ă��鏑�́j

		//�摜�̓ǂݍ���
		if (ReadBmp(&htitle, "image/wtitle.bmp")		== false)	return 0;	// *�ő���A���Ŏ󂯎��
		if (ReadBmp(&hbrack, "image/wbrackout.bmp")		== false)	return 0;
		if (ReadBmp(&hentrance, "image/wentrance.bmp")	== false)	return 0;
		if (ReadBmp(&hbook, "image/wbook.bmp")			== false)	return 0;
		if (ReadBmp(&hkaidan, "image/wkaidan.bmp")		== false)	return 0;
		if (ReadBmp(&hout, "image/wout.bmp")			== false)	return 0;
		if (ReadBmp(&hchild, "image/wchild.bmp")		== false)	return 0;
		if (ReadBmp(&hdoor, "image/wdoor.bmp")			== false)	return 0;
		if (ReadBmp(&hroom, "image/wroom.bmp")			== false)	return 0;
		if (ReadBmp(&hmirror, "image/wmirror.bmp")		== false)	return 0;
		if (ReadBmp(&hhand, "image/hands.bmp")			== false)	return 0;
		if (ReadBmp(&hgameover, "image/wgameover.bmp")	== false)	return 0;
		if (ReadBmp(&hrakugaki, "image/wrakugaki.bmp")	== false)	return 0;
		if (ReadBmp(&hnormal, "image/�m�[�}��.bmp")		== false)	return 0;
		if (ReadBmp(&haseri, "image/�����.bmp")		== false)	return 0;
		if (ReadBmp(&hmsbox, "image/msbox.bmp")			== false)	return 0;


		//������DC�̍쐬
		hMemDC = CreateCompatibleDC(NULL);	//�݊���

		//�^�C�}�[�̐ݒ�
		SetTimer(hWnd, 1, 100, NULL);

		////BGM�̃I�[�v��
		mciSendString("open �L��.mp3 alias BGM", NULL, 0, hWnd);

		//BGM�̍Đ�
		mciSendString("play BGM notify", NULL, 0, hWnd);


		//PlaySound(NULL,NULL,NULL) ���̒�~

		return 0;

	case WM_TIMER:			//���Ԃ�������
		char sMsg[256];		//�X�e�[�^�X���b�Z�[�W

		//BGM�̏�Ԃ��擾
		mciSendString("status BGM mode", sMsg, 255, hWnd);

		//��~���Ă��邩�ǂ���
		if (strcmp(sMsg, "stopped") == 0)
		{
			//BGM��擪�ɂ��ǂ�
			mciSendString("seek BGM to start", NULL, 0, hWnd);
			mciSendString("play BGM notify", NULL, 0, hWnd);
		}
		

		return 0;

	case WM_KEYDOWN:				//�L�[�������ꂽ�Ƃ�

		//�L�[�ʂ̏���
		switch (wParam)
		{
		case VK_ESCAPE:		//ESC�L�[
			PostQuitMessage(0);
			break;

		case VK_RETURN:		//Enter�L�[

			switch (scene) {
			case 0:		//�^�C�g��
				if (nikki == 1)
				{
					if (sel == 0)scene = 1;
					else if (sel == 1)scene = 30;
				}
				else scene = 1;
				break;

			case 1:	//�Ö�
				cnt++;
				if (cnt == 7) {
					cnt = 0;
					scene = 2;
				}
				break;

			case 2:		//����
				cnt++;
				if (cnt == 5) {

					if (sel == 0) {
						cnt = 0;
						scene = 3;
					}
					else if (sel == 1) {
						cnt = 0;
						scene = 6;
					}
				}
				break;

			case 3:		//����
				cnt++;
				if (cnt == 3) {
					if (sel == 0) {
						nikki = 1;
						cnt = 50;
					}
					else if (sel == 1) {
						cnt = 10;
					}
				}
				
					if (cnt == 52) {
						cnt = 10;
					}
				
				if (cnt >= 10 && cnt <= 20) {
					cnt++;
					if (cnt >= 14) {
						if (sel == 0) {
							scene = 6,cnt=0;
						}
						else if (sel == 1) {
							scene = 4,cnt=0;
						}
					}
				}

				break;

			case 4:		//�K�i
				if (sel == 0) cnt = 0, scene = 7;
				else if (sel == 1)cnt = 0,scene = 5;
				break;

			case 5:		//�O
				cnt++;
				if (cnt == 4)
				{
					cnt = 0;
					scene = 0;
				}
				break;

			case 6:		//�q������
				cnt++;
				if (cnt == 5) {
					if (sel == 0) {
						r = 1;
						cnt = 0;
						scene = 20;
					}
					else if (sel == 1) cnt = 10;
				}
				if (cnt == 10) {
					cnt++;
					if (cnt == 11)cnt = 0, scene = 4;
				}
				break;

			case 7:		//���h�A
				cnt++;
				if (cnt == 4 && r==1) {
					if (sel == 0) {
						cnt = 0;
						scene = 8;
					}
					else if (sel == 1) cnt = 5;
				}
				else if (cnt == 5) {
					cnt = 0;
					scene = 5;
				}
				break;

			case 8:
				cnt++;
				if (cnt == 2) {
					cnt = 0;
					scene = 9;
				}
				break;

			case 9:
				cnt++;
				if (cnt == 5) {
					cnt = 0;
					scene = 10;
				}
				break;

			case 10:
				scene = 11;
				break;

			case 11:
				scene = 13;
				break;

			case 12:
				scene = 0;
				nikki = 0;
				break;

			case 13:
				cnt++;
				if (cnt == 11) {
					cnt = 0;
					scene = 12;
				}
				break;

			case 20:
				r = 1;
				cnt = 0;
				scene = 4;
				break;

			case 30:
				cnt++;
				if (cnt == 11) {
					cnt = 0;
					scene = 0;
				}
			}
			break;

		case VK_UP:			//����
			if (sel > 0)sel--;
			break;

		case VK_DOWN:		//�����
			if (sel < 1) sel++;
			break;
			
		}

		//��ʂ��ĕ`��iWM_PAINT�𓮂����j
		InvalidateRect(hWnd, NULL, FALSE);	//ture=�V�K�@false=�㏑��
		return 0;

		case WM_PAINT:					//�\������Ƃ��i�ŏ��ƃE�B���h�E���X�V���ꂽ�Ƃ��j

			hdc = BeginPaint(hWnd, &ps);//�\���J�n

			//�摜��������DC�ɃR�s�[
			switch (scene)
			{
			case 0:
				BBlt(hdc, hMemDC, htitle);
				break;
			case 1:
				BBlt(hdc, hMemDC, hbrack);
				break;
			case 2:
				BBlt(hdc, hMemDC, hentrance);
				TBlt(hdc, hMemDC, 0, 0, 800, 600, hmsbox);
				TBlt(hdc, hMemDC, 450, 300, 400, 300, hnormal);
				break;
			case 3:
				BBlt(hdc, hMemDC, hbook);
				TBlt(hdc, hMemDC, 0, 0, 800, 600, hmsbox);
				TBlt(hdc, hMemDC, 450, 300, 400, 300, hnormal);
				if(cnt==51)TBlt(hdc, hMemDC, 450, 300, 400, 300, haseri);
				break;
			case 4:
				BBlt(hdc, hMemDC, hkaidan);
				TBlt(hdc, hMemDC, 0, 0, 800, 600, hmsbox);
				TBlt(hdc, hMemDC, 450, 300, 400, 300, haseri);
				break;
			case 5:
				BBlt(hdc, hMemDC, hout);
				TBlt(hdc, hMemDC, 0, 0, 800, 600, hmsbox);
				TBlt(hdc, hMemDC, 450, 300, 400, 300, hnormal);
				break;
			case 6:
				BBlt(hdc, hMemDC, hchild);
				TBlt(hdc, hMemDC, 0, 0, 800, 600, hmsbox);
				TBlt(hdc, hMemDC, 450, 300, 400, 300, hnormal);
				if(cnt>=4)TBlt(hdc, hMemDC, 450, 300, 400, 300, haseri);
				break;
			case 7:
				BBlt(hdc, hMemDC, hdoor);
				TBlt(hdc, hMemDC, 0, 0, 800, 600, hmsbox);
				TBlt(hdc, hMemDC, 450, 300, 400, 300, haseri);
				break;
			case 8:
				BBlt(hdc, hMemDC, hroom);
				TBlt(hdc, hMemDC, 0, 0, 800, 600, hmsbox);
				TBlt(hdc, hMemDC, 450, 300, 400, 300, hnormal);
				break;
			case 9:
				BBlt(hdc, hMemDC, hmirror);
				TBlt(hdc, hMemDC, 0, 0, 800, 600, hmsbox);
				break;
			case 10:
				BBlt(hdc, hMemDC, hmary);
				break;
			case 11:
				BBlt(hdc, hMemDC, hhand);
				break;
			case 12:
				BBlt(hdc, hMemDC, hgameover);
				break;
			case 13:
				BBlt(hdc, hMemDC, hbrack);
				break;
			case 20:
				BBlt(hdc, hMemDC, hrakugaki);
				break;
			case 30:
				BBlt(hdc, hMemDC, hbrack);
				break;
			}


			//�����F�̐ݒ�
			SetTextColor(hdc, RGB(255, 255, 255));
			//�����̔w�i�F�̐ݒ�
			SetBkColor(hdc, RGB(0, 0, 255));
			//�����̔w�i�F�𓧉�
			SetBkMode(hdc, TRANSPARENT);
			//�t�H���g�̕ύX
			SelectObject(hdc, hFont);

			//�����̕\��
			switch (scene)
			{
			case 0://�^�C�g��
				SetTextColor(hdc, RGB(255, 0, 0));

				Text(hdc, 300, 400, "�EEnter�@to�@Start");
				if(nikki==1) {
					SetBkColor(hdc, RGB(255, 255, 255));
					if (sel == 0) SetBkMode(hdc, OPAQUE);
					Text(hdc, 300, 400, "�EEnter�@to�@Start");

					if (sel == 1) SetBkMode(hdc, OPAQUE);
					Text(hdc, 300, 450, "�E�����񍐏�");
					}
				break;

			case 1://���͈Ö�
				SetTextColor(hdc, RGB(255, 0, 0));

				Text(hdc, 10, 20, "���͂���̐X�̒��ɉ��~���������B");
				if (cnt >= 2)Text(hdc, 10, 40, "�̂͂��邨�������̈�Ƃ��Z��ł����B");
				if (cnt >= 3)Text(hdc, 10, 60, "�������A���闒�̓��A��ƑS�������񂾁B");
				if (cnt >= 4)Text(hdc, 10, 80, "�E���ꂽ�炵���B");
				if (cnt >= 5)Text(hdc, 10, 100, "�Ɛl�͍������܂��Ă��Ȃ��B");
				if (cnt >= 6)Text(hdc, 10, 150, "�����āA���̉��~�ɂ͍����c�B");
				break;

			case 2://����
				if (cnt >= 1 && cnt <= 3)Text(hdc, 20, 400, "�u�������\�̗H�쉮�~�c");
				if (cnt >= 2 && cnt <= 3)Text(hdc, 25, 430, "����������΂������ǁv");
				if (cnt == 3)Text(hdc, 20, 480, "�u�ɂ��Ă������ƍL�����~�c�v");

				if (cnt == 4) {
					Text(hdc, 20, 400, "�ǂ��ւ�����");
					if (sel == 0) SetBkMode(hdc, OPAQUE);
					Text(hdc, 40, 440, "�E����");

					if (sel == 1) SetBkMode(hdc, OPAQUE);
					Text(hdc, 40, 460, "�E�q������");
				}
				break;

			case 3:
				if (cnt == 0 || cnt == 1)	Text(hdc, 20, 400, "���̏�ɉ�������");
				if (cnt == 1) {
					Text(hdc, 20, 430, "---���L���������B");
					PlaySound("�͂Ă�.wav", NULL, SND_FILENAME | SND_RING | SND_ASYNC);
				}

				if (cnt == 2) {
					Text(hdc, 20, 400, "���L��ǂ݂܂����H");
					if (sel == 0) SetBkMode(hdc, OPAQUE);
						Text(hdc, 40, 440, "�E�ǂ�");
					if (sel == 1) SetBkMode(hdc, OPAQUE);
						Text(hdc, 40, 460, "�E�ǂ܂Ȃ�");
					
				}

				if (cnt == 51) {
					Text(hdc, 20, 400, "�u����ȁc�܂��Ɛl�����������������n�ˁv");
				}

				if (cnt == 11) {
					Text(hdc, 20, 400, "�u���̕����͂����������Ȃ��B�v");
				}

				if (cnt == 13) {
					Text(hdc, 20, 400, "�ǂ��ւ����H");
					if (sel == 0) SetBkMode(hdc, OPAQUE);
					Text(hdc, 40, 440, "�E�q������");

					if (sel == 1) SetBkMode(hdc, OPAQUE);
					Text(hdc, 40, 460, "�E�K�i");
				}

				break;

			case 4:
				Text(hdc,20, 400, "�ǂ����悤��");
				if (sel == 0) SetBkMode(hdc, OPAQUE);
				Text(hdc, 40, 440, "�E�RF�ւ�����");
				if (sel == 1) SetBkMode(hdc, OPAQUE);
				Text(hdc, 40, 460, "�E�O�֏o��");
				break;

			case 5:
				if (cnt >= 1)Text(hdc, 20, 400, "�u�H�쉮�~�ƌ����Ă邾�������āA�s�C���ł͂�������ˁv");
				if (cnt >= 2)Text(hdc, 20, 430, "�u�����N���Ȃ��Ă悩�����v");
				if (cnt == 3)Text(hdc, 20, 480, "�u���ĂƁA�A���Ē����񍐂��Ȃ�����ˁc�v");
				break;

			case 6:
				if (cnt == 1)Text(hdc, 20, 400, "�u�q�������œ����̂͂��̕����������v");
				if (cnt == 2 || cnt == 3)Text(hdc, 20, 400, "�J�T�b");
				if (cnt == 3) {
					Text(hdc, 20, 430, "�ۂ܂������𓥂񂸂����悤���B");
					PlaySound("�͂Ă�.wav", NULL, SND_FILENAME | SND_RING | SND_ASYNC);
				}
				if (cnt == 4) {
					Text(hdc, 20, 400, "�E���܂����H");
					if (sel == 0) SetBkMode(hdc, OPAQUE);
					Text(hdc, 40, 440, "�E�E��");

					if (sel == 1) SetBkMode(hdc, OPAQUE);
					Text(hdc, 40, 460, "�E�E��Ȃ�");
				}

				if (cnt == 10) {
					Text(hdc, 20, 400, "�u���̕����͂����������Ȃ��B�v");
				}
				break;

			case 7:
				if (cnt == 1)Text(hdc, 20, 400, "�h�A�v���[�g�ɂ̓}���[�Ə�����Ă���B");
				if (cnt == 2)Text(hdc, 20, 400, "�u�����́A����l�̕����c�H�v");

				if (cnt == 3 && r==1 ) {
					Text(hdc, 20, 400, "�����ɓ���܂����H");
					if (sel == 0) SetBkMode(hdc, OPAQUE);
					Text(hdc, 40, 440, "�E����");

					if (sel == 1) SetBkMode(hdc, OPAQUE);
					Text(hdc, 40, 460, "�E����Ȃ�");
				}
				else if (cnt == 3) {
					Text(hdc, 20, 400, "�������Ă���悤���B");
					if(cnt == 4)Text(hdc, 20, 430, "�u�c�A�邵���Ȃ��݂����ˁv");
				}
				break;

			case 8:
				if (cnt == 1)Text(hdc, 20, 400, "���̂��镁�ʂ̕����̂悤���B");
				break;

			case 9:
				if (cnt == 1 || cnt == 2)Text(hdc, 20, 400, "�u���G��̃}���[�́A���̑O�Ŗ��O���ĂԂƌĂ񂾐l��A�ꋎ��B�v");
				if (cnt == 2)Text(hdc, 20, 430, "�u�܂����A�ˁB�v");

				if (cnt == 3 || cnt == 4)Text(hdc, 20, 400, "�u�cBloody Mary Bloody Mary Are you here?�v");
				if (cnt == 4)Text(hdc, 20, 430, "�u�Ƒ����E�����̂͂��Ȃ��ˁH�v");
				break;

			case 13:
				SetTextColor(hdc, RGB(255, 0, 0));

				Text(hdc, 10, 20, "�u�[�[�[�Ȃ񂾁����̂���������f���΂��v");
				if (cnt >= 2)Text(hdc, 10, 40, "�u�����ł��ˁA������T�Ԃ����M�s�ʂȂ�Ă��������Ȃ��ł����v");
				if (cnt >= 3)Text(hdc, 10, 60, "�u�|�|�|�T�����L�҂����ɂȂ��ē������񂶂�Ȃ��̂��v");
				if (cnt >= 4)Text(hdc, 10, 80, "�u����ł��A�A���Ă��Ă��Ȃ��݂����ł���v");
				if (cnt >= 5)Text(hdc, 10, 100, "�u���[�A��T�ԑO�ƌ�������A�����͗H�쉮�~�̒������������H");
				if (cnt >= 6)Text(hdc, 10, 120, "�u�����ł��ˁA���[�Z���g��Ƃ̉��~�ł��v");
				if (cnt >= 7)Text(hdc, 10, 140, "�u�|�|�|�H��ɂ�����ł������񂶂�Ȃ����H�v");
				if (cnt >= 8)Text(hdc, 10, 160, "�u��k�����ł���c���������Ȃ����ł��v");
				if (cnt >= 9)Text(hdc, 10, 180, "�u�[�[�[�\���͔ے肵����Ȃ��A�������ɑ{���̏������v");
				if (cnt >= 10)Text(hdc, 10, 200, "�u�c�͂��v");
				break;

			case 30:
				SetTextColor(hdc, RGB(255, 255, 255));

				Text(hdc, 10, 20, "���G��̃}���[�̉��~�@�����񍐏�");
				if (cnt >= 2)Text(hdc, 10, 60, "�ƎS�E�����̔Ɛl�͏���l�u�}���[�E���[�Z���g�v�ł������B");
				if (cnt >= 3)Text(hdc, 10, 80, "�ޏ��͔�Q�ϑz�⋕���Ȃ��������A");
				if (cnt >= 4)Text(hdc, 10, 100, "�Ƒ��ɂ����߂��Ă���Ɗ��Ⴂ���Ă����B");
				if (cnt >= 5)Text(hdc, 10, 140, "���̃X�g���X���琸�_�a�͈������Ă�������ł������B");
				if (cnt >= 6)Text(hdc, 10, 160, "�܂��A���L�̍Ō�̃y�[�W�ɂ͐f�f�����}�܂�Ă����B");
				if (cnt >= 7)Text(hdc, 10, 200, "�[�[�[�}���[�E���[�Z���g");
				if (cnt >= 8)Text(hdc, 10, 220, "�����ȁA��Q�ϑz�̌������X��������");
				if (cnt >= 9)Text(hdc, 10, 240, "�ɒ[�ɐ����������A�܂��{�l����̌X�����݂���B");
				if (cnt >= 10)Text(hdc, 10, 280, "���̊��Ⴂ�̕��Q���������A�S�E�����̐^���ł���B");
			}

			EndPaint(hWnd, &ps);			//�\���I��
			return 0;

		
		case WM_DESTROY:		//�E�B���h�E������ꂽ��
			//===�I������===//

			//BGM�̒�~
			mciSendString("close BGM", NULL, 0, hWnd);

			PostQuitMessage(0);	//�A�v���P�[�V�����̏I��
			return 0;			//���C���ɖ߂�
		}

		//���C���ɕԂ����
		return DefWindowProc(hWnd, uMsg, wParam, lParam);
	}



//���C��
int WINAPI WinMain(
	HINSTANCE hInstance,	//�C���X�^���X�ԍ����E�B���h�E�̔ԍ�
	HINSTANCE hPrevInstance,
	PSTR	  lpCmdLine,
	int       nCmdShow)
{
	WNDCLASS wc;			//�E�B���h�E�N���X�\����
	HWND hWnd;				//�E�C���h�E�n���h��
	MSG msg;				//�E�B���h�E���b�Z�[�W

	//�E�B���h�E���̐ݒ�

	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = WindowProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInstance;							//�C���X�^���X�ԍ�
	wc.hIcon = NULL;									//�A�C�R���i�f�t�H���g�j
	wc.hCursor = NULL;									//�J�[�\���i���}�E�X�̖��݂����Ȃ�j
	wc.hbrBackground = (HBRUSH)COLOR_BACKGROUND + 1;	//�w�i�F
	wc.lpszMenuName = NULL;								//���j���[
	wc.lpszClassName = APPLY_NAME;							//�A�v���P�[�V���������E�B���h�E�Ɠ������O

	//�E�B���h�E�N���X��Windows�ɓo�^

	if (RegisterClass(&wc) == false)
	{
		//���s���̃G���[���b�Z�\�W
		MessageBox(NULL, "�E�C���h�E�N���X�̓o�^���s", "�G���[���b�Z�[�W", MB_OK);
		return 0;
	}

	//�E�C���h�E�̍쐬
	hWnd = CreateWindow(
		APPLY_NAME,				//�Q�[���^�C�g�� 
		TITLE_NAME,	//�E�C���h�E�^�C�g��
		WS_OVERLAPPEDWINDOW,	//���ʂ̃E�C���h�E�i��ނ�����j
		100, 100,				//�\������ʒu��XY���W	
		WND_W,WND_H,				//�E�C���h�E�̕��ƍ���
		NULL,					//�e�E�C���h�E�̃n���h��
		NULL,					//���j���[�̐ݒ�
		hInstance,				//�C���X�^���X�ԍ�
		NULL);					//�g�p���Ȃ�

	if (hWnd == NULL) {

		//�G���[���b�Z�[�W
		MessageBox(NULL, "�E�C���h�E�N���X�̍쐬���s", "�G���[���b�Z�[�W", MB_OK);
		return 0;

	}

	//�E�C���h�E�̕\��
	ShowWindow(hWnd, SW_SHOW);

	//�E�B���h�E�֐����Ăяo�����߂̃��b�Z�[�W���[�v�i�E�B���h�E��������܂Łj
	while (GetMessage(&msg,NULL,0,0)>0) {
		
		//�E�B���h�E�֐��Ƀ��b�Z�[�W�𑗂�
		DispatchMessage(&msg);
	}

	return 0;
}