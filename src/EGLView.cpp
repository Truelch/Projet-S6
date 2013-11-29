#include "EGLView.h"
#include "GL/glfw.h"
#include "Scene.h"

void coordinateOpenglToCocos2dx(int x, int y, float& cocos_x, float& cocos_y) {
	EGLView* pEGLView = EGLView::sharedOpenGLView();
	cocos_x = ((float)x/pEGLView->getFrameZoomFactor() - pEGLView->getViewPortRect().origin.x) / pEGLView->getScaleX();
	cocos_y = ((pEGLView->getViewPortRect().getMaxY()-(float)y)/pEGLView->getFrameZoomFactor() - pEGLView->getViewPortRect().origin.y) / pEGLView->getScaleY();
}

void mouse_button_event(int iMouseID,int iMouseState) {
	Scene * scene = (Scene *)cocos2d::CCDirector::sharedDirector()->getRunningScene();
	int x,y;
	
	if(scene) {

		glfwGetMousePos(&x, &y);

		if (iMouseState == GLFW_PRESS) {
			if( iMouseID == GLFW_MOUSE_BUTTON_LEFT )
				scene->mouse_left_button_down(x,y);
			else if( iMouseID == GLFW_MOUSE_BUTTON_RIGHT )
				scene->mouse_left_button_down(x,y);
		} else if (iMouseState == GLFW_RELEASE) {
			if( iMouseID == GLFW_MOUSE_BUTTON_LEFT )
				scene->mouse_left_button_up(x,y);
			else if( iMouseID == GLFW_MOUSE_BUTTON_RIGHT )
				scene->mouse_right_button_up(x,y);
		}
	}
}

void mouse_pos_event(int x,int y) {
	Scene * scene = (Scene *)cocos2d::CCDirector::sharedDirector()->getRunningScene();
	if(scene) scene->mouse_move(x,y);
}

void key_event_handle(int iKeyID,int iKeyState) {
	Scene * scene = (Scene *)cocos2d::CCDirector::sharedDirector()->getRunningScene();
	if( iKeyState==GLFW_PRESS && scene ) {
		scene->key_press(iKeyID);
	}
}

void EGLView::setFrameSize(float width, float height) {
	cocos2d::CCEGLView::setFrameSize(width,height);
	glfwSetMouseButtonCallback(mouse_button_event);
	glfwSetMousePosCallback(mouse_pos_event);
	glfwSetKeyCallback(key_event_handle);
}

EGLView* EGLView::sharedOpenGLView()
{
	static EGLView* s_pEglView = NULL;
	if (s_pEglView == NULL)
	{
		s_pEglView = new EGLView();
	}
	return s_pEglView;
}
