#pragma once 
#include<pthread.h>
#include<semaphore.h>
#include<signal.h>
#include<unistd.h>

#define SEM_INIT_VALUE 0

class CloudPushOSWrapper 
{
	private:
		sem_t sem_lock;
	public:
		void CloudPushOSWrapperSemInit()
		{
			sem_init(&sem_lock,0,SEM_INIT_VALUE);
		}

		void CloudPushOSWrapperDestroy()
		{
			sem_destroy(&sem_lock);
		}

		void CloudPushOSWrapperSemUnlock()
		{
			sem_post(&sem_lock);
		}

		void CloudPushOSWrapperSemLock()
		{
			sem_wait(&sem_lock);
		}

};
