#pragma once
#include <Windows.h>
#include<mmsystem.h>

//���C�u�����錾
#pragma comment(lib,"winmm.lib")//���i���y�⓮��j�֌W�̃��C�u����
#pragma comment(lib,"msimg32.lib")

//�萔�錾
#define APPLY_NAME "NOVEL"
#define TITLE_NAME "�}���[�̉��~"
#define WND_W 800
#define WND_H 600

//�����֐��̃v���g�^�C�v�錾����//
//�e�L�X�g�̕\���i�֐��j
void Text(HDC hdc, int x, int y, const char* text);

//�摜�̓ǂݍ���
bool ReadBmp(HBITMAP* hBmp, LPCTSTR fileName);

//�摜�\��
void BBlt(HDC hdc, HDC hMemDC, HBITMAP hBmp);

void TBlt(HDC hdc, HDC hMemDC, int x, int y, int w, int h, HBITMAP hBmp);
