#include"sub.h"

//ウィンドウ関数
LRESULT CALLBACK WindowProc(
	HWND	hWnd,		//ウィンドウハンドル
	UINT	uMsg,		//メッセージ（キーが押されたなど）
	WPARAM	wParam,		//メッセージに対応した情報
	LPARAM	lParam		//メッセージに対応した情報
)
{
	//変数宣言
	HDC				hdc;	//デバイスコンテキスト（以下DC）＝画面
	PAINTSTRUCT		ps;		//描画構造体

	//static=静的変数（メモリの中に保持される）
	static	HDC		hMemDC;		//メモリDC

	static HBITMAP	htitle;		//タイトル 0
	static HBITMAP	hbrack;		//暗転１
	static HBITMAP	hentrance;	//玄関２
	static HBITMAP	hbook;		//書斎３
	static HBITMAP	hkaidan;	//階段４
	static HBITMAP	hout;		//脱出５
	static HBITMAP	hchild;		//子供部屋６
	static HBITMAP	hdoor;		//鏡部屋ドア７
	static HBITMAP	hroom;		//鏡部屋８
	static HBITMAP	hmirror;	//主人公鏡９
	static HBITMAP	hmary;		//鏡マリー１０
	static HBITMAP	hhand;		//手１１
	static HBITMAP	hgameover;	//GAMEOVER１２
	static HBITMAP  hrakugaki;	//落書き２０

	static HBITMAP	hnormal;	//主人公ノーマル
	static HBITMAP	haseri;		//主人公困り顔
	static HBITMAP  hmsbox;

	static HFONT	hFont;	//フォントハンドル

	static int scene = 0;	//シーンカウンタ（画面切り替え用）
	static int sel = 0;		//選択番号
	static int nikki = 0;	//分岐フラグ：日記
	static int r = 0;		//分岐フラグ：落書き
	static int cnt = 0;		//カウント

	//メッセージ別の処理
	switch (uMsg) {

	case WM_CREATE:			//ウィンドウが作成されたとき（1回のみ）
		//===初期処理===//

		//フォントの作成
		hFont = CreateFont(
			20,			//文字の大きさ
			10,			//文字幅
			0,			//文字の角度
			0,			//ベースライン角度
			FW_REGULAR,	//文字の太さ（太字：FW_BOLD）
			FALSE,		//斜めにするか
			FALSE,		//下線
			FALSE,		//打ち消し線
			SHIFTJIS_CHARSET,	//文字セット
			OUT_DEFAULT_PRECIS,	//出力精度
			CLIP_DEFAULT_PRECIS,//クリッピング精度
			DEFAULT_QUALITY,	//出力品質
			VARIABLE_PITCH | FF_ROMAN,	//可変ピッチとフォントファミリ
			"ＭＳ 明朝");	//書体（NULL：現在使われている書体）

		//画像の読み込み
		if (ReadBmp(&htitle, "image/wtitle.bmp")		== false)	return 0;	// *で送る、＆で受け取る
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
		if (ReadBmp(&hnormal, "image/ノーマル.bmp")		== false)	return 0;
		if (ReadBmp(&haseri, "image/困り顔.bmp")		== false)	return 0;
		if (ReadBmp(&hmsbox, "image/msbox.bmp")			== false)	return 0;


		//メモリDCの作成
		hMemDC = CreateCompatibleDC(NULL);	//互換性

		//タイマーの設定
		SetTimer(hWnd, 1, 100, NULL);

		////BGMのオープン
		mciSendString("open 記憶.mp3 alias BGM", NULL, 0, hWnd);

		//BGMの再生
		mciSendString("play BGM notify", NULL, 0, hWnd);


		//PlaySound(NULL,NULL,NULL) 音の停止

		return 0;

	case WM_TIMER:			//時間が来た時
		char sMsg[256];		//ステータスメッセージ

		//BGMの状態を取得
		mciSendString("status BGM mode", sMsg, 255, hWnd);

		//停止しているかどうか
		if (strcmp(sMsg, "stopped") == 0)
		{
			//BGMを先頭にもどす
			mciSendString("seek BGM to start", NULL, 0, hWnd);
			mciSendString("play BGM notify", NULL, 0, hWnd);
		}
		

		return 0;

	case WM_KEYDOWN:				//キーが押されたとき

		//キー別の処理
		switch (wParam)
		{
		case VK_ESCAPE:		//ESCキー
			PostQuitMessage(0);
			break;

		case VK_RETURN:		//Enterキー

			switch (scene) {
			case 0:		//タイトル
				if (nikki == 1)
				{
					if (sel == 0)scene = 1;
					else if (sel == 1)scene = 30;
				}
				else scene = 1;
				break;

			case 1:	//暗幕
				cnt++;
				if (cnt == 7) {
					cnt = 0;
					scene = 2;
				}
				break;

			case 2:		//玄関
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

			case 3:		//書斎
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

			case 4:		//階段
				if (sel == 0) cnt = 0, scene = 7;
				else if (sel == 1)cnt = 0,scene = 5;
				break;

			case 5:		//外
				cnt++;
				if (cnt == 4)
				{
					cnt = 0;
					scene = 0;
				}
				break;

			case 6:		//子供部屋
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

			case 7:		//鏡ドア
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

		case VK_UP:			//上矢印
			if (sel > 0)sel--;
			break;

		case VK_DOWN:		//下矢印
			if (sel < 1) sel++;
			break;
			
		}

		//画面を再描画（WM_PAINTを動かす）
		InvalidateRect(hWnd, NULL, FALSE);	//ture=新規　false=上書き
		return 0;

		case WM_PAINT:					//表示するとき（最初とウィンドウが更新されたとき）

			hdc = BeginPaint(hWnd, &ps);//表示開始

			//画像をメモリDCにコピー
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


			//文字色の設定
			SetTextColor(hdc, RGB(255, 255, 255));
			//文字の背景色の設定
			SetBkColor(hdc, RGB(0, 0, 255));
			//文字の背景色を透過
			SetBkMode(hdc, TRANSPARENT);
			//フォントの変更
			SelectObject(hdc, hFont);

			//文字の表示
			switch (scene)
			{
			case 0://タイトル
				SetTextColor(hdc, RGB(255, 0, 0));

				Text(hdc, 300, 400, "・Enter　to　Start");
				if(nikki==1) {
					SetBkColor(hdc, RGB(255, 255, 255));
					if (sel == 0) SetBkMode(hdc, OPAQUE);
					Text(hdc, 300, 400, "・Enter　to　Start");

					if (sel == 1) SetBkMode(hdc, OPAQUE);
					Text(hdc, 300, 450, "・調査報告書");
					}
				break;

			case 1://序章暗幕
				SetTextColor(hdc, RGB(255, 0, 0));

				Text(hdc, 10, 20, "町はずれの森の中に屋敷があった。");
				if (cnt >= 2)Text(hdc, 10, 40, "昔はあるお金持ちの一家が住んでいた。");
				if (cnt >= 3)Text(hdc, 10, 60, "しかし、ある嵐の日、一家全員が死んだ。");
				if (cnt >= 4)Text(hdc, 10, 80, "殺されたらしい。");
				if (cnt >= 5)Text(hdc, 10, 100, "犯人は今もつかまっていない。");
				if (cnt >= 6)Text(hdc, 10, 150, "そして、その屋敷には今も…。");
				break;

			case 2://玄関
				if (cnt >= 1 && cnt <= 3)Text(hdc, 20, 400, "「ここが噂の幽霊屋敷…");
				if (cnt >= 2 && cnt <= 3)Text(hdc, 25, 430, "何か見つかればいいけど」");
				if (cnt == 3)Text(hdc, 20, 480, "「にしても随分と広い屋敷…」");

				if (cnt == 4) {
					Text(hdc, 20, 400, "どこへいこう");
					if (sel == 0) SetBkMode(hdc, OPAQUE);
					Text(hdc, 40, 440, "・書斎");

					if (sel == 1) SetBkMode(hdc, OPAQUE);
					Text(hdc, 40, 460, "・子供部屋");
				}
				break;

			case 3:
				if (cnt == 0 || cnt == 1)	Text(hdc, 20, 400, "机の上に何かある");
				if (cnt == 1) {
					Text(hdc, 20, 430, "---日記を見つけた。");
					PlaySound("はてな.wav", NULL, SND_FILENAME | SND_RING | SND_ASYNC);
				}

				if (cnt == 2) {
					Text(hdc, 20, 400, "日記を読みますか？");
					if (sel == 0) SetBkMode(hdc, OPAQUE);
						Text(hdc, 40, 440, "・読む");
					if (sel == 1) SetBkMode(hdc, OPAQUE);
						Text(hdc, 40, 460, "・読まない");
					
				}

				if (cnt == 51) {
					Text(hdc, 20, 400, "「そんな…まぁ犯人が分かっただけ収穫ね」");
				}

				if (cnt == 11) {
					Text(hdc, 20, 400, "「この部屋はもういいかなぁ。」");
				}

				if (cnt == 13) {
					Text(hdc, 20, 400, "どこへいく？");
					if (sel == 0) SetBkMode(hdc, OPAQUE);
					Text(hdc, 40, 440, "・子供部屋");

					if (sel == 1) SetBkMode(hdc, OPAQUE);
					Text(hdc, 40, 460, "・階段");
				}

				break;

			case 4:
				Text(hdc,20, 400, "どうしようか");
				if (sel == 0) SetBkMode(hdc, OPAQUE);
				Text(hdc, 40, 440, "・３Fへあがる");
				if (sel == 1) SetBkMode(hdc, OPAQUE);
				Text(hdc, 40, 460, "・外へ出る");
				break;

			case 5:
				if (cnt >= 1)Text(hdc, 20, 400, "「幽霊屋敷と言われてるだけあって、不気味ではあったわね」");
				if (cnt >= 2)Text(hdc, 20, 430, "「何も起きなくてよかった」");
				if (cnt == 3)Text(hdc, 20, 480, "「さてと、帰って調査報告しなくちゃね…」");
				break;

			case 6:
				if (cnt == 1)Text(hdc, 20, 400, "「子供部屋で入れるのはこの部屋だけか」");
				if (cnt == 2 || cnt == 3)Text(hdc, 20, 400, "カサッ");
				if (cnt == 3) {
					Text(hdc, 20, 430, "丸まった紙を踏んずけたようだ。");
					PlaySound("はてな.wav", NULL, SND_FILENAME | SND_RING | SND_ASYNC);
				}
				if (cnt == 4) {
					Text(hdc, 20, 400, "拾いますか？");
					if (sel == 0) SetBkMode(hdc, OPAQUE);
					Text(hdc, 40, 440, "・拾う");

					if (sel == 1) SetBkMode(hdc, OPAQUE);
					Text(hdc, 40, 460, "・拾わない");
				}

				if (cnt == 10) {
					Text(hdc, 20, 400, "「この部屋はもういいかなぁ。」");
				}
				break;

			case 7:
				if (cnt == 1)Text(hdc, 20, 400, "ドアプレートにはマリーと書かれている。");
				if (cnt == 2)Text(hdc, 20, 400, "「ここは、女主人の部屋…？」");

				if (cnt == 3 && r==1 ) {
					Text(hdc, 20, 400, "部屋に入りますか？");
					if (sel == 0) SetBkMode(hdc, OPAQUE);
					Text(hdc, 40, 440, "・入る");

					if (sel == 1) SetBkMode(hdc, OPAQUE);
					Text(hdc, 40, 460, "・入らない");
				}
				else if (cnt == 3) {
					Text(hdc, 20, 400, "鍵が壊れているようだ。");
					if(cnt == 4)Text(hdc, 20, 430, "「…帰るしかないみたいね」");
				}
				break;

			case 8:
				if (cnt == 1)Text(hdc, 20, 400, "鏡のある普通の部屋のようだ。");
				break;

			case 9:
				if (cnt == 1 || cnt == 2)Text(hdc, 20, 400, "「血濡れのマリーは、鏡の前で名前を呼ぶと呼んだ人を連れ去る。」");
				if (cnt == 2)Text(hdc, 20, 430, "「まさか、ね。」");

				if (cnt == 3 || cnt == 4)Text(hdc, 20, 400, "「…Bloody Mary Bloody Mary Are you here?」");
				if (cnt == 4)Text(hdc, 20, 430, "「家族を殺したのはあなたね？」");
				break;

			case 13:
				SetTextColor(hdc, RGB(255, 0, 0));

				Text(hdc, 10, 20, "「ーーーなんだ○○のやつ今日も無断欠勤か」");
				if (cnt >= 2)Text(hdc, 10, 40, "「そうですね、もう一週間も音信不通なんておかしくないですか」");
				if (cnt >= 3)Text(hdc, 10, 60, "「－－－週刊誌記者が嫌になって逃げたんじゃないのか」");
				if (cnt >= 4)Text(hdc, 10, 80, "「いやでも、帰ってきてもないみたいですよ」");
				if (cnt >= 5)Text(hdc, 10, 100, "「あー、一週間前と言ったら、あいつは幽霊屋敷の調査だったか？");
				if (cnt >= 6)Text(hdc, 10, 120, "「そうですね、ルーセント一家の屋敷です」");
				if (cnt >= 7)Text(hdc, 10, 140, "「－－－幽霊にさらわれでもしたんじゃないか？」");
				if (cnt >= 8)Text(hdc, 10, 160, "「冗談きついですよ…もしそうなら大問題です」");
				if (cnt >= 9)Text(hdc, 10, 180, "「ーーー可能性は否定しきれない、今日中に捜索の準備だ」");
				if (cnt >= 10)Text(hdc, 10, 200, "「…はい」");
				break;

			case 30:
				SetTextColor(hdc, RGB(255, 255, 255));

				Text(hdc, 10, 20, "血濡れのマリーの屋敷　調査報告書");
				if (cnt >= 2)Text(hdc, 10, 60, "家惨殺事件の犯人は女主人「マリー・ルーセント」であった。");
				if (cnt >= 3)Text(hdc, 10, 80, "彼女は被害妄想や虚言癖が激しく、");
				if (cnt >= 4)Text(hdc, 10, 100, "家族にいじめられていると勘違いしていた。");
				if (cnt >= 5)Text(hdc, 10, 140, "そのストレスから精神病は悪化していく一方であった。");
				if (cnt >= 6)Text(hdc, 10, 160, "また、日記の最後のページには診断書が挿まれていた。");
				if (cnt >= 7)Text(hdc, 10, 200, "ーーーマリー・ルーセント");
				if (cnt >= 8)Text(hdc, 10, 220, "虚言癖、被害妄想の激しい傾向があり");
				if (cnt >= 9)Text(hdc, 10, 240, "極端に声が小さく、また本人も難聴の傾向がみられる。");
				if (cnt >= 10)Text(hdc, 10, 280, "その勘違いの復讐劇こそが、惨殺事件の真相である。");
			}

			EndPaint(hWnd, &ps);			//表示終了
			return 0;

		
		case WM_DESTROY:		//ウィンドウが閉じられた時
			//===終了処理===//

			//BGMの停止
			mciSendString("close BGM", NULL, 0, hWnd);

			PostQuitMessage(0);	//アプリケーションの終了
			return 0;			//メインに戻る
		}

		//メインに返す情報
		return DefWindowProc(hWnd, uMsg, wParam, lParam);
	}



//メイン
int WINAPI WinMain(
	HINSTANCE hInstance,	//インスタンス番号＝ウィンドウの番号
	HINSTANCE hPrevInstance,
	PSTR	  lpCmdLine,
	int       nCmdShow)
{
	WNDCLASS wc;			//ウィンドウクラス構造体
	HWND hWnd;				//ウインドウハンドル
	MSG msg;				//ウィンドウメッセージ

	//ウィンドウ情報の設定

	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = WindowProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInstance;							//インスタンス番号
	wc.hIcon = NULL;									//アイコン（デフォルト）
	wc.hCursor = NULL;									//カーソル（＝マウスの矢印みたいなやつ）
	wc.hbrBackground = (HBRUSH)COLOR_BACKGROUND + 1;	//背景色
	wc.lpszMenuName = NULL;								//メニュー
	wc.lpszClassName = APPLY_NAME;							//アプリケーション名＝ウィンドウと同じ名前

	//ウィンドウクラスをWindowsに登録

	if (RegisterClass(&wc) == false)
	{
		//失敗時のエラーメッセ―ジ
		MessageBox(NULL, "ウインドウクラスの登録失敗", "エラーメッセージ", MB_OK);
		return 0;
	}

	//ウインドウの作成
	hWnd = CreateWindow(
		APPLY_NAME,				//ゲームタイトル 
		TITLE_NAME,	//ウインドウタイトル
		WS_OVERLAPPEDWINDOW,	//普通のウインドウ（種類がある）
		100, 100,				//表示する位置のXY座標	
		WND_W,WND_H,				//ウインドウの幅と高さ
		NULL,					//親ウインドウのハンドル
		NULL,					//メニューの設定
		hInstance,				//インスタンス番号
		NULL);					//使用しない

	if (hWnd == NULL) {

		//エラーメッセージ
		MessageBox(NULL, "ウインドウクラスの作成失敗", "エラーメッセージ", MB_OK);
		return 0;

	}

	//ウインドウの表示
	ShowWindow(hWnd, SW_SHOW);

	//ウィンドウ関数を呼び出すためのメッセージループ（ウィンドウが閉じられるまで）
	while (GetMessage(&msg,NULL,0,0)>0) {
		
		//ウィンドウ関数にメッセージを送る
		DispatchMessage(&msg);
	}

	return 0;
}