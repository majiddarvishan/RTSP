#include "Mutex.h"

int MUTEX_INIT(MUTEX *mutex)
{
	*mutex = CreateMutex(NULL, FALSE, NULL);
	return *mutex == NULL ? -1 : 0;
}

int MUTEX_DESTROY(MUTEX *mutex)
{
	if (*mutex) 
    {
		CloseHandle(*mutex);
		*mutex = NULL;
	}
	return 0;
}

int MUTEX_LOCK(MUTEX *mutex)
{
	return WaitForSingleObject(*mutex, INFINITE) == WAIT_FAILED ? -1 : 0;
}

int MUTEX_UNLOCK(MUTEX *mutex)
{
	return ReleaseMutex(*mutex) == 0 ? -1 : 1;
}
