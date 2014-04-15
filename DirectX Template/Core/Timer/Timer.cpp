// ╔════════════════════════════════════════════════════════════════════════════════════╗
// ║ Filename: Timer.cpp																║
// ║																					║
// ║ Copyright: Jonas Axelsson															║
// ║ Created: 2013-03-05																║
// ║																					║
// ║ Desciription:																		║
// ║  Main game timer, used for accurate time measurements.								║
// ╚════════════════════════════════════════════════════════════════════════════════════╝

#include "Timer.h"

// ╔════════════════════════════════════════════════════════════════════════════════════╗
// ║ Constructor and Destructor.														║
// ╚════════════════════════════════════════════════════════════════════════════════════╝
Timer::Timer() 
{
	// Set variables to initial values.
	m_secondsPerCount	= 0.0;
	m_deltaTime			= -1.0;

	m_baseTime			= 0;
	m_pausedTime		= 0;
	m_stopTime			= 0;

	m_currentTime		= 0;
	m_previousTime		= 0;
		
	m_stopped = false;

	// Query performance frequency.
	__int64 l_countsPerSecond;
	QueryPerformanceFrequency((LARGE_INTEGER*)&l_countsPerSecond);
	
	// Calculate seconds per count.
	m_secondsPerCount = 1.0 / (double)l_countsPerSecond;
}

Timer::~Timer()
{

}

// ╔════════════════════════════════════════════════════════════════════════════════════╗
// ║ Per frame count function.															║
// ╚════════════════════════════════════════════════════════════════════════════════════╝
void Timer::Count()
{
	// If the timer is paused return 0.
	if(m_stopped)
	{
		m_deltaTime = 0.0;
		return;
	}

	// Get the current frame time.
	__int64 l_currentTime;
	QueryPerformanceCounter((LARGE_INTEGER*)&l_currentTime);
	m_currentTime = l_currentTime;

	// Calculate differance between current and previous time stamps.
	m_deltaTime = (m_currentTime - m_previousTime) * m_secondsPerCount;

	// Set current time stamp as the previous.
	m_previousTime = m_currentTime;

	// Safety check for negative values.
	if(m_deltaTime < 0.0)
	{
		m_deltaTime = 0.0;
	}
}

// ╔════════════════════════════════════════════════════════════════════════════════════╗
// ║ Start timer function.																║
// ╚════════════════════════════════════════════════════════════════════════════════════╝
void Timer::Start()
{
	// Get the current frame time.
	__int64 l_currentTime;
	QueryPerformanceCounter((LARGE_INTEGER*)&l_currentTime);

	// Accumulate the time elapsed between stop and start.
	if(m_stopped)
	{
		m_pausedTime += (l_currentTime - m_stopTime);	
		m_previousTime = l_currentTime;

		// Restart timer.
		m_stopTime = 0;
		m_stopped = false;
	}
}

// ╔════════════════════════════════════════════════════════════════════════════════════╗
// ║ Stop timer function.																║
// ╚════════════════════════════════════════════════════════════════════════════════════╝
void Timer::Stop()
{
	if(!m_stopped)
	{
		// Get the current frame time.
		__int64 l_currentTime;
		QueryPerformanceCounter((LARGE_INTEGER*)&l_currentTime);

		// Stops the timer.
		m_stopTime = l_currentTime;
		m_stopped  = true;
	}
}

// ╔════════════════════════════════════════════════════════════════════════════════════╗
// ║ Reset timer function.																║
// ╚════════════════════════════════════════════════════════════════════════════════════╝
void Timer::Reset()
{
	// Get the current frame time.
	__int64 l_currentTime;
	QueryPerformanceCounter((LARGE_INTEGER*)&l_currentTime);

	// Reset base and previous time stamps.
	m_baseTime = l_currentTime;
	m_previousTime = l_currentTime;

	// Restart timer.
	m_stopTime = 0;
	m_stopped = false;
}

// ╔════════════════════════════════════════════════════════════════════════════════════╗
// ║ Get functions.																		║
// ╚════════════════════════════════════════════════════════════════════════════════════╝

// Returns the delta time in seconds.
float Timer::GetDeltaTime()
{
	return (float)m_deltaTime;
	
}

// Returns the total time in seconds. NOT counting paused time.
float Timer::GetTotalTime()
{
	float l_totalTime;

	// If timer is stopped, time that has passed since the timer stopped is ignored.
	if(m_stopped)
	{
		l_totalTime = (float)(((m_stopTime - m_pausedTime) - m_baseTime) * m_secondsPerCount);
		return l_totalTime;
	}

	//  Returned total timed passed, ignoring any paused time.
	else
	{
		l_totalTime = (float)(((m_currentTime - m_pausedTime) - m_baseTime) * m_secondsPerCount);
		return l_totalTime;
	}
}