#include"sub.h"

//�e�L�X�g�̕\���i�֐��j
void Text(HDC hdc, int x, int y, const char* text)
{
	TextOut(hdc, x, y, text, lstrlen(text));
	SetBkMode(hdc, TRANSPARENT);
}

//�摜�̓ǂݍ���
bool ReadBmp(HBITMAP* hBmp, LPCTSTR fileName) 
{
	*hBmp = (HBITMAP)LoadImage(
		NULL,				//�C���X�^���X�ԍ��i�ȗ��j
		fileName,		//�摜�t�@�C����
		IMAGE_BITMAP,		//�r�b�g�}�b�v���w��
		0, 0,				//�摜���̓ǂݍ��݊J�n���W
		LR_LOADFROMFILE);	//�t�B������ǂݍ���

	if (*hBmp == NULL) {
		MessageBox(NULL, "�摜�t�@�C���̓ǂݍ��ݎ��s", fileName, MB_OK);
		return false;
	}
	return true;			//�ǂݍ��ݐ���
}

//�摜�\��
void BBlt(HDC hdc,HDC hMemDC,HBITMAP hBmp)
{
	//�摜��������DC�փR�s�[
	SelectObject(hMemDC, hBmp);

	//�摜�̕\��
	BitBlt(
		hdc,		//���
		0, 0,		//�\����̍��W
		WND_W, WND_H,	//�\���̕���
		hMemDC,		//�ǂ�������p����̂�
		0, 0,		//�摜��XY���W
		SRCCOPY);	//������DC�����ʂɃR�s�[
}

void TBlt(HDC hdc, HDC hMemDC, int x,int y,int w,int h,HBITMAP hBmp)
{
	SelectObject(hMemDC, hBmp);
	TransparentBlt(hdc,		//���
		x, y,				//�\�����W
		w, h,			//�\���̕���
		hMemDC,
		0, 0,				//�摜�̍��W
		800, 600,				//�摜�̕���
		RGB(0, 255, 0));
}



/*

//BGM�̃I�[�v��
void BGM_Open(HWND hWnd, LPCTSTR hBgm, LPCTSTR fileName)
{
	char str[128];

	//�t�@�C��������I�[�v���̕�������쐬
	strcpy_s(str, "open ");
	strcat_s(str, fileName);
	strcat_s(str, "alias ");
	strcat_s(str, hBgm);

	mciSendString(str, NULL, 0, hWnd);
}

//BGM�̍Đ�
void BGM_Play(HWND hWnd, LPCTSTR hBgm)
{
	char str[128];
	strcpy_s(str, "play ");
	strcat_s(str, hBgm);
	strcat_s(str, "notify ");

	mciSendString("str", NULL, 0, hWnd);
}

//BGM�̒�~
void BGM_Close(HWND hWnd, LPCTSTR hBgm)
{
	char str[128];

	strcpy_s(str, "close ");
	strcat_s(str, hBgm);

	mciSendString(str, NULL, 0, hWnd);
}

*/