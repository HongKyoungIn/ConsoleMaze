#pragma once

typedef unsigned __int64 ULONGLONG;

namespace myTime {
	void InitTime();
	void UpdateTime();
	const float GetFrameRate();
	const ULONGLONG GetDeltaTime();
	int  PlayTime();
	bool shouldProcessInput();
}