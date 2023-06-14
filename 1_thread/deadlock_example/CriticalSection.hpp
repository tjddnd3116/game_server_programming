#ifndef CriticalSection_hpp
#define CriticalSection_hpp

#include <pthread.h>

class CriticalSection
{
		private:
			pthread_mutex_t m_mutex;

		public:
			CriticalSection();
			~CriticalSection();

			void Lock();
			void Unlock();
};
#endif //CriticalSection_hpp
