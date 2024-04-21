#include "time.h"
#include <cmath>
#include <Windows.h>

namespace myTime {
	ULONGLONG previousTime;
	ULONGLONG currentTime;
	ULONGLONG deltaTime;
	ULONGLONG playStartTime; // 플레이 시작 시간

	void InitTime() {
		previousTime = currentTime = GetTickCount64();
		playStartTime = previousTime;
	}

	void UpdateTime() {
		previousTime = currentTime;
		currentTime = GetTickCount64();
		deltaTime = currentTime - previousTime;
	}

	int PlayTime() {
		int currentPlayTime = GetTickCount64() - playStartTime; // 현재 플레이 타임 계산
		return currentPlayTime;
	}

	const float GetFrameRate() {
		if(deltaTime == 0) {
			return 0;
		}

		return ceil(((1000.0f / deltaTime) * 1000) / 1000);
	}

	const ULONGLONG GetDeltaTime() {
		return deltaTime;
	}
}