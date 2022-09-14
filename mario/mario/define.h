#pragma once
/* windows constant values */
#define WIDTH				800
#define HEIGHT				600
#define VK_MAX				0xFF

/* constant values */
#define TEXT_LENGTH			64
#define	PI					3.141592f

/* update return event */
#define EVENT_SUCCEED		 0
#define EVENT_FAILED		-1

enum class OBJ_TYPE
{
	DEFAULT,      //�ʱⰪ
	PLAYER,       //�÷��̾�
	ENEMY,        //��
	INTERACTION,  //��ȣ�ۿ� ������Ʈ
	ENVIRONMENT,  //ȯ�� ������Ʈ
	TERRAIN,      //����
	UI,			  //UI
	END
};

enum class OBJ_STATE
{
	DEFAULT,  //�ʱⰪ
	ACTIVE,   //Ȱ��ȭ
	DISABLE,  //��Ȱ��ȭ : ��Ȱ��ȭ�� ������Ʈ �κп��� ������Ʈ ����
	END
};

enum class SCENE_STATE
{
	STAGE_START,	// ���ӽ��� �޴�
	STAGE_1,		// �������� 1
	STAGE_2,		// �������� 2
	STAGE_3,		// �������� 3
	STAGE_4,		// �������� 4
	STAGE_END,		// �������� ��
	STAGE_COUNT
};

enum class KEY_STATE
{
	NONE,	 //����Ʈ
	PRESSED, //��������
	DOWN,    //Ű �ٿ�
	UP       //Ű �� 
};