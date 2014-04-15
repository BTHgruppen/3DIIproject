// ╔════════════════════════════════════════════════════════════════════════════════════╗
// ║ Filename: Timer.h																	║
// ║																					║
// ║ Copyright: Jonas Axelsson															║
// ║ Created: 2013-03-05																║
// ║																					║
// ║ Desciription:																		║
// ║  Main game timer, used for accurate time measurements.								║
// ╚════════════════════════════════════════════════════════════════════════════════════╝

#pragma once
#include "../../Misc/Inclusions.h"

// ╔════════════════════════════════════════════════════════════════════════════════════╗
// ║ Class definition.																	║
// ╚════════════════════════════════════════════════════════════════════════════════════╝
class Timer
{
public:
	public:
		// Functions:
		Timer();
		~Timer();

		void Count();
		void Start();
		void Stop();
		void Reset();

		float GetDeltaTime(); // NOTE: Return value in seconds.
		float GetTotalTime(); // NOTE: Return value in seconds.
		
	private:
		// Variables:
		double m_secondsPerCount;
		double m_deltaTime;

		__int64 m_baseTime;
		__int64 m_pausedTime;
		__int64 m_stopTime;
		
		__int64 m_currentTime;
		__int64 m_previousTime;

		bool m_stopped;
};