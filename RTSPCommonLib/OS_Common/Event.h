#ifndef __EVENT_H__
#define __EVENT_H__

#include <windows.h>
#define	EVENT	HANDLE

void EVENT_INIT(EVENT *event);
void EVENT_DESTROY(EVENT *event);
void EVENT_WAIT(EVENT *event);
void EVENT_SET(EVENT *event);
void EVENT_RESET(EVENT *event);

#endif
