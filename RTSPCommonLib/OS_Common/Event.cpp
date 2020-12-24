#include "Event.h"

void EVENT_INIT(EVENT *event)
{
	*event = CreateEvent(NULL, TRUE, FALSE, NULL);
}

void EVENT_DESTROY(EVENT *event)
{
	CloseHandle(*event);
}

void EVENT_WAIT(EVENT *event)
{
	WaitForSingleObject(*event, INFINITE);
}

void EVENT_SET(EVENT *event)
{
	SetEvent(*event);
}

void EVENT_RESET(EVENT *event)
{
	ResetEvent(*event);
}
