#ifndef EGL_VIEW
#define EGL_VIEW

#include "cocos2d.h"

float leght_pixel_to_cocos(int lenght);
int lenght_cocos_to_pixel(float lenght);
void coordinateOpenglToCocos2dx(int opengl_x, int opengl_y, float& cocos_x, float& cocos_y, cocos2d::CCLayer * layer);
void coordinateCocos2dxToOpengl(float cocos_x, float cocos_y, int& opengl_x, int& opengl_y);

class EGLView : public cocos2d::CCEGLView {
	public:
		EGLView(): CCEGLView() {}

		virtual void setFrameSize(float width, float height);

		static EGLView* sharedOpenGLView();
	
};

#endif
