#include "CriticalSectionLock.hpp"

CriticalSectionLock::CriticalSectionLock(CriticalSection& pCritSec)
{
	m_pCritSec = &pCritSec;
	m_pCritSec->Lock();
}

CriticalSectionLock::~CriticalSectionLock()
{
	m_pCritSec->Unlock();
}
