#pragma once

typedef unsigned __int64 ULONGLONG;

namespace GameTime {
	void InitTime();
	void UpdateTime();
	const float GetFrameRate();
	const ULONGLONG GetDeltaTime();
	int  PlayTime();
	void SleepTime(unsigned int milliseconds);
}