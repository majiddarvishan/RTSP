#include <stdio.h>
#include "RTSPServer.h"
#include "RTSPLiveStreamer.h"

#pragma comment(lib, "RTSPCommonLib.lib")

#include <conio.h>
#include <windows.h>

#ifdef _DEBUG
#include <crtdbg.h>
#endif

#define mygetch	getch

#define NUM_STREAMER (5)

RTSPLiveStreamer *streamers[NUM_STREAMER] = { NULL };

void addServerSessions()
{
	streamers[0] = new RTSPLiveStreamer();
	streamers[0]->open("rtsp://172.30.1.213/live/main", 0, "stream1");
	streamers[0]->run();

	streamers[1] = new RTSPLiveStreamer();
	streamers[1]->open("rtsp://admin:1234@172.30.10.103/h264", 0, "stream2");
	streamers[1]->run();
}

void removeServerSessions()
{
	for (int i=0; i<NUM_STREAMER; i++) {
		if (streamers[i]) {
			streamers[i]->close();
			delete streamers[i];
			streamers[i] = NULL;
		}
	}
}

int main(int argc, char *argv[])
{
#ifdef _DEBUG
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif

	addServerSessions();

	RTSPServer *rtspServer = RTSPServer::instance();
	rtspServer->startServer(8554);

	char c;
	while (c = mygetch() != 'q') 
    {
		Sleep(10);
	}

	removeServerSessions();

	rtspServer->stopServer();

	rtspServer->destroy();

	return 0;
}
