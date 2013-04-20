#include "main.h"

#include "AppDelegate.h"
#include "cocos2d.h"

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string>

USING_NS_CC;

int main(int argc, char **argv)
{
	AppDelegate app;

	CCEGLView* eglView = CCEGLView::sharedOpenGLView();

	eglView->setFrameSize(1280, 720);

	return CCApplication::sharedApplication()->run();
}