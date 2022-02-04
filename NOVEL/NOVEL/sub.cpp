#include"sub.h"

//テキストの表示（関数）
void Text(HDC hdc, int x, int y, const char* text)
{
	TextOut(hdc, x, y, text, lstrlen(text));
	SetBkMode(hdc, TRANSPARENT);
}

//画像の読み込み
bool ReadBmp(HBITMAP* hBmp, LPCTSTR fileName) 
{
	*hBmp = (HBITMAP)LoadImage(
		NULL,				//インスタンス番号（省略）
		fileName,		//画像ファイル名
		IMAGE_BITMAP,		//ビットマップを指定
		0, 0,				//画像内の読み込み開始座標
		LR_LOADFROMFILE);	//フィルから読み込む

	if (*hBmp == NULL) {
		MessageBox(NULL, "画像ファイルの読み込み失敗", fileName, MB_OK);
		return false;
	}
	return true;			//読み込み成功
}

//画像表示
void BBlt(HDC hdc,HDC hMemDC,HBITMAP hBmp)
{
	//画像をメモリDCへコピー
	SelectObject(hMemDC, hBmp);

	//画像の表示
	BitBlt(
		hdc,		//画面
		0, 0,		//表示先の座標
		WND_W, WND_H,	//表示の幅高
		hMemDC,		//どこから引用するのか
		0, 0,		//画像のXY座標
		SRCCOPY);	//メモリDCから画面にコピー
}

void TBlt(HDC hdc, HDC hMemDC, int x,int y,int w,int h,HBITMAP hBmp)
{
	SelectObject(hMemDC, hBmp);
	TransparentBlt(hdc,		//画面
		x, y,				//表示座標
		w, h,			//表示の幅高
		hMemDC,
		0, 0,				//画像の座標
		800, 600,				//画像の幅高
		RGB(0, 255, 0));
}



/*

//BGMのオープン
void BGM_Open(HWND hWnd, LPCTSTR hBgm, LPCTSTR fileName)
{
	char str[128];

	//ファイル名からオープンの文字列を作成
	strcpy_s(str, "open ");
	strcat_s(str, fileName);
	strcat_s(str, "alias ");
	strcat_s(str, hBgm);

	mciSendString(str, NULL, 0, hWnd);
}

//BGMの再生
void BGM_Play(HWND hWnd, LPCTSTR hBgm)
{
	char str[128];
	strcpy_s(str, "play ");
	strcat_s(str, hBgm);
	strcat_s(str, "notify ");

	mciSendString("str", NULL, 0, hWnd);
}

//BGMの停止
void BGM_Close(HWND hWnd, LPCTSTR hBgm)
{
	char str[128];

	strcpy_s(str, "close ");
	strcat_s(str, hBgm);

	mciSendString(str, NULL, 0, hWnd);
}

*/