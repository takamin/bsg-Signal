/*!
	\file signal.c
	\brief �͋[�M�����C�u���� ���C������
	\author BeNest SDGr K.Urakari
	\date 2015/11/14
	\details
	### �T�v

	���̃t�@�C����SignalLib�̎g�p���@��������邽�߂̃T���v���t�@�C���ł��B

	���C�u��������R�[�������֐�����ʂ�T���v���������Ă��܂��B
	���̎������C������(�R�[���o�b�N�֐��̒��g������������)���ƂŃA�v���P�[�V�������������܂��B	
	
	�����v�̕`���{�^���̓��͂̓��C�u�������ŏ������Ă��܂��̂ŁA�R�[���o�b�N�֐��ɂ̓A�v���P�[�V�����ŗL�̏����݂̂��L�q���܂��B
	
	### �T���v���̓���

	�T���v������Ƃ��Ď��̗l�Ɏ�������Ă��܂��B�����܂Ń��C�u�����̊m�F�p�T���v�������ł��̂Ŗ{���̓���ł͂���܂���B

	- �ԗp�M��
	�@500msec�����Łu����->�_��->���F�_��->�ԓ_���v���J��Ԃ��܂��B
	- ���s�җp�M��
	�@�{�^����������閈�Ɂu����->�_��->�ԓ_���v���J��Ԃ��܂��B
	- "���܂���������"�����"�{�^���������Ă�������"�����v
	�@�{�^������������2�b�ԁA"���܂���������"��_�����A���̌�"�{�^���������Ă�������"��_�����܂��B
	
	### ���C�u�����̎g����

	#### �R�[���o�b�N
	���C�u���������4�̊֐����R�[������܂��B�����̊֐������݂��Ȃ���΃r���h�G���[�ɂȂ�܂��B
	�֐����폜������錾��ς��Ȃ��ł��������B
	\sa OnInitialize() OnStart() OnTimer() OnButton()

	#### �͋[�n�[�h�E�F�A�̐���
	�e�����v�͂̓_����Ԃ́A���C�u�������̐�p�֐��ɂĐ��䂵�܂��B
	\sa SetRoadwaySignalColor() SetCrosswalkSignalColor() SetPedestrianLamp()

	### ������̒���

	- ������C99�K�i�ɏ]���K�v������܂��B
	- �ŏI�I�ɂ͑g�ݍ��݃}�C�R���œ��삳���邽�߁AC�̕W�����C�u����(printf��malloc)���͎g��Ȃ��ł��������B
	- Debug���[�h�Ńr���h����Ƃ������x�����������܂����A�������Ă��������B
*/

#include "signallib.h"

/*!
	\brief �T���v���p�\����
	\details
	�T���v��������s�����߂̏����L������\���̂ł��B
*/
typedef struct{
	struct{
		int cnt;						/*!< �_������ */
		RoadwaySignalColor col;			/*!< �_���F */
	}roadway;							/*!< �ԗp�M�� */
	int pedestrianCnt;					/*!< "���܂���������"�����v�_������ */
	CrosswalkSignalColor crosswalkCol;	/*!< ���s�җp�M���̓_���F*/
}Context;

static Context ctx;

/*!
	\brief �������R�[���o�b�N
	\details
	�v���O�����̏���������1�񂾂����C�u��������R�[������܂��B
	���̊֐����ŃA�v���P�[�V���������������Ă��������B
	\attention
	���̊֐��͕K�{�ł��B�폜�܂��͐錾�̕ύX�����Ȃ��ł��������B
*/
void OnInitialize(void){
	ctx.pedestrianCnt = 0;
	ctx.roadway.cnt = 0;
	ctx.roadway.col = RSCBlack;
	ctx.crosswalkCol = CSCBlack;
}

/*!
	\brief �J�n�R�[���o�b�N
	\details
	�v���O�����̏������I����A�v���O�����J�n����1�񂾂����C�u��������R�[������܂��B
	���̊֐����Ńv���O�����J�n�ɕK�v�ȏ��������Ă��������B
	\attention
	���̊֐��͕K�{�ł��B�폜�܂��͐錾�̕ύX�����Ȃ��ł��������B
*/
void OnStart(void){
}

/*!
	\brief �^�C�}�R�[���o�b�N
	\details
	�v���O�����J�n��A���C�u������������I�ɃR�[������܂��B
	\param[in] elapse �O��R�[�����ꂽ������̌o�ߎ���[msec]
	\attention
	���̊֐��͕K�{�ł��B�폜�܂��͐錾�̕ύX�����Ȃ��ł��������B
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
	\brief �{�^���R�[���o�b�N
	\details
	�v���O�����J�n��A�{�^���������ꂽ���ɃR�[������܂��B
	\attention
	���̊֐��͕K�{�ł��B�폜�܂��͐錾�̕ύX�����Ȃ��ł��������B
*/
void OnButton(void){
	ctx.pedestrianCnt = 2000;
	SetPedestrianLamp(PLWait);

	ctx.crosswalkCol = (ctx.crosswalkCol + 1) % (CSCRed + 1);
	SetCrosswalkSignalColor(ctx.crosswalkCol);
}

/*!
\mainpage
### �͋[�M�����C�u���� �T���v���v���O����

����͖͋[�M�����C�u����(SingalLib)�̎g������������邽�߂̃T���v���v���O�����ł��B

�ڂ��������́usignal.c�v�t�@�C�����ɏ�����Ă��܂��B��́u�t�@�C���v->�usignal.c�v���烊���N��H���Ă��������B
*/

