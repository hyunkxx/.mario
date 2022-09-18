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

#define DeltaTime			CCore::fDeltaTime

#define SAFE_DELETE(T)		if(T){delete T; T  = nullptr;}
#define SAFE_DELETE_ARR(T)  if(T){delete[] T; T  = nullptr;}

enum class OBJ_TYPE
{
	DEFAULT,      //�ʱⰪ
	ENVIRONMENT,  //ȯ�� ������Ʈ
	TERRAIN,      //����
	ENUMY,	      //����
	PLAYER,       //�÷��̾�
	INTERACTION,  //��ȣ�ۿ� ������Ʈ
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
	STAGE_EDIT,	    // ������ ��
	STAGE_COUNT
};

enum class KEY_STATE
{
	NONE,	 //����Ʈ
	PRESSED, //��������
	DOWN,    //Ű �ٿ�
	UP       //Ű �� 
};

enum class MAP
{
	STAGE_START,
	STAGE_1,
	STAGE_2,
	STAGE_3,
	STAGE_4,
	STAGE_ENDING,
	STAGE_EDIT,
	END
};