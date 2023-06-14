#ifndef CriticalSectionLock_hpp
#define CriticalSectionLock_hpp

#include "CriticalSection.hpp"

class CriticalSectionLock
{
		private:
			CriticalSection* m_pCritSec;

		public:
			CriticalSectionLock(CriticalSection& pCritSec);
			~CriticalSectionLock();
};
#endif //CriticalSectionLock_hpp
