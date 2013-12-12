#include "EGLView.h"
#include "GL/glfw.h"
#include "Scene.h"

int closeEventHandle() {
	cocos2d::CCDirector::sharedDirector()->end();
	return GL_TRUE;
}


float leght_pixel_to_cocos(int lenght) {
	EGLView* pEGLView = EGLView::sharedOpenGLView();
	return (float)lenght/(pEGLView->getFrameZoomFactor()*pEGLView->getScaleX());
}

int lenght_cocos_to_pixel(float lenght) {
	EGLView* pEGLView = EGLView::sharedOpenGLView();
	return (int)(lenght*pEGLView->getScaleX()*pEGLView->getFrameZoomFactor());
}

void coordinateOpenglToCocos2dx(int opengl_x, int opengl_y, float& cocos_x, float& cocos_y) {
	EGLView* pEGLView = EGLView::sharedOpenGLView();

	cocos_x = ((float)opengl_x/pEGLView->getFrameZoomFactor() - pEGLView->getViewPortRect().origin.x) / pEGLView->getScaleX();
	cocos_y = ((pEGLView->getViewPortRect().getMaxY()-(float)opengl_y)/pEGLView->getFrameZoomFactor() - pEGLView->getViewPortRect().origin.y) / pEGLView->getScaleY();
}

void coordinateCocos2dxToOpengl(float cocos_x, float cocos_y, int& opengl_x, int& opengl_y) {
	EGLView* pEGLView = EGLView::sharedOpenGLView();
	opengl_x = (int)((cocos_x*pEGLView->getScaleX()+pEGLView->getViewPortRect().origin.x)*pEGLView->getFrameZoomFactor());
	opengl_y = (int)(pEGLView->getViewPortRect().getMaxY()-(cocos_y*pEGLView->getScaleY()+pEGLView->getViewPortRect().origin.y)*pEGLView->getFrameZoomFactor());
}

void mouse_button_event(int iMouseID,int iMouseState) {
	Scene * scene = (Scene *)cocos2d::CCDirector::sharedDirector()->getRunningScene();
	
	if(scene) {

		if (iMouseState == GLFW_PRESS) {
			if( iMouseID == GLFW_MOUSE_BUTTON_LEFT )
				scene->mouse_left_button_down();
			else if( iMouseID == GLFW_MOUSE_BUTTON_RIGHT )
				scene->mouse_right_button_down();
		} else if (iMouseState == GLFW_RELEASE) {
			if( iMouseID == GLFW_MOUSE_BUTTON_LEFT )
				scene->mouse_left_button_up();
			else if( iMouseID == GLFW_MOUSE_BUTTON_RIGHT )
				scene->mouse_right_button_up();
		}
	}
}

void mouse_pos_event(int x,int y) {
	Scene * scene = (Scene *)cocos2d::CCDirector::sharedDirector()->getRunningScene();
	if(scene) scene->mouse_move(x,y);
}

void mouse_wheel(int pos) {
	static int old_pos=0;
	Scene * scene = (Scene *)cocos2d::CCDirector::sharedDirector()->getRunningScene();
	if(scene) {
		if(pos==old_pos+1) scene->mouse_wheel_up();
		else if(pos==old_pos-1) scene->mouse_wheel_down();
	}
	old_pos=pos;
}

void key_event_handle(int iKeyID,int iKeyState) {
	Scene * scene = (Scene *)cocos2d::CCDirector::sharedDirector()->getRunningScene();
	if(scene) {
		if( iKeyState==GLFW_PRESS ) {
			scene->key_press(iKeyID);
		}
		else if( iKeyState==GLFW_RELEASE ) {
			scene->key_release(iKeyID);
		}
	}
}

//EGLView::EGLView(): CCEGLView(), bIsInit(false) {}

EGLView::EGLView(): CCEGLView() {}


EGLView* EGLView::sharedOpenGLView()
{
	static EGLView* s_pEglView = NULL;
	if (s_pEglView == NULL)
	{
		s_pEglView = new EGLView();
	}
	return s_pEglView;
}

void EGLView::setFrameSize(int width, int height) {
//	bool eResult = false;
//	int u32GLFWFlags = GLFW_FULLSCREEN;
//	//create the window by glfw.
//
//	//check
//	CCAssert(width!=0&&height!=0, "invalid window's size equal 0");
//
//	//Inits GLFW
//	eResult = glfwInit() != GL_FALSE;
//
//	if (!eResult) {
//		CCAssert(0, "fail to init the glfw");
//	}
//
//	/* Updates window hint */
//	glfwOpenWindowHint(GLFW_WINDOW_NO_RESIZE, GL_TRUE);
//
//	int iDepth = 16; // set default value
//	/* Depending on video depth */
//	switch(iDepth)
//	{
//		/* 16-bit */
//		case 16:
//		{
//			/* Updates video mode */
//			eResult = (glfwOpenWindow(width, height, 5, 6, 5, 0, 16, 8, (int)u32GLFWFlags) != false) ? true : false;
//
//			break;
//		}
//
//		/* 24-bit */
//		case 24:
//		{
//			/* Updates video mode */
//			eResult = (glfwOpenWindow(width, height, 8, 8, 8, 0, 16, 8, (int)u32GLFWFlags) != false) ? true : false;
//
//			break;
//		}
//
//		/* 32-bit */
//		default:
//		case 32:
//		{
//			/* Updates video mode */
//			eResult = (glfwOpenWindow(width, height, 8, 8, 8, 8, 16, 8, (int)u32GLFWFlags) != GL_FALSE) ? true :false;
//			break;
//		}
//	}
//
//	/* Success? */
//	if(eResult)
//	{
//
//	  	glfwGetWindowSize(&width, &height);
//
//		CCEGLViewProtocol::setFrameSize(width, height);		
//
//		/* Updates its title */
//		glfwSetWindowTitle("Cocos2dx-Linux");
//
//		//set the init flag
//		bIsInit = true;
//
//		glfwSetWindowCloseCallback(closeEventHandle);
//
//
//		//Inits extensions
//		eResult = initExtensions();
//
//		if (!eResult) {
//			CCAssert(0, "fail to init the extensions of opengl");
//		}
//		initGL();
//	}

	CCEGLView::setFrameSize(width,height);
	glfwSetMouseButtonCallback(mouse_button_event);
	glfwSetMousePosCallback(mouse_pos_event);
	glfwSetKeyCallback(key_event_handle);
	glfwSetMouseWheelCallback(mouse_wheel);

}

//bool EGLView::isOpenGLReady()
//{
//	return bIsInit;
//}
//
//void EGLView::swapBuffers() {
//	if (bIsInit) {
//		/* Swap buffers */
//		glfwSwapBuffers();
//	}
//}
//
//bool EGLView::initGL()
//{
//    GLenum GlewInitResult = glewInit();
//    if (GLEW_OK != GlewInitResult) 
//    {
//        fprintf(stderr,"ERROR: %s\n",glewGetErrorString(GlewInitResult));
//        return false;
//    }
//
//    if (GLEW_ARB_vertex_shader && GLEW_ARB_fragment_shader)
//    {
//        cocos2d::CCLog("Ready for GLSL");
//    }
//    else 
//    {
//        cocos2d::CCLog("Not totally ready :(");
//    }
//
//    if (glewIsSupported("GL_VERSION_2_0"))
//    {
//        cocos2d::CCLog("Ready for OpenGL 2.0");
//    }
//    else
//    {
//        cocos2d::CCLog("OpenGL 2.0 not supported");
//    }
//
//    // Enable point size by default on linux.
//    glEnable(GL_VERTEX_PROGRAM_POINT_SIZE);
//
//    return true;
//}
