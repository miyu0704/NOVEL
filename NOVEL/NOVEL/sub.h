#pragma once
#include <Windows.h>
#include<mmsystem.h>

//ライブラリ宣言
#pragma comment(lib,"winmm.lib")//音（音楽や動画）関係のライブラリ
#pragma comment(lib,"msimg32.lib")

//定数宣言
#define APPLY_NAME "NOVEL"
#define TITLE_NAME "マリーの屋敷"
#define WND_W 800
#define WND_H 600

//＝＝関数のプロトタイプ宣言＝＝//
//テキストの表示（関数）
void Text(HDC hdc, int x, int y, const char* text);

//画像の読み込み
bool ReadBmp(HBITMAP* hBmp, LPCTSTR fileName);

//画像表示
void BBlt(HDC hdc, HDC hMemDC, HBITMAP hBmp);

void TBlt(HDC hdc, HDC hMemDC, int x, int y, int w, int h, HBITMAP hBmp);
