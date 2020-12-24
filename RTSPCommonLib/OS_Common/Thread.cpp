#include "Thread.h"

int THREAD_CREATE(THREAD *thread, THREAD_FUNC func(void *), void *param)
{
	*thread = (HANDLE)_beginthreadex(NULL, 0, func, param, 0, NULL);
	return *thread == NULL ? -1 : 0;
}

int THREAD_JOIN(THREAD *thread)
{
	return WaitForSingleObject(*thread, INFINITE) == WAIT_FAILED ? -1 : 0;
}

void THREAD_DESTROY(THREAD *thread)
{
	if (*thread)
		CloseHandle(*thread);
}
