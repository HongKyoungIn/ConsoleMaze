#include "time.h"
#include <cmath>
#include <Windows.h>

namespace myTime {
	ULONGLONG previousTime;
	ULONGLONG currentTime;
	ULONGLONG deltaTime;
	ULONGLONG playStartTime; // 플레이 시작 시간
	const int DEBOUNCE_DELAY = 100; // 입력 디바운스 간격 (밀리초)
	DWORD lastInputTime = GetTickCount64(); // 마지막 입력 시간을 저장하는 변수

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

	bool shouldProcessInput() {
		DWORD currentTime = GetTickCount64(); // 현재 시간 가져오기

		// 입력 디바운스 간격 이내에 새로운 입력이 감지되면 처리하지 않음
		if(currentTime - lastInputTime < DEBOUNCE_DELAY) {
			return true; // 입력을 처리
		}

		// 입력을 처리할 수 있는 경우, 마지막 입력 시간을 업데이트
		lastInputTime = currentTime;
		return false; // 입력을 처리하지 않음
	}
}