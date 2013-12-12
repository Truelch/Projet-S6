#include "AppDelegate.h"
#include "cocos2d.h"
#include "EGLView.h"

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string>
#include <stdlib.h>
#include <time.h>

#include <GL/glfw.h>

USING_NS_CC;

int main(int argc, char **argv)
{
	// create the application instance
	AppDelegate app;

	srand(time(NULL));

	EGLView* eglView = EGLView::sharedOpenGLView();
	eglView->setFrameSize(1024,768);

	cocos2d::CCApplication * app2 = CCApplication::sharedApplication();
	return app2->run();
}
