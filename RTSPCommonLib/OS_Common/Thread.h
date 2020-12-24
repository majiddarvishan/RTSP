#ifndef __THREAD_H__
#define __THREAD_H__

#include <windows.h>
#include <process.h>

#define THREAD		HANDLE
#define THREAD_FUNC	unsigned __stdcall

int THREAD_CREATE(THREAD *thread, THREAD_FUNC func(void *), void *param);
int THREAD_JOIN(THREAD *thread);
void THREAD_DESTROY(THREAD *thread);

#endif
