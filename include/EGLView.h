#ifndef EGL_VIEW
#define EGL_VIEW

#include "cocos2d.h"

void coordinateOpenglToCocos2dx(int opengl_x, int opengl_y, float& cocos_x, float& cocos_y);
void coordinateCocos2dxToOpengl(float cocos_x, float cocos_y, int& opengl_x, int& opengl_y);

class EGLView : public cocos2d::CCEGLView {
	public:
		EGLView(): CCEGLView() {}

		virtual void setFrameSize(float width, float height);

		static EGLView* sharedOpenGLView();
	
};

#endif
