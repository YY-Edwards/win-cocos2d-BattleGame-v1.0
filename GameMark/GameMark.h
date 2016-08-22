#ifndef example11_1_GameMark_h
#define example11_1_GameMark_h
#include "cocos2d.h"
using namespace cocos2d;

class GameMark:public CCNode
{
public:
	
	int mark;
	Array *bits;
	Texture2D *ui;

	void addnumber(int var);
	virtual void onEnter();
	virtual void onExit();




};



#endif