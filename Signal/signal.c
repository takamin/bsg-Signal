/*!
	\file signal.c
	\brief 模擬信号ライブラリ メイン処理
	\author BeNest SDGr K.Urakari
	\date 2015/11/14
	\details
	### 概要

	このファイルはSignalLibの使用方法を説明するためのサンプルファイルです。

	ライブラリからコールされる関数を一通りサンプル実装しています。
	この実装を修正する(コールバック関数の中身を書き換える)ことでアプリケーションを実装します。	
	
	ランプの描画やボタンの入力はライブラリ側で処理していますので、コールバック関数にはアプリケーション固有の処理のみを記述します。
	
	### サンプルの動作

	サンプル動作として次の様に実装されています。あくまでライブラリの確認用サンプル実装ですので本来の動作ではありません。

	- 車用信号
	　500msec周期で「消灯->青点灯->黄色点灯->赤点灯」を繰り返します。
	- 歩行者用信号
	　ボタンが押される毎に「消灯->青点灯->赤点灯」を繰り返します。
	- "おまちください"および"ボタンをおしてください"ランプ
	　ボタンが押されると2秒間、"おまちください"を点灯し、その後"ボタンをおしてください"を点灯します。
	
	### ライブラリの使い方

	#### コールバック
	ライブラリからは4つの関数がコールされます。これらの関数が存在しなければビルドエラーになります。
	関数を削除したり宣言を変えないでください。
	\sa OnInitialize() OnStart() OnTimer() OnButton()

	#### 模擬ハードウェアの制御
	各ランプはの点灯状態は、ライブラリ内の専用関数にて制御します。
	\sa SetRoadwaySignalColor() SetCrosswalkSignalColor() SetPedestrianLamp()

	### 実装上の注意

	- 実装はC99規格に従う必要があります。
	- 最終的には組み込みマイコンで動作させるため、Cの標準ライブラリ(printfやmalloc)等は使わないでください。
	- Debugモードでビルドするといくつか警告が発生しますが、無視してください。
*/

#include "signallib.h"

/*!
	\brief サンプル用構造体
	\details
	サンプル動作を行うための情報を記憶する構造体です。
*/
typedef struct{
	struct{
		int cnt;						/*!< 点灯時間 */
		RoadwaySignalColor col;			/*!< 点灯色 */
	}roadway;							/*!< 車用信号 */
	int pedestrianCnt;					/*!< "おまちください"ランプ点灯時間 */
	CrosswalkSignalColor crosswalkCol;	/*!< 歩行者用信号の点灯色*/
}Context;

static Context ctx;

/*!
	\brief 初期化コールバック
	\details
	プログラムの初期化時に1回だけライブラリからコールされます。
	この関数内でアプリケーションを初期化してください。
	\attention
	この関数は必須です。削除または宣言の変更をしないでください。
*/
void OnInitialize(void){
	ctx.pedestrianCnt = 0;
	ctx.roadway.cnt = 0;
	ctx.roadway.col = RSCBlack;
	ctx.crosswalkCol = CSCBlack;
}

/*!
	\brief 開始コールバック
	\details
	プログラムの初期化終了後、プログラム開始時に1回だけライブラリからコールされます。
	この関数内でプログラム開始に必要な初期化してください。
	\attention
	この関数は必須です。削除または宣言の変更をしないでください。
*/
void OnStart(void){
}

/*!
	\brief タイマコールバック
	\details
	プログラム開始後、ライブラリから周期的にコールされます。
	\param[in] elapse 前回コールされた時からの経過時間[msec]
	\attention
	この関数は必須です。削除または宣言の変更をしないでください。
*/
void OnTimer(int elapse){
	ctx.roadway.cnt += elapse;

	if (ctx.roadway.cnt >= 500) {
		ctx.roadway.cnt %= 500;
		ctx.roadway.col = (ctx.roadway.col + 1) % (RSCRed + 1);
		SetRoadwaySignalColor(ctx.roadway.col);
	}

	if (ctx.pedestrianCnt >= elapse) {
		ctx.pedestrianCnt -= elapse;
		SetPedestrianLamp(PLWait);
	} else {
		ctx.pedestrianCnt = 0;
		SetPedestrianLamp(PLPushButton);
	}
}

/*!
	\brief ボタンコールバック
	\details
	プログラム開始後、ボタンが押された時にコールされます。
	\attention
	この関数は必須です。削除または宣言の変更をしないでください。
*/
void OnButton(void){
	ctx.pedestrianCnt = 2000;
	SetPedestrianLamp(PLWait);

	ctx.crosswalkCol = (ctx.crosswalkCol + 1) % (CSCRed + 1);
	SetCrosswalkSignalColor(ctx.crosswalkCol);
}

/*!
\mainpage
### 模擬信号ライブラリ サンプルプログラム

これは模擬信号ライブラリ(SingalLib)の使い方を説明するためのサンプルプログラムです。

詳しい説明は「signal.c」ファイル中に書かれています。上の「ファイル」->「signal.c」からリンクを辿ってください。
*/

