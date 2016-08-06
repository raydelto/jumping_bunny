#include "../Classes/AppDelegate.h"
#include "cocos2d.h"

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string>

USING_NS_CC;

int main(int argc, char **argv)
{
    // create the application instance
    AppDelegate app;

    CCEGLView* eglView = CCEGLView::sharedOpenGLView();
    int width = 240;
    int height = 320;
    if(argc >1){
       if(strcmp(argv[1],"z10") == 0){
		CCLog("Z10  :  720 x 1280");
		width = 720;
		height = 1280;
	}else if(strcmp(argv[1],"q10") == 0){
		CCLog("Q10  :  720 x 720");
		width = 720;
		height = 720;
	}
	else if(strcmp(argv[1],"s2") == 0){
		CCLog("Galaxy S2  :  480 x 800");
		width = 480;
		height = 800;
	}else if(strcmp(argv[1],"iphone5") == 0){
		CCLog("iphone5 :  640 x 1136");
		width = 640;
		height = 1136;
	}else if(strcmp(argv[1],"iphone4") == 0){
		CCLog("iphone4  :  640 x 960");
		width = 640;
		height = 960;
	}


    }
    eglView->setFrameSize(width, height);
    return CCApplication::sharedApplication()->run();
}
