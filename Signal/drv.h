/*!
	\file drv.h
	\brief ハードウェアドライバ
	\author BeNest SDGr K.Urakari
	\date 2015/11/14
*/

#ifndef DRV_H_
#define DRV_H_

#include <stdbool.h>

/*!
	\brief 車用信号色
*/
typedef enum{
	RSCBlack = 0,	/*!< 消灯 */
	RSCBlue,		/*!< 青 */
	RSCYellow,		/*!< 黄色 */
	RSCRed,			/*!< 赤 */
}RoadwaySignalColor;

/*!
	\brief 歩行者用信号色
*/
typedef enum{
	CSCBlack = 0,	/*!< 消灯 */
	CSCBlue,		/*!< 青 */
	CSCRed,			/*!< 赤 */
}CrosswalkSignalColor;

/*!
	\brief 操作箱ランプ種別
*/
typedef enum{
	PLOff = 0,		/*!< 消灯中 */
	PLPushButton,	/*!< "ボタンをおしてください" */
	PLWait,			/*!< "おまちください"*/
}PedestrianLamp;

/*!
	\brief ドライバ初期化
	\param[in] option 初期化情報
*/
void InitDriver(void* option);

/*!
	\brief ドライバ終了
*/
void UninitDriver(void);

/*!
	\brief 車用信号色の設定
	\param[in] color 色
*/
void SetRoadwaySignalColor(RoadwaySignalColor color);

/*!
	\brief 歩行車用信号色の設定
	\param[in] color 色
*/
void SetCrosswalkSignalColor(CrosswalkSignalColor color);

/*!
	\brief 操作箱ランプの設定
	\param[in] lamp ランプ
*/
void SetPedestrianLamp(PedestrianLamp lamp);

/*!
	\brief 操作箱ボタンの状態取得
	\retval true 押されている
	\retval false 押されていない
*/
_Bool GetPedestrianButton(void);

#endif
