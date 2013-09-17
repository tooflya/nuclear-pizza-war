<<<<<<< HEAD
#include "main.h"

=======
>>>>>>> f9f27125dceb14026510c91133d98969d0d7d29b
#include "AppDelegate.h"
#include "cocos2d.h"

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string>

USING_NS_CC;

int main(int argc, char **argv)
{
<<<<<<< HEAD
	AppDelegate app;

	CCEGLView* eglView = CCEGLView::sharedOpenGLView();

	eglView->setFrameSize(1280, 720);

	return CCApplication::sharedApplication()->run();
=======
    AppDelegate app;

    CCEGLView* eglView = CCEGLView::sharedOpenGLView();

    eglView->setFrameSize(1280, 720);

    return CCApplication::sharedApplication()->run();
>>>>>>> f9f27125dceb14026510c91133d98969d0d7d29b
}