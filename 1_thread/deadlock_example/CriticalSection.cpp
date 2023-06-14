/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CriticalSection.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soum <soum@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 17:00:19 by soum              #+#    #+#             */
/*   Updated: 2023/06/14 17:00:19 by soum             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "CriticalSection.hpp"
#include <pthread.h>

CriticalSection::CriticalSection()
{
	pthread_mutexattr_t m_mutexAttr;

	pthread_mutexattr_settype(&m_mutexAttr, PTHREAD_MUTEX_RECURSIVE);
	pthread_mutex_init(&m_mutex, &m_mutexAttr);
	pthread_mutexattr_destroy(&m_mutexAttr);
}

CriticalSection::~CriticalSection()
{
	pthread_mutex_destroy(&m_mutex);
}

void
CriticalSection::Lock()
{
	pthread_mutex_lock(&m_mutex);
}

void
CriticalSection::Unlock()
{
	pthread_mutex_unlock(&m_mutex);
}
