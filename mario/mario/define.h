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
	DEFAULT,      //초기값
	ENVIRONMENT,  //환경 오브젝트
	TERRAIN,      //지형
	ENUMY,	      //몬스터
	PLAYER,       //플레이어
	INTERACTION,  //상호작용 오브젝트
	UI,			  //UI
	END
};

enum class OBJ_STATE
{
	DEFAULT,  //초기값
	ACTIVE,   //활성화
	DISABLE,  //비활성화 : 비활성화시 업데이트 부분에서 오브젝트 제거
	END
};

enum class SCENE_STATE
{
	STAGE_START,	// 게임시작 메뉴
	STAGE_1,		// 스테이지 1
	STAGE_2,		// 스테이지 2
	STAGE_3,		// 스테이지 3
	STAGE_4,		// 스테이지 4
	STAGE_END,		// 게임종료 씬
	STAGE_EDIT,	    // 에디터 씬
	STAGE_COUNT
};

enum class KEY_STATE
{
	NONE,	 //디폴트
	PRESSED, //눌려있음
	DOWN,    //키 다운
	UP       //키 업 
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