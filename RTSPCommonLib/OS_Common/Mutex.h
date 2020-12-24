#ifndef __MUTEX_H__
#define __MUTEX_H__

#include <windows.h>
#include <process.h>

#define MUTEX	HANDLE
#define PTHREAD_MUTEX_INITIALIZER	CreateMutex(NULL, FALSE, NULL)

int MUTEX_INIT(MUTEX *mutex);
int MUTEX_LOCK(MUTEX *mutex);
int MUTEX_UNLOCK(MUTEX *mutex);
int MUTEX_DESTROY(MUTEX *mutex);

#endif
