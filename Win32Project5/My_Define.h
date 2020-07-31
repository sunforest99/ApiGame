#pragma once

#define MEX_BULLET 20
#define BUL_SPEED 4
#define MEX_MONSTER 10

enum{
	LOGO = 1,
	MENU,
	GAME,
};

enum{
	INIT = 1,
	LOOP,
	DESTROY,
};

enum{
	KEY_UP,
	KEY_DOWN,
	KEY_LEFT,
	KEY_RIGHT,
	KEY_SPACE,
};

typedef enum{
	LIVE,
	DIE,
} LIVEDIE;