/*!
	\file drv.h
	\brief �n�[�h�E�F�A�h���C�o
	\author BeNest SDGr K.Urakari
	\date 2015/11/14
*/

#ifndef DRV_H_
#define DRV_H_

#include <stdbool.h>

/*!
	\brief �ԗp�M���F
*/
typedef enum{
	RSCBlack = 0,	/*!< ���� */
	RSCBlue,		/*!< �� */
	RSCYellow,		/*!< ���F */
	RSCRed,			/*!< �� */
}RoadwaySignalColor;

/*!
	\brief ���s�җp�M���F
*/
typedef enum{
	CSCBlack = 0,	/*!< ���� */
	CSCBlue,		/*!< �� */
	CSCRed,			/*!< �� */
}CrosswalkSignalColor;

/*!
	\brief ���씠�����v���
*/
typedef enum{
	PLOff = 0,		/*!< ������ */
	PLPushButton,	/*!< "�{�^���������Ă�������" */
	PLWait,			/*!< "���܂���������"*/
}PedestrianLamp;

/*!
	\brief �h���C�o������
	\param[in] option ���������
*/
void InitDriver(void* option);

/*!
	\brief �h���C�o�I��
*/
void UninitDriver(void);

/*!
	\brief �ԗp�M���F�̐ݒ�
	\param[in] color �F
*/
void SetRoadwaySignalColor(RoadwaySignalColor color);

/*!
	\brief ���s�ԗp�M���F�̐ݒ�
	\param[in] color �F
*/
void SetCrosswalkSignalColor(CrosswalkSignalColor color);

/*!
	\brief ���씠�����v�̐ݒ�
	\param[in] lamp �����v
*/
void SetPedestrianLamp(PedestrianLamp lamp);

/*!
	\brief ���씠�{�^���̏�Ԏ擾
	\retval true ������Ă���
	\retval false ������Ă��Ȃ�
*/
_Bool GetPedestrianButton(void);

#endif
