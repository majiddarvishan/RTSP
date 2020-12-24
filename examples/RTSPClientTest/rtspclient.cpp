#include <stdio.h>
#ifdef WIN32
#include <conio.h>
#endif

#include <iostream>

#pragma comment(lib, "RTSPClientLib.lib")
#pragma comment(lib, "RTSPCommonLib.lib")

#include "RTSPClient.h"
#include "RTSPCommonEnv.h"

#ifdef WIN32
#include <windows.h>

#ifdef _DEBUG
#include <crtdbg.h>
#endif

#define mygetch	getch

#elif defined(LINUX)
#include <stdint.h>
#include <termios.h>
#include <unistd.h>

int mygetch(void)
{
    struct termios oldt,
    newt;
    int ch;
    tcgetattr( STDIN_FILENO, &oldt );
    newt = oldt;
    newt.c_lflag &= ~( ICANON | ECHO );
    tcsetattr( STDIN_FILENO, TCSANOW, &newt );
    ch = getchar();
    tcsetattr( STDIN_FILENO, TCSANOW, &oldt );
    return ch;
}
#endif

FILE *fp_dump = NULL;

static void frameHandlerFunc(void *arg, RTP_FRAME_TYPE frame_type, int64_t timestamp, unsigned char *buf, int len)
{
	if (fp_dump)
		fwrite(buf, len, 1, fp_dump);
}

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        std::cout << "Please enter URL\n";
        return 0;
    }
#ifdef _DEBUG
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif

	RTSPCommonEnv::SetDebugFlag(DEBUG_FLAG_RTSP);

	//char *strURL = "rtsp://222.96.113.48:4554/AVStream1_2";
    char* strURL =argv[1];

	fp_dump = fopen("video.264", "wb");

	RTSPClient *rtspClient = new RTSPClient();

	if (rtspClient->openURL(strURL, 1, 2) == 0)
	{
		if (rtspClient->playURL(frameHandlerFunc, rtspClient, NULL, NULL) == 0)
		{
			char c;
			while (c = mygetch() != 'q')
			{
#ifdef WIN32
				Sleep(10);
#else
				usleep(10000);
#endif
			}
		}
	}	

	rtspClient->closeURL();
	delete rtspClient;

    if (fp_dump)
    {
        fclose(fp_dump);
    }

	return 0;
}
