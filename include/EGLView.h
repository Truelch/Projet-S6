#ifndef EGL_VIEW
#define EGL_VIEW

#include "cocos2d.h"

float lenght_pixel_to_cocos(int lenght);
int lenght_cocos_to_pixel(float lenght);
void coordinateOpenglToCocos2dx(int opengl_x, int opengl_y, float& cocos_x, float& cocos_y);
void coordinateCocos2dxToOpengl(float cocos_x, float cocos_y, int& opengl_x, int& opengl_y);

class EGLView : public cocos2d::CCEGLView {
	public:
		EGLView();

		virtual void setFrameSize(int width, int height);

		static EGLView* sharedOpenGLView();

		/*
		virtual bool isOpenGLReady();
		virtual void swapBuffers();

		bool initGL();

	private:
		bool bIsInit;
		*/
	
};

#endif
